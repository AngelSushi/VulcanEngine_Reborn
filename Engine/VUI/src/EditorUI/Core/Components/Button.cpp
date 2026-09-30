
#include <EditorUI/Core/Components/Button.h>

#include "ResourceManager.h"
#include "CoreAPI/VCore.h"
#include "CoreAPI/VSurface.h"
#include "EditorUI/Core/Slot/ButtonSlot.h"
#include "EditorUI/Core/Slot/CanvasSlot.h"

std::unique_ptr<UISlot> Button::GetSlotClass() {
    return std::make_unique<ButtonSlot>();
}

void Button::ApplyProps() {
    UIContentWidget::ApplyProps();

    std::string WindowName = VCore::GetInstance().GetWindowByIndex(WindowIndex).GetTitle();
    std::string NormalImageName = Node.TryPropValue("normalImage").Get<std::string>();
    
    NormalImage = ResourceManager::Get().GetTextureByName(NormalImageName).get();
}

Clay_ElementDeclaration Button::Build() {
    Clay_ElementDeclaration Declaration = UIContentWidget::Build();

    if (auto* SlotBtn = dynamic_cast<ButtonSlot*>(GetContent()->GetSlot())) {
        Declaration.layout.padding = Clay_Padding(
            static_cast<uint16_t>(SlotBtn->GetSlotPadding().Left),
            static_cast<uint16_t>(SlotBtn->GetSlotPadding().Right),
            static_cast<uint16_t>(SlotBtn->GetSlotPadding().Top),
            static_cast<uint16_t>(SlotBtn->GetSlotPadding().Bottom));

        Declaration.layout.childAlignment = SlotBtn->ComputeChildAlignment();
    }

    Declaration.image.imageData = NormalImage;

    return Declaration;
}

