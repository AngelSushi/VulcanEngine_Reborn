#include "UIUtils.h"

#include "IRegistry.h"
#include "VCast.h"
#include "VUIHelper.h"
#include "World.h"
#include "Reflection/Property/VArrayProperty.h"
#include "Systems/EditorSystem.h"

void UIDragDrop::MakeSource(const VUI::VUIElement& Element, const void* InData, size_t InLength,VUI::TreeEntry* InEntry) {
    if (Element.Properties.contains("drag")) {
        nlohmann::json dragJson = Element.Properties["drag"];
        auto payloadType = VUI::VUIHelper::json_or<std::string>(dragJson,"type","");

        if (ImGui::BeginDragDropSource()) {
            ImGui::SetDragDropPayload(payloadType.c_str(), InData, InLength);
            ImGui::Text("Dragging %s", InEntry->EntryName);

            if (DragDropPayload* TestPayload = *static_cast<DragDropPayload* const*>(InData)) {
                TestPayload->InEntry = InEntry;
            }
        
            ImGui::EndDragDropSource();
        }
    }
}

void UIDragDrop::MakeTarget(const VUI::VUIElement& Element,VUI::TreeEntry* Target) {
    if (Element.Properties.contains("drop")) {
        nlohmann::json dropJSON = Element.Properties["drop"];
        auto acceptedTypes = VUI::VUIHelper::json_or<std::vector<std::string>>(dropJSON,"type",std::vector<std::string>{});
        for (auto& dropType : acceptedTypes) {
            if (auto dropped = Accept(dropType)) {
                auto onDropped  = VUI::VUIHelper::json_or<std::string>(dropJSON,"onDropped","");
                dropped->OutEntry = Target;

                auto droppedFunc = VulcanEngine::BindingRegistry.FindIf([&onDropped](const VUI::Binding& b) {
                    return b.GetName() == onDropped;
                });

                if (droppedFunc) {
                    droppedFunc->Invoke(*dropped); 
                }
            }
        }
    }
}

UIDragDrop::DragDropPayload* UIDragDrop::Accept(const std::string& InPayloadType) {
    DragDropPayload* drag_drop = nullptr;

    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(InPayloadType.c_str())) {
            if (payload->DataSize == sizeof(drag_drop)) {
                drag_drop = *static_cast<DragDropPayload* const*>(payload->Data);
            }
        }

        ImGui::EndDragDropTarget();
    }
    return drag_drop;
}

void UIPopup::ContextMenu(const std::string& Id, std::function<void()> InCallback) {
    if (ImGui::BeginPopupContextItem(Id.c_str())) {
        InCallback();
        ImGui::EndPopup();
    }
}

void UIProperty::DrawClassProperty(VulcanCore::ReflectionBase* ClassBase,VulcanCore::VProperty* Property,bool& OutChanged) {
    if (!Property) {
        VLOG_WARN(EditorUI, "UIProperty::DrawProperty The property you are trying to draw is null");
        return;
    }

    /*std::string bypassMeta{};
    std::string metaType = std::get<std::string>(Property->FindMeta("type"));

    if (!metaType.empty()) {
        std::vector<std::string> types;

        auto metaType = Property->FindMeta("type");
        if (auto* v = std::get_if<std::vector<std::string>>(&metaType)) {
            types = *v;
        }
        
        auto typeFuncName = std::get<std::string>(Property->FindMeta("type_func"));
        if (auto Fn = ClassBase->GetClass().find_function(typeFuncName)) {
            bypassMeta = std::any_cast<std::string>(Fn->Invoke(ClassBase, { ClassBase,Property,types}));
        }
    }
    
    std::string label = "##" + Property->GetName() + "##obj_" + std::to_string(reinterpret_cast<uintptr_t>(ClassBase)) + "_prop_" + std::to_string(reinterpret_cast<uintptr_t>(Property));
    
    ImGui::SetWindowFontScale(0.95f);
    ImGui::SetNextItemWidth(250.0f);

    if (Property->Type == &typeid(std::string)) {
        if (!Property->FindAttribute("Selectable").empty() || bypassMeta == "Selectable") {
            OutChanged = ImGui::Selectable(Property->GetTypedPtr<std::string>(ClassBase)->c_str());
        }
        else if (!Property->FindAttribute("InputText").empty() || bypassMeta == "InputText") {
            std::string value = *Property->GetTypedPtr<std::string>(ClassBase);
            char buffer[256];
            std::strncpy(buffer, value.c_str(), sizeof(buffer));
            buffer[sizeof(buffer) - 1] = '\0';

            if (ImGui::InputText(label.c_str(),buffer,sizeof(buffer))) {
                std::string newValue(buffer);
                Property->Set(ClassBase, newValue);
                OutChanged = true;
            }
        }
        else {
            ImGui::Text("%s",Property->GetTypedPtr<std::string>(ClassBase)->c_str());
        }
    }
    else if (Property->Type == &typeid(bool)) {
        bool& val = *Property->GetTypedPtr<bool>(ClassBase);
        if (ImGui::Checkbox(label.c_str(), &val)) {
            OutChanged = true;
        }
    }
    else if (Property->Type == &typeid(bool*)) {
        bool* val = *Property->GetTypedPtr<bool*>(ClassBase);
        if (ImGui::Checkbox(label.c_str(), val)) {
            OutChanged = true;
        }
    }
    else if (Property->Type == &typeid(float)) {
        float val = *Property->GetTypedPtr<float>(ClassBase);
        if (ImGui::DragFloat(label.c_str(), &val)) {
            Property->Set(ClassBase, val);
            OutChanged = true;
        }
    }
    else if (Property->Type == &typeid(VMath::Vector3i)) {
        auto vec = *Property->GetTypedPtr<VMath::Vector3i>(ClassBase);
        int vecValues[3] = {vec.x,vec.y,vec.z};

        if (ImGui::DragInt3(label.c_str(),vecValues)) {
            vec = VMath::Vector3i{ vecValues[0],vecValues[1],vecValues[2] };
            Property->Set(ClassBase, vec);
            OutChanged = true;
        }
    }
    else if (Property->Type == &typeid(VMath::Vector3f)) {
        auto vec = *Property->GetTypedPtr<VMath::Vector3f>(ClassBase);
        float vecValues[3] = {vec.x,vec.y,vec.z};
          
        if (ImGui::DragFloat3(label.c_str(),vecValues)) {
            vec = VMath::Vector3f{ vecValues[0],vecValues[1],vecValues[2] };
            Property->Set(ClassBase, vec);
            OutChanged = true;
        }
    }
    else if (Property->Type == &typeid(VMath::Vector3d)) {
        auto vec = *Property->GetTypedPtr<VMath::Vector3d>(ClassBase);
        double vecValues[3] = {vec.x,vec.y,vec.z};

        if (ImGui::DragScalarN(label.c_str(), ImGuiDataType_Double, vecValues, 3)) {
            vec = VMath::Vector3d{ vecValues[0],vecValues[1],vecValues[2] };
            Property->Set(ClassBase, vec);
            OutChanged = true;
        }
    }

    if (OutChanged) {
        std::string onChangeFunc = std::get<std::string>(Property->FindMeta("onchange_func"));
        
        if (!onChangeFunc.empty()) {
            auto funcName = std::get<std::string>(Property->FindMeta("onchange_func"));
            
            auto className = funcName.substr(0, funcName.find("::"));
            auto methodName = funcName.substr(funcName.find("::") + 2);

            auto* cl = static_cast<VulcanCore::VClass*>(VulcanCore::ReflectionCore::Instance().Find(className));
            auto func = cl->find_function(methodName);

            if (!func) {
                return;
            }
            // WARNING : The fonction must not have parameters
            
            if (!className.empty()) { // Object method
                if (func->HasFlag(VulcanCore::EFunctionFlags::EFunctionFlags_Static)) {
                    //staticFn->Invoke(nullptr, {});
                }
                else {  // object has a Instance() inside
                    if (auto* instanceFn = cl->find_function("Instance")) {
                        if (auto* instance = VulcanCore::Cast<VulcanCore::ReflectionBase>(instanceFn->Invoke(nullptr,{}))) {
                            func->Invoke(instance,{});
                        }
                    }
                }
            }
            else { // Self ReflectionBase class function
                func->Invoke(ClassBase,{});
            }
        }
    }
    
    ImGui::SetWindowFontScale(1.0f);*/
}

void UIProperty::DrawStructProperty(void* Instance, VulcanCore::VProperty* Property, bool& OutChanged) {
    if (!Property) {
        VLOG_WARN(EditorUI, "UIProperty::DrawProperty The property you are trying to draw is null");
        return;
    }
    
  /*  std::string label = "##" + Property->GetName() + "##obj_" + std::to_string(reinterpret_cast<uintptr_t>(Instance)) + "_prop_" + std::to_string(reinterpret_cast<uintptr_t>(Property));
    
    ImGui::SetWindowFontScale(0.95f);
    ImGui::SetNextItemWidth(250.0f);

    if (Property->Type == &typeid(std::string)) {
        if (!Property->FindAttribute("Selectable").empty()) {
            OutChanged = ImGui::Selectable(Property->GetTypedPtr<std::string>(Instance)->c_str());
        }
        else if (!Property->FindAttribute("InputText").empty()) {
            std::string value = *Property->GetTypedPtr<std::string>(Instance);
            char buffer[256];
            std::strncpy(buffer, value.c_str(), sizeof(buffer));
            buffer[sizeof(buffer) - 1] = '\0';

            if (ImGui::InputText(label.c_str(),buffer,sizeof(buffer))) {
                std::string newValue(buffer);
                Property->Set(Instance, newValue);
                OutChanged = true;
            }
        }
        else {
            ImGui::Text("%s",Property->GetTypedPtr<std::string>(Instance)->c_str());
        }
    }
    else if (Property->Type == &typeid(bool)) {
        bool& val = *Property->GetTypedPtr<bool>(Instance);
        if (ImGui::Checkbox(label.c_str(), &val)) {
            OutChanged = true;
        }
    }
    else if (Property->Type == &typeid(bool*)) {
        bool* val = *Property->GetTypedPtr<bool*>(Instance);
        if (ImGui::Checkbox(label.c_str(), val)) {
            OutChanged = true;
        }
    }
    else if (Property->Type == &typeid(float)) {
        float val = *Property->GetTypedPtr<float>(Instance);
        if (ImGui::DragFloat(label.c_str(), &val)) {
            Property->Set(Instance, val);
            OutChanged = true;
        }
    }
    else if (Property->Type == &typeid(VMath::Vector3i)) {
        auto vec = *Property->GetTypedPtr<VMath::Vector3i>(Instance);
        int vecValues[3] = {vec.x,vec.y,vec.z};

        if (ImGui::DragInt3(label.c_str(),vecValues)) {
            vec = VMath::Vector3i{ vecValues[0],vecValues[1],vecValues[2] };
            Property->Set(Instance, vec);
            OutChanged = true;
        }
    }
    else if (Property->Type == &typeid(VMath::Vector3f)) {
        auto vec = *Property->GetTypedPtr<VMath::Vector3f>(Instance);
        float vecValues[3] = {vec.x,vec.y,vec.z};
          
        if (ImGui::DragFloat3(label.c_str(),vecValues)) {
            vec = VMath::Vector3f{ vecValues[0],vecValues[1],vecValues[2] };
            Property->Set(Instance, vec);
            OutChanged = true;
        }
    }
    else if (Property->Type == &typeid(VMath::Vector3d)) {
        auto vec = *Property->GetTypedPtr<VMath::Vector3d>(Instance);
        double vecValues[3] = {vec.x,vec.y,vec.z};

        if (ImGui::DragScalarN(label.c_str(), ImGuiDataType_Double, vecValues, 3)) {
            vec = VMath::Vector3d{ vecValues[0],vecValues[1],vecValues[2] };
            Property->Set(Instance, vec);
            OutChanged = true;
        }
    }

    if (OutChanged) {
        std::string onChangeFunc = std::get<std::string>(Property->FindMeta("onchange_func"));
        
        if (!onChangeFunc.empty()) {
            auto funcName = std::get<std::string>(Property->FindMeta("onchange_func"));
            
            auto className = funcName.substr(0, funcName.find("::"));
            auto methodName = funcName.substr(funcName.find("::") + 2);

            auto* cl = static_cast<VulcanCore::VClass*>(VulcanCore::ReflectionCore::Instance().Find(className));
            auto func = cl->find_function(methodName);

            if (!func) {
                return;
            }
            // WARNING : The fonction must not have parameters
            
            if (!className.empty()) { // Object method
                if (func->HasFlag(VulcanCore::EFunctionFlags::EFunctionFlags_Static)) {
                    //staticFn->Invoke(nullptr, {});
                }
                else {  // object has a Instance() inside
                    if (auto* instanceFn = cl->find_function("Instance")) {
                        if (auto* instance = VulcanCore::Cast<VulcanCore::ReflectionBase>(instanceFn->Invoke(nullptr,{}))) {
                            func->Invoke(instance,{});
                        }
                    }
                }
            }
        }
    }
    
    ImGui::SetWindowFontScale(1.0f);*/
}

void UIProperty::DrawArrayProperty(void* Instance, VulcanCore::VArrayProperty* ArrayProp,int& SelectedIndex, bool& OutChanged) {
    if (!ArrayProp) {
        VLOG_WARN(EditorUI, "UIProperty::DrawArrayProperty The property you are trying to draw is not an array");
        return;
    }

    std::string label = "##" + ArrayProp->GetName() + "##obj_" + std::to_string(reinterpret_cast<uintptr_t>(Instance)) + "_prop_" + std::to_string(reinterpret_cast<uintptr_t>(ArrayProp));

    size_t arraySize = ArrayProp->size(Instance);
    if (arraySize == 0) {
        ImGui::TextDisabled("(empty)");
        return;
    }

    SelectedIndex = VMath::Clamp(SelectedIndex, 0, arraySize - 1);
    std::string currentText;

    if (ArrayProp->Inner->Type == &typeid(std::string)) {
        void* elementPtr = ArrayProp->GetElement(Instance, (size_t)SelectedIndex);
        currentText = *static_cast<std::string*>(elementPtr);
    }
    else {
        currentText = fmt::format("Element {}",SelectedIndex);
    }

    ImGui::SetWindowFontScale(0.95f);
    ImGui::SetNextItemWidth(250.0f);
    if (ImGui::BeginCombo(label.c_str(),currentText.c_str())){
        for (size_t i = 0; i < arraySize; ++i) {
            void* elementPtr = ArrayProp->GetElement(Instance, (size_t)i);
            std::string value = ArrayProp->Inner->Type == &typeid(std::string) ? *static_cast<std::string*>(elementPtr) : fmt::format("Element {}", i);

            bool isSelected = (i == (size_t)SelectedIndex);
            if (ImGui::Selectable(value.c_str(), isSelected)) {
                SelectedIndex = i;
                OutChanged = true;
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    
}
