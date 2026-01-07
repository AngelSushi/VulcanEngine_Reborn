#pragma once

#include <CoreAPI/precomp.h>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include <Reflection/VField.h>
#include <Reflection/ReflectionCore.h>

namespace VulcanCore {

    struct EnumEntry {
        std::string Name;
        int64_t Value;
    };
    
    class VEnum : public VField {
    public:
        //VEnum(const std::string& EnumName) : VField(EnumName) {}

        void AddEntry(const std::string& EntryName,int64 Value);
        const EnumEntry* FindByName(const std::string& EntryName) const;
        const EnumEntry* FindByValue(int64 Value) const;
        const std::string ToString(int64 Value) const;
        
        const std::vector<EnumEntry>& GetEntries() const { return Entries; }
        
    private:
        std::vector<EnumEntry> Entries;
        std::unordered_map<std::string,int64> NameToIndex;
        std::unordered_map<int64,int64> ValueToIndex;
        
    };
    
    template<typename E>
    VEnum& StaticEnum() {
        static_assert(std::is_enum_v<E>,"StaticEnum<E> : E must be an enum type");
        VEnum* enumPtr = ReflectionCore::Instance().Find(typeid(E));

        if (!enumPtr) {
            throw std::runtime_error("StaticEnum: Enum not registered");
        }

        return *enumPtr;
    }

    template<typename E>
    std::string EnumToString(E value) {
        return StaticEnum<E>().ToString(static_cast<int64_t>(value));
    }
}
