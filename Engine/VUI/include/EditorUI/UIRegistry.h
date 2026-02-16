#pragma once
#include <CoreAPI/precomp.h>


class UIWidget;
struct UIPropSchema;

struct UIRegistryType {
    // std::function maybe not work on certain sdk
    std::function<std::unique_ptr<UIWidget>()> Factory;
    std::vector<UIPropSchema> Schemas;
};

class UIRegistry {

public:
    static UIRegistry& Create() {
        static UIRegistry registry;
        return registry;
    }
    
    void Initialize();

    void Register(const std::string& InKey, UIRegistryType InType);
    bool Unregister(const std::string& InKey);

    const UIRegistryType* Find(const std::string& InKey) const;
private:
    // Use this for after when the full system of object/class has been set
    //std::unordered_map<std::string,VulcanCore::VClass*> RegisteredClasses;
    //VulcanCore::VClass* TreeClass;

    std::unordered_map<std::string,UIRegistryType> Registry;
};