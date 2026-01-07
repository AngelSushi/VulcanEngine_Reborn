#pragma once
#include <string>
#include "Entry.h"
#include <Reflection/Property/VProperty.h>

#include <ComboEntry.vht.h>

namespace VUI {

    VCLASS()
    class ComboEntry : public Entry {
        VCLASS_BODY()
        
    public:
        ComboEntry() = default;
        
        VPROPERTY(meta=[type=[Selectable,Text], type_func=ResolvePropertyWidgetType])
        std::string EntryName;

        VFUNCTION()
        std::string ResolvePropertyWidgetType(ReflectionBase* Obj, VulcanCore::VProperty* Prop, const std::vector<std::string>& Types);

    protected:
        ComboEntry(std::string InName) : EntryName(std::move(InName)) {}
        
        
    };
}
