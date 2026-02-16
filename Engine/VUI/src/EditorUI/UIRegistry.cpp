#include <EditorUI/UIRegistry.h>

void UIRegistry::Initialize() {
    // Here we try to find the base class for all UI elements.
}

void UIRegistry::Register(const std::string& InKey, UIRegistryType InType) {
    Registry[InKey] = std::move(InType);
}

bool UIRegistry::Unregister(const std::string& InKey) {
    return Registry.erase(InKey) > 0;
}

const UIRegistryType* UIRegistry::Find(const std::string& InKey) const {
    auto it = Registry.find(InKey);

    if (it == Registry.end()) {
        return nullptr;
    }

    return &it->second;
}

