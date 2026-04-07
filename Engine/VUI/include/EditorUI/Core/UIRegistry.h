#pragma once
#include <CoreAPI/precomp.h>

#include "UIPropSchema.h"
#include "UIWidget.h"

struct UIRegisteredType
{
    std::vector<UIPropSchema> Schemas;
    std::function<std::unique_ptr<UIWidget>()> Create;
    
    bool IsNull() {
        return !Create;
    }
};

class UIRegistry {

public:
    static UIRegistry Create() {
        return UIRegistry();
    }

    void AddEntry(std::string Key,UIRegisteredType Type);

    bool Has(const std::string& Key) const;
    UIRegisteredType Find(const std::string& Key) const;
    
private:
    std::unordered_map<std::string,UIRegisteredType> Types;

    VulcanCore::VClass* TreeClass;
};