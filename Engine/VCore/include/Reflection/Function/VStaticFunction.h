#pragma once
#include <Reflection/Function/VFunctionBase.h>

namespace VulcanCore  {
    class ReflectionBase;

    template<typename R,typename... Args>
    class VStaticFunction : public VFunctionBase {
    public:
        using MethodType = R(*)(Args...);

        VStaticFunction(const std::string& funcName, MethodType funcMethod) : VFunctionBase(std::move(funcName)), Method(funcMethod) {
            this->Flags |= EFunctionFlags::EFunctionFlags_Static | (IsConstMemberFunction<MethodType>::value ? EFunctionFlags::EFunctionFlags_Const : EFunctionFlags::EFunctionFlags_None);
            BuildParams();
            BuildReturnType();
        }

        const std::type_info& GetReturnType() const override {
            return typeid(R);
        }

        const std::vector<VFunctionParamInfo>& GetParameters() const override {
            return Params;
        }

        std::any Invoke(ReflectionBase* instance, const std::vector<std::any>& funcArgs) {
            CheckArgs(funcArgs);
            return InvokeTyped(funcArgs, std::index_sequence_for<Args...>{});
        }

        void InvokeRaw(ReflectionBase* instance, void** argsBuffer, void* retBuffer) {
            CallRaw(argsBuffer,retBuffer,std::index_sequence_for<Args...>{});
        }

    private:
        MethodType Method;
        std::vector<VFunctionParamInfo> Params;

        template<typename T>
        static VFunctionParamInfo BuildParamInfo(const char* ParamName = "") {
            return { &typeid(T), ParamName, ParamTrait<T>::IsRef,ParamTrait<T>::IsPointer, ParamTrait<T>::IsConst };
        }
        
        void BuildParams() {
            Params = { BuildParamInfo<Args>()... };

            for (auto& p : Params) {
                if (p.IsRef) {
                    this->Flags |= EFunctionFlags::EFunctionFlags_ParamsByRef | (p.IsConst ? EFunctionFlags::EFunctionFlags_Const : EFunctionFlags::EFunctionFlags_None);
                }
                else if (p.IsPointer) {
                    this->Flags |= EFunctionFlags::EFunctionFlags_ParamsByPointer | (p.IsConst ? EFunctionFlags::EFunctionFlags_Const : EFunctionFlags::EFunctionFlags_None);
                }
                else {
                    this->Flags |= EFunctionFlags::EFunctionFlags_ParamsByValue | (p.IsConst ? EFunctionFlags::EFunctionFlags_Const : EFunctionFlags::EFunctionFlags_None);
                }
            }
        }

        void BuildReturnType() {
            using ReturnTraits = ParamTrait<R>;

            if constexpr (std::is_reference_v<R>) {
                this->Flags |= EFunctionFlags::EFunctionFlags_ReturnsRef | (ReturnTraits::IsConst ? EFunctionFlags::EFunctionFlags_Const : EFunctionFlags::EFunctionFlags_None);
            }
            else if constexpr (ReturnTraits::IsPointer) {
                this->Flags |= EFunctionFlags::EFunctionFlags_ReturnsPointer | (ReturnTraits::IsConst ? EFunctionFlags::EFunctionFlags_Const : EFunctionFlags::EFunctionFlags_None);
            }
            else {
                this->Flags |= EFunctionFlags::EFunctionFlags_ReturnsCopy | (ReturnTraits::IsConst ? EFunctionFlags::EFunctionFlags_Const : EFunctionFlags::EFunctionFlags_None);
            }
        }

        void CheckArgs(const std::vector<std::any>& args) {
            if (args.size() != sizeof...(Args)) {
                throw std::runtime_error("Bad number of arguments");
            }
            for (size_t i=0; i<args.size(); ++i) {
                if (args[i].type() != *Params[i].Type) {
                    throw std::runtime_error("Bad argument type");
                }
            }
        }
        
        template<std::size_t... I>
        std::any InvokeTyped(const std::vector<std::any>& args,std::index_sequence<I...>) {
            if constexpr (std::is_void_v<R>) {
                Method( std::any_cast<Args>(args[I])... );
                return std::any{};
            }
            else if constexpr (std::is_reference_v<R>) {
                using Raw = typename ParamTrait<R>::RawNoPtrRef;

                R ref = Method(std::any_cast<Args>(args[I])...);
                FunctionRefValue out;
                out.Ptr = const_cast<Raw*>(std::addressof(ref));
                out.Type = &typeid(Raw);
                out.IsConst = ParamTrait<R>::IsConst;

                return std::any(out);
            }
            else {
                R ref = Method( std::any_cast<Args>(args[I])... );
                return std::any(std::move(ref));
            }
        }

        template<typename A>
        static std::remove_reference_t<A>& GetArg(void* ptr) {
            using Raw = std::remove_reference_t<A>;
            return *static_cast<Raw*>(ptr);
        }

        
        template<size_t... I>
        void CallRaw(void** argsBuffer,void* returnBuffer,std::index_sequence<I...> ){
            if constexpr (std::is_void_v<R>) {
                Method( (GetArg<Args>(argsBuffer[I]))... );
            }
            else if constexpr (std::is_reference_v<R>) {
                using Raw = typename ParamTrait<R>::RawNoPtrRef;
                R ref = Method( (GetArg<Args>(argsBuffer[I]))... );

                if (!returnBuffer) {
                    throw std::runtime_error("VFunctionStatic::InvokeRaw : ReturnBuffer is null for non-void return type");
                }

                auto* out = static_cast<FunctionRefValue*>(returnBuffer);
                out->Ptr = const_cast<Raw*>(std::addressof(ref));
                out->Type = &typeid(Raw);
                out->IsConst = ParamTrait<R>::IsConst;
            }
            else {
                if (!returnBuffer) {
                    throw std::runtime_error("VFunctionStatic::InvokeRaw : ReturnBuffer is null for non-void return type");
                }
                
                *static_cast<R*>(returnBuffer) =Method( (GetArg<Args>(argsBuffer[I]))... );
            }
        }
    };
}
