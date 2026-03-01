#include <EditorUI/UIPropSchema.h>
#include <EditorUI/UIValue.h>

void ApplyDefaultSchemas(std::unordered_map<std::string,UIValue>& Properties,const std::vector<UIPropSchema>& Schemas) {
    for (const UIPropSchema& Schema : Schemas) {
        if (!Properties.contains(Schema.Name)) {
            Properties[Schema.Name] = Schema.DefaultValue;
        }
    }

    for (const auto& Prop : Schemas) {
        
    }
}	