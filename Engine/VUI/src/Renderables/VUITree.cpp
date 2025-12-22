
    #include "Renderables/VUITree.h"


    #include "IRegistry.h"
    #include "Layout.h"
    #include "UIUtils.h"
#include "VCast.h"
#include "VUIHelper.h"

    namespace VUI {
        
        void VUITree::Render( const VUIElement& e,const UILayout& InParent) {
            auto bindMethod = VulcanEngine::BindingRegistry.FindIf([&](const Binding& b){
                    return b.GetName() == e.Bind;
            });

            if (!bindMethod) return;
 
            auto& treeData = bindMethod->InvokeAs<TreeEntry>();
            
            auto providerName = VUIHelper::json_or<std::string>(e.Properties, "provider", "");
            auto provider = VulcanEngine::TreeIconProviderRegistry.FindIf([&](const ITreeIconProvider& p){
                return p.GetName() == providerName;
            });

            auto gridLayout = UILayout::ParseLayout(e.Properties,ImGui::GetWindowSize());
            bool border = VUIHelper::json_or<bool>(e.Properties,"border",false);

            if (border) {
                ImGui::GetWindowDrawList()->AddRect(ImGui::GetCursorScreenPos(), { ImGui::GetCursorScreenPos().x + gridLayout.size.x , ImGui::GetCursorScreenPos().y + gridLayout.size.y }, IM_COL32(255,0,0,255));
            }

            ImGui::SetCursorPos({ImGui::GetCursorPos().x + gridLayout.margin[3],ImGui::GetCursorPos().y + gridLayout.margin[0]});
            ImGui::BeginGroup();
            RenderTree(treeData, provider,gridLayout,e);
            
            ImGui::EndGroup();

            if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                DeselectAll(treeData);
            }
        }

        void VUITree::RenderTree(TreeEntry& InRoot,ITreeIconProvider* InProvider,const UILayout& InLayout, const VUIElement& InElement) {
            ImTextureID texID = nullptr;

            if (InProvider) {
                try {
                    auto tex = InProvider->GetIconForEntry(InRoot);
                    texID = tex->GetTexture();
                }
                catch (...) {}
            }
            
            if (InRoot.IsDirectory) {
                auto cursorPos = ImGui::GetCursorPos();
                
                if (texID != nullptr) {
                    ImGui::Image(texID,{22,22});
                    cursorPos = { cursorPos.x + 30, cursorPos.y - 3};
                }
                
                ImGui::SetCursorPos(cursorPos);

                std::string nodeLabel = "##" + InRoot.EntryName;

                auto textPos = ImGui::GetCursorPos();
                ImGui::SetCursorPos({textPos.x + 30,textPos.y - 3});
                ImGui::Text("%s", InRoot.EntryName.c_str());
                BuildPopup(InRoot,InElement,textPos);
                
                ImGui::SetCursorPos(textPos);
                UIDragDrop::MakeTarget(InElement,&InRoot);
                if (ImGui::TreeNode(nodeLabel.c_str())) {
                    for (auto& child : InRoot.Children) {
                        if (child.IsDirectory) {
                            RenderTree(child, InProvider,InLayout,InElement);
                        }
                        else {
                            auto childCursorPos = ImGui::GetCursorPos();

                            if (InProvider) {
                                auto childTex = InProvider->GetIconForEntry(child);
                                ImTextureID childTexID = childTex->GetTexture();

                                ImGui::Image(childTexID,{22,22});
                                childCursorPos = { childCursorPos.x + 30, childCursorPos.y - 6};
                            }
                            
                            ImGui::SetCursorPos(childCursorPos);

                            if (!child.IsDirty) {
                                if (ImGui::Selectable(child.EntryName.c_str(),&child.IsSelected)) {
                                    if (!ImGui::GetIO().KeyCtrl) {
                                        DeselectAll(child.Root());
                                        child.SetSelected(!child.IsSelected);
                                    }
                                }
                                UIDragDrop::MakeTarget(InElement,&InRoot);
                                BuildPopup(child,InElement,childCursorPos);

                                UIDragDrop::DragDropPayload* ptr = &dragdrop;
                                MakeSource(InElement, &ptr, sizeof(ptr),&child);
                            }
                            else {
                                fmt::print("Skipping dirty child: {}\n", child.EntryName);
                            }
                            
                        }
                    }
                    
                    ImGui::TreePop();
                }
            }
            
        }

        void VUITree::BuildPopup(const TreeEntry& InChild,const VUIElement& InElement,const ImVec2& InPosition) {
            if (InElement.Properties.contains("popup")) {
                auto popup = InElement.Properties["popup"];

                if (!popup.is_null()) {
                    std::string popupID = "RightClickMenu##" + std::any_cast<std::string>(InChild.EntryName);
                    
                    UIPopup::ContextMenu(popupID,[&popup,&InChild,&InPosition](){
                        for (auto action : popup["items"]) {
                            auto actionLabel = VUIHelper::json_or<std::string>(action,"label","");
                            auto actionName = VUIHelper::json_or<std::string>(action,"action","");
                            auto submenu = VUIHelper::json_or<std::string>(action,"submenu","");

                            auto menuActionMethod = VulcanEngine::BindingRegistry.FindIf([&actionName](const Binding& b){
                                return b.GetName() == actionName;
                            });
                            
                            if (submenu.empty()) {
                                if (ImGui::MenuItem(actionLabel.c_str())) {
                                    if (menuActionMethod) {
                                        menuActionMethod->Invoke(std::any_cast<std::string>(InChild.Payload),InPosition);
                                    }
                                }
                            }
                            else {
                                
                                auto submenuActionMethod = VulcanEngine::BindingRegistry.FindIf([&submenu](const Binding& b){
                                     return b.GetName() == submenu;
                                 });

                                auto subMenuActions = submenuActionMethod ? submenuActionMethod->InvokeAs<std::vector<std::string>>() : std::vector<std::string>{};

                                auto cursorPos = ImGui::GetCursorPos();

                                ImGui::SetCursorPos({cursorPos.x + 30, cursorPos.y});
                                if (ImGui::BeginMenu(actionLabel.c_str())) {
                                    for (auto& subAction : subMenuActions) {
                                        if (ImGui::MenuItem(subAction.c_str())) {
                                            if (menuActionMethod) {
                                                menuActionMethod->Invoke(std::any_cast<std::string>(InChild.Payload),subAction);
                                            }
                                        }

                                        ImGui::Separator();
                                    }

                                    ImGui::EndMenu();
                                }
                            }
                            
                            ImGui::Separator();
                        }
                    }); 
                }
            }
        }
        
        void VUITree::DeselectAll(TreeEntry& Root) {
            for (auto& child : Root.Children) {
                child.SetSelected(false);
                DeselectAll(child);
            }
        }
    }
