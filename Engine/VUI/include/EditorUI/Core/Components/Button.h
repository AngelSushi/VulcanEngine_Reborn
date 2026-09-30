#pragma once
#include <CoreAPI/precomp.h>

#include <EditorUI/Core/UIWidget.h>

#include "CoreAPI/VTexture.h"
#include "EditorUI/Core/Panels/UIContentWidget.h"

class Button : public UIContentWidget {

public:
    std::unique_ptr<UISlot> GetSlotClass() override;

    void ApplyProps() override;
    
    Clay_ElementDeclaration Build() override;

private:
    // Un pointeur d'un VTexture, is it worth ?  
   VTexture* NormalImage = nullptr;

    
};
