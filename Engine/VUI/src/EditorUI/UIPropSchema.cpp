#include <EditorUI/UIPropSchema.h>
#include <EditorUI/UIValue.h>

#include "LogSystem.h"
#include "Systems/EditorSystem.h"

bool CheckType(UIValue Value, EPropType Type) {
    switch (Type) {
        case EPropType::Bool:
            return Value.Is<bool>();
        case EPropType::Int:
            return Value.Is<int>();
        case EPropType::Float:
            return Value.Is<float>();
        case EPropType::String:
            return Value.Is<std::string>();
        case EPropType::Color:
            return Value.Is<std::string>(); // For simplicity, we use string to represent color, we may need to replace it later.
        case EPropType::Vec2:
            return Value.Is<std::string>(); // For simplicity, we use string to represent vec2, we may need to replace it later.
        case EPropType::Array:
            return Value.Is<std::string>(); // For simplicity, we use string to represent array, we may need to replace it later.
        case EPropType::Object:
            return Value.Is<std::string>(); // For simplicity, we use string to represent object, we may need to replace it later.
    }
}

void ApplyDefaultSchemas(std::unordered_map<std::string,UIValue>& Properties,const std::vector<UIPropSchema>& Schemas) {
    for (const UIPropSchema& Schema : Schemas) {
        if (!Properties.contains(Schema.Name)) {
            Properties[Schema.Name] = Schema.DefaultValue;
        }
    }

    for (const auto& Prop : Schemas) {
        auto it = Properties.find(Prop.Name);

        if (it == Properties.end())
            continue;

        if (!CheckType(it->second,Prop.Type)) {
            VLOG_WARN(EditorUI, "Property {} has invalid type, expected {}, but got {}", Prop.Name, static_cast<int>(Prop.Type), it->second.Value.index());
            it->second = Prop.DefaultValue;
            continue;
        }

        if (Prop.Validator && !Prop.Validator(it->second)) {
            VLOG_WARN(EditorUI, "Property {} failed validation, using default value", Prop.Name);
            it->second = Prop.DefaultValue;
        }
        
    }
}	