#pragma once
#include <string>
#include <vector>
#include <fmt/core.h>

#include "IRequestRenderer.h"
#include "UIUtils.h"

namespace VUI {
    
    class ImportAssetRenderer : public IRequestRenderer {
    public:
        void Render(const UIRequest& InRequest) override {
            
            auto& data = *std::get<std::unique_ptr<ImportData>>(InRequest.Data);
            
            bool open = true;
            ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_Once);
            if (ImGui::Begin("Import Settings", &open,ImGuiWindowFlags_NoResize)) {

                if (ImGui::IsWindowAppearing()) {
                    BuildPropertyCategories(data);
                }

                for (auto& entry : Entries) {
                    ImGui::SeparatorText(entry.CategoryName.c_str());
                    for (auto& option : entry.Options) {
                        ImGui::Spacing();
                        ImGui::Dummy({5,0});
                        ImGui::SameLine();
                        ImGui::Text("%s", option.c_str());
                        ImGui::SameLine();
                        ImGui::Dummy(ImVec2(5, 0)); 
                        ImGui::SameLine();

                        // Why static struct et pas GetStruct comme GetClass() ? 
                        /*auto propBase = data.StaticStruct().Find(option);
                        bool changed = false;

                        if (auto* propArray = dynamic_cast<VulcanCore::ArrayProperty*>(propBase)) {
                            int& index = CombosSelection[propArray];
                            UIProperty::DrawArrayProperty(&data,propArray,index,changed);
                        }
                        else {
                            UIProperty::DrawStructProperty(&data,data.StaticStruct().find_property(option),changed);
                        }
                          */  
                    }

                    ImGui::Spacing();
                }

                ImGui::End();
            }
            
        }

    private:
        struct ImportEntry {
            std::string CategoryName;
            std::vector<std::string> Options;
        };

        void BuildPropertyCategories(const ImportData& data) {
            /*for (auto& prop : data.StaticStruct().GetProperties()) {
                std::string category = std::get<std::string>(prop->FindMeta("Category")); // Check if std::get doees not crash if not std::string
                
                auto it = std::find_if(Entries.begin(), Entries.end(), [&](const ImportEntry& InEntry) {
                    return InEntry.CategoryName == category;
                });

                if (it != Entries.end()) {
                    it->Options.push_back(prop->GetName());
                }
                else {
                    ImportEntry entry;
                    entry.CategoryName = category;
                    entry.Options.push_back(prop->GetName());
                    Entries.push_back(std::move(entry));
                }
            }*/
        }
        
        std::vector<ImportEntry> Entries;
        //std::unordered_map<VulcanCore::VPropertyBase*, int> CombosSelection;
        
    };
}
