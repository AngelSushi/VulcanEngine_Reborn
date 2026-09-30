 #include <EditorUI/Core/Slot/ButtonSlot.h>


 void ButtonSlot::ApplyProps(UINode& Node) {
     HorizontalAlignment = ToEnumHorizontal(Node.TryPropValue("horizontalAlignment").Get<std::string>());
     VerticalAlignment = ToEnumVertical(Node.TryPropValue("verticalAlignment").Get<std::string>());
     SlotPadding = Node.TryPropValue("padding").Get<Padding>();
 }

 bool ButtonSlot::UseFloatingLayout() const {
     return false;
 }

 Clay_Sizing ButtonSlot::ComputeSizing() const {
     Clay_SizingAxis Width = HorizontalAlignment == EHorizontalAlignment::Fill ? CLAY_SIZING_GROW() : CLAY_SIZING_FIT();
     Clay_SizingAxis Height = VerticalAlignment == EVerticalAlignment::Fill ? CLAY_SIZING_GROW() : CLAY_SIZING_FIT();
     
     return Clay_Sizing { Width,Height };
 }

 Clay_TextAlignment ButtonSlot::ComputeAlignment() const {
     return HorizontalAlignment == EHorizontalAlignment::Left ? CLAY_TEXT_ALIGN_LEFT :
            HorizontalAlignment == EHorizontalAlignment::Center ? CLAY_TEXT_ALIGN_CENTER :
            HorizontalAlignment == EHorizontalAlignment::Right ? CLAY_TEXT_ALIGN_RIGHT :
            CLAY_TEXT_ALIGN_LEFT;
 }

// Kinda useless to have it now, cause button child can't have any children. We need to find an other way without implemting it here, but for now we keep it here
 Clay_ChildAlignment ButtonSlot::ComputeChildAlignment() const {
     return { 
         HorizontalAlignment == EHorizontalAlignment::Left ? CLAY_ALIGN_X_LEFT :
         HorizontalAlignment == EHorizontalAlignment::Center ? CLAY_ALIGN_X_CENTER :
         HorizontalAlignment == EHorizontalAlignment::Right ? CLAY_ALIGN_X_RIGHT :
         CLAY_ALIGN_X_LEFT,
         
         VerticalAlignment == EVerticalAlignment::Top ? CLAY_ALIGN_Y_TOP :
         VerticalAlignment == EVerticalAlignment::Center ? CLAY_ALIGN_Y_CENTER :
         VerticalAlignment == EVerticalAlignment::Bottom ? CLAY_ALIGN_Y_BOTTOM :
         CLAY_ALIGN_Y_TOP
     };
 }


 Padding ButtonSlot::GetSlotPadding() const {
     return SlotPadding;
 }
