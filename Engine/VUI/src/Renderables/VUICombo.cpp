
#include <Renderables/VUICombo.h>

#include "Binding.h"
#include "IRegistry.h"
#include "Layout.h"
#include "TVector.h"
#include "UIUtils.h"
#include "VCast.h"
#include "VUIHelper.h"
#include "Entries/ComboBoolEntry.h"
#include "Systems/EditorSystem.h"

namespace VUI {
    
    void VUICombo::Render( const VUIElement& e,const UILayout& InParent) {
        UILayout itemLayout = UILayout::ParseLayout(e.Properties,{InParent.size.x,InParent.size.y},InParent);
        auto label = VUIHelper::json_or<std::string>(e.Properties,"label","");
        
        std::string preview{};

        auto bindName = VUIHelper::json_or<std::string>(e.Properties,"bind","");
        auto bindMethod = VulcanEngine::BindingRegistry.FindIf([&bindName](const Binding& b) {
            return b.GetName() == bindName;
        });

        if (bindMethod) {
            auto& objects = bindMethod->InvokeAs<VulcanEngine::TVector<std::unique_ptr<VulcanCore::ReflectionBase>>>();
            std::string comboLabel = "##" + label;

            auto hasPreview = VUIHelper::json_or<bool>(e.Properties,"hasPreview",false);

            if (!hasPreview) {
                if (Selected.first < objects.size()) {
                    auto* obj = objects[Selected.first].get();
                    auto* prop = obj->GetClass().find_property(Selected.second);

                    if (obj && prop) {
                        preview = *prop->GetTypedPtr<std::string>(obj);
                    }
                }
            }
            else if (hasPreview) {
                BuildPreview(objects,preview);
            }
            
            ImGui::SetNextItemWidth(itemLayout.size.x);
            if (ImGui::BeginCombo(comboLabel.c_str(), preview.c_str())) {
                for (size_t i = 0; i < objects.size(); ++i) {
                    auto obj = objects[i].get();
                    for (auto& prop : obj->GetClass().GetProperties()) {
                        bool changed = false;
                        UIProperty::DrawClassProperty(obj, prop.get(), changed);
                        ImGui::SameLine();
                    
                        if (changed) {
                            Selected.first = i;
                            Selected.second = prop->GetName();

                            auto onClicked = VUIHelper::json_or<std::string>(e.Properties,"onClicked","");
                            if (!onClicked.empty()) {
                                auto clickBind = VulcanEngine::BindingRegistry.FindIf([&onClicked](const Binding& b) {
                                    return b.GetName() == onClicked;
                                });
                            
                                if (clickBind) { // Fix this no GetAsAny method
                                   // clickBind->Invoke(prop->GetAsAny(obj));
                                } 
                            }
                        }
                    }
                    ImGui::NewLine();
                }

                ImGui::EndCombo();
                
            }
        }
    }

    void VUICombo::BuildPreview(VulcanEngine::TVector<std::unique_ptr<VulcanCore::ReflectionBase>>& Objects,std::string& OutPreview) {
        OutPreview.clear();

        for (auto& obj : Objects) {
            if (obj->GetClass().IsA<ComboBoolEntry>()) {
                if (ComboBoolEntry* entry = VulcanCore::Cast<ComboBoolEntry>(obj.get())) {
                    if (entry->IsEnabled) {
                        OutPreview += entry->EntryName + " - ";
                    }
                }
            }
            else {
                VLOG_WARN(EditorUI, "VUICombo::BuildPreview: Entry type must be ComboBoolEntry to build preview.");
            }
        }
    }
}
