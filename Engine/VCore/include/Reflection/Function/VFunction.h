#pragma once
#include <any>
#include <complex.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <Reflection/Function/VFunctionBase.h>


namespace VulcanCore  {

    template<typename C,typename R,typename... Args>
    class VFunction : public VFunctionBase {
    public:
        using MethodType = R(C::*)(Args...);

        VFunction(const std::string& funcName, MethodType funcMethod) : VFunctionBase(std::move(funcName)), Method(funcMethod) {
            this->Flags |= EFunctionFlags::EFunctionFlags_Member | (IsConstMemberFunction<MethodType>::value ? EFunctionFlags::EFunctionFlags_Const : EFunctionFlags::EFunctionFlags_None);
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
            C* obj = static_cast<C*>(instance);

            CheckArgs(funcArgs);

            return InvokeTyped(obj,funcArgs, std::index_sequence_for<Args...>{});
        }

        void InvokeRaw(ReflectionBase* instance, void** argsBuffer, void* retBuffer) {
            C* obj = static_cast<C*>(instance);

            CallRaw(obj,argsBuffer,retBuffer,std::index_sequence_for<Args...>{});
        }

    private:
        MethodType Method;
        std::vector<VFunctionParamInfo> Params;

        template<typename T>
        static VFunctionParamInfo BuildParamInfo(const char* ParamName = "") {
            return { &typeid(T), ParamName, ParamTrait<T>::IsRef,ParamTrait<T>::IsPointer,ParamTrait<T>::IsConst };
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
        std::any InvokeTyped(C* obj,const std::vector<std::any>& args,std::index_sequence<I...>) {
            if constexpr (std::is_void_v<R>) {
                (obj->*Method)(std::any_cast<Args>(args[I])...);
                return std::any{};
            }
            else if (std::is_reference_v<R>) {
                using Raw = typename ParamTrait<R>::RawNoPtrRef;

                R ref = (obj->*Method)( std::any_cast<Args>(args[I])... );
                
                FunctionRefValue outRef;
                outRef.Ptr = const_cast<Raw*>(std::addressof(ref));
                outRef.Type = &typeid(Raw);
                outRef.IsConst = ParamTrait<R>::IsConst;

                return std::any(outRef);
            }
            else {
                R result = (obj->*Method)(std::any_cast<Args>(args[I])...);
                return std::any(std::move(result));
            }
        }

        template<typename A>
        static std::remove_reference_t<A>& GetArg(void* ptr) {
            using Raw = std::remove_reference_t<A>;
            return *static_cast<Raw*>(ptr);
        }
        

        template<size_t... I>
        void CallRaw(C* obj, void** argsBuffer,void* returnBuffer,std::index_sequence<I...> ){
            if constexpr (std::is_void_v<R>) {
                (obj->*Method)(GetArg<Args>(argsBuffer[I])...);
            }
            else if (std::is_reference_v<R>) {
                using Raw = typename ParamTrait<R>::RawNoPtrRef;

                if (!returnBuffer) {
                    throw std::runtime_error("VFunction::InvokeRaw : ReturnBuffer is null for non-void return type");
                }

                R ref = (obj->*Method)(GetArg<Args>(argsBuffer[I])...);
                auto* out = static_cast<FunctionRefValue*>(returnBuffer);
                out->Ptr = const_cast<Raw*>(std::addressof(ref));
                out->Type = &typeid(Raw);
                out->IsConst = ParamTrait<R>::IsConst;
            }
            else {
                if (!returnBuffer) {
                    throw std::runtime_error("VFunction::InvokeRaw : ReturnBuffer is null for non-void return type");
                }
                *static_cast<R*>(returnBuffer) = (obj->*Method)(GetArg<Args>(argsBuffer[I])...);
            }
        }
    };
}
