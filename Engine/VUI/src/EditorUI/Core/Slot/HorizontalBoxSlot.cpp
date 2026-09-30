 #include <EditorUI/Core/Slot/HorizontalBoxSlot.h>


 void HorizontalBoxSlot::ApplyProps(UINode& Node) {
     HorizontalAlignment = ToEnumHorizontal(Node.TryPropValue("horizontalAlignment").Get<std::string>());
     VerticalAlignment = ToEnumVertical(Node.TryPropValue("verticalAlignment").Get<std::string>());
 }

 bool HorizontalBoxSlot::UseFloatingLayout() const {
     return false;
 }

 Clay_Sizing HorizontalBoxSlot::ComputeSizing() const {
     Clay_SizingAxis Width = HorizontalAlignment == EHorizontalAlignment::Fill ? CLAY_SIZING_GROW() : CLAY_SIZING_FIT();
     Clay_SizingAxis Height = VerticalAlignment == EVerticalAlignment::Fill ? CLAY_SIZING_GROW() : CLAY_SIZING_FIT();
     
     return Clay_Sizing { Width,Height };
 }

// Done it mainly for button, need to check if its fit with every container 
 Clay_ChildAlignment HorizontalBoxSlot::ComputeChildAlignment() const {
     return { 
         CLAY_ALIGN_X_LEFT,
         CLAY_ALIGN_Y_TOP
     };

 }
