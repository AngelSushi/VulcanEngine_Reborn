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
        /*Entry(const Entry&) = delete;
        Entry& operator=(const Entry&) = delete;

        Entry(Entry&&) = delete;
        Entry& operator=(Entry&&) = delete;
*/
    };
}
