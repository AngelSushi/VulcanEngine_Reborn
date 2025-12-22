#pragma once
#include <memory>
#include <string>
#include <Reflection/VField.h>
#include <Reflection/Property/VProperty.h>

#include "ReflectionCore.h"


namespace VulcanCore {

    // Base of all reflected structures (e.g. class, struct, functions, ...)
    // Its only just a block of memory to store datas
    class VStruct : public VField {

    public:

        // Used for static construction (StaticStruct())
        VStruct(uint32 ParamSize,uint32 Alignment);

        // Used for instance construction
        VStruct(VStruct* InSuperStruct,uint32 ParamsSize, uint32 Alignment);
        
        void BuildMemoryLayout();
    private:
        uint32 MinAlignement;
    };

    
    
    class VScriptStruct : public VStruct {

    public:
        VScriptStruct(const std::string& StructName, std::string& InFullName,size_t StructSize) : VField(std::move(StructName)),FullName(std::move(InFullName)), Size(StructSize) {}

        size_t GetSize() const { return Size; }
        
        VScriptStruct* Parent = nullptr;
        
    private:
        std::string FullName;
        size_t Size = 0;
    };

    template<typename T>
    VScriptStruct& StaticStruct() {
        VScriptStruct* structPtr = ReflectionCore::Instance().Find(typeid(T));

        if (!structPtr) {
            throw std::runtime_error("StaticStruct: Struct not registered");
        }

        return *structPtr;
    }

}
