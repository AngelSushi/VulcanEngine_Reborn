#include <Entries/ComboEntry.h>

#include "Entries/ComboBoolEntry.h"

namespace VUI {
    std::string ComboEntry::ResolvePropertyWidgetType(ReflectionBase* Obj, VulcanCore::VPropertyBase* Prop,const std::vector<std::string>& Types) {
        if (Types.size() != 1) {
            return Obj->GetClass().IsA<ComboBoolEntry>() ? Types[1] : Types[0];
        }

        return Types[0];
    }
}
