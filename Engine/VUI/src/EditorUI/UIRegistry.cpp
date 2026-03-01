#include <EditorUI/UIRegistry.h>

void UIRegistry::Initialize() {
    // Here we try to find the base class for all UI elements.
}

void UIRegistry::BuildRegistry() {

    // Here we build the registry of all UI elements.
    
}

bool UIRegistry::Has(const std::string& Key) const {
    return Types.find(Key) != Types.end();
}

UIRegisteredType UIRegistry::Find(const std::string& Key) const {
    auto It = Types.find(Key);
    return It != Types.end() ? It->second : UIRegisteredType();
}
