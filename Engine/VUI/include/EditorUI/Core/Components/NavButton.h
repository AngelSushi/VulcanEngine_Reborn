#pragma once
#include <CoreAPI/precomp.h>
#include <EditorUI/Core/UIWidget.h>

#include <EditorUI/Core/Components/Button.h>

class NavButton : public Button {

public:
    void ApplyProps() override;
    void Initialized(WidgetApplication& WidgetApplication) override;
    


private:
    void OnHoverFunc();
    
    UINode SubMenuNode;
    std::string Action;
};
