#pragma once 
#include <string>
#include <Types/Assets/UIAsset.h>

#include "Entries/TreeEntry.h"
#include "Reflection/Property/VArrayProperty.h"


namespace UIDragDrop {
    
    struct DragDropPayload {
        VUI::TreeEntry* InEntry;
        VUI::TreeEntry* OutEntry;
    };
    
    void MakeSource(const VUI::VUIElement& Element, const void* InData, size_t InLength,VUI::TreeEntry* InEntry);
    DragDropPayload* Accept(const std::string& InPayloadType);

    void MakeTarget(const VUI::VUIElement& Element,VUI::TreeEntry* Target);
}

namespace UIPopup {
    void ContextMenu(const std::string& Id, std::function<void()> InCallback);
}

namespace UIProperty {
    void DrawClassProperty(VulcanCore::ReflectionBase* ClassBase,VulcanCore::VProperty* Property,bool& OutChanged);
    void DrawStructProperty(void* Instance,VulcanCore::VProperty* Property,bool& OutChanged);
    void DrawArrayProperty(void* Instance,VulcanCore::VArrayProperty* Property,int& SelectedIndex,bool& OutChanged);
}
