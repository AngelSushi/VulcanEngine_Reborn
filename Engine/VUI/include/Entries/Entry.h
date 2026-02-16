#pragma once
#include <Reflection/VObject.h>
#include <Reflection/VMacros.h>
#include <Entry.vht.h>

namespace VUI {

    VCLASS()
    class Entry : public VulcanCore::ReflectionBase {

        VCLASS_BODY()
    public:
        Entry() = default;

    };
}
