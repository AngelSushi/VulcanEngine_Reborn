#include <Reflection/VEnum.h>

namespace VulcanCore {
    
    void VEnum::AddEntry(const std::string& EntryName,int64_t Value) {
        Entries.push_back({ std::move(EntryName), Value });
        NameToIndex[Entries.back().Name] = Entries.size() - 1;
        ValueToIndex[Entries.back().Value] = Entries.size() - 1;
    }

    const EnumEntry* VEnum::FindByName(const std::string& EntryName) const {
        auto it = NameToIndex.find(EntryName);
        return it != NameToIndex.end() ? &Entries[it->second] : nullptr;
    }

    const EnumEntry* VEnum::FindByValue(int64_t Value) const {
        auto it = ValueToIndex.find(Value);
        return it != ValueToIndex.end() ? &Entries[it->second] : nullptr;
    }

    const std::string VEnum::ToString(int64_t Value) const {
        const EnumEntry* e = FindByValue(Value);
        return e ? e->Name : "Unknown";
    }
}
