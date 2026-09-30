#pragma once
#include <CoreAPI/precomp.h>

#include "UIPanelWidget.h"


class VUI_API UIContentWidget : public UIPanelWidget {

public:

    bool CanHaveMultipleChildren() const override;
    UIWidget* GetContent() const;
    
    
protected:
};
