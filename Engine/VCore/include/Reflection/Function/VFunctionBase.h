#pragma once

#include <Reflection/VField.h>
#include <Reflection/Function/FunctionUtils.h>

namespace VulcanCore  {
    class ReflectionBase;

    class VFunctionBase : public VField {

    public:
        VFunctionBase(const std::string& FuncName, std::vector<std::string> PropAttrs = {}, MetaMap PropDatas = {}) : VField(std::move(FuncName), std::move(PropAttrs), std::move(PropDatas)) {}

        EFunctionFlags GetFlags() const { return Flags; }
        bool HasFlag(EFunctionFlags b) const { return VulcanCore::HasFlag(Flags,b);}
        
        virtual const std::type_info& GetReturnType() const = 0;
        virtual const std::vector<VFunctionParamInfo>& GetParameters() const = 0;

        virtual std::any Invoke(ReflectionBase* Instance, const std::vector<std::any>& Args) = 0;
        virtual void InvokeRaw(ReflectionBase* instance, void** argsBuffer, void* retBuffer) = 0;

    protected:
        EFunctionFlags Flags = EFunctionFlags::EFunctionFlags_None;
    };
}
