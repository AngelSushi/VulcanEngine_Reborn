#pragma once
#include <CoreAPI/precomp.h>

#include "UIPropSchema.h"
#include "UIWidget.h"

struct UIRegisteredType
{
    std::string Name = "EMPTY_STRING"; // make for future custom string class that has EMPTY_STRING has null value
    std::vector<UIPropSchema> Schemas;
    std::function<std::unique_ptr<UIWidget>()> Create;

    UIRegisteredType() = default;
    UIRegisteredType(std::string InName, std::vector<UIPropSchema> InSchemas, std::function<std::unique_ptr<UIWidget>()> InCreate): Name(std::move(InName)), Schemas(std::move(InSchemas)), Create(std::move(InCreate)) {}

    bool IsNull() {
        return Name == "EMPTY_STRING";
    }
};

class UIRegistry {

public:
    void Initialize();

    void BuildRegistry();

    bool Has(const std::string& Key) const;
    UIRegisteredType Find(const std::string& Key) const;
    
private:
    std::unordered_map<std::string,UIRegisteredType> Types;

    VulcanCore::VClass* TreeClass;
};