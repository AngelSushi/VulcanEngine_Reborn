#include <EditorUI/Core/UIRegistry.h>


void UIRegistry::AddEntry(std::string Key, UIRegisteredType Type) {
    Types[std::move(Key)] = std::move(Type);
}

bool UIRegistry::Has(const std::string& Key) const {
    return Types.find(Key) != Types.end();
}

UIRegisteredType UIRegistry::Find(const std::string& Key) const {
    auto It = Types.find(Key);
    return It != Types.end() ? It->second : UIRegisteredType();
}
