#pragma once
#include <CoreAPI/precomp.h>

#include <EditorUI/Core/UIValue.h>

// Delete by prop system later, this is just a temporary struct to represent the type of a property, we may need to replace it later.
enum EPropType
{
    Bool = 0,
    Int = 1,
    Float = 2,
    String = 3,
    Color = 4,
    Vec2 = 5,
    Array = 6,
    Object = 7
};

struct UIPropSchema {
    std::string Name;
    EPropType Type;
    UIValue DefaultValue;
    std::function<bool(const UIValue&)> Validator; // std::function can not work on certain sdk, we may need to replace it later.
};

bool CheckType(UIValue Value,EPropType Type);
void ApplyDefaultSchemas(std::unordered_map<std::string,UIValue>& Properties,const std::vector<UIPropSchema>& Schemas);