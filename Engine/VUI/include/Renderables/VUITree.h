#pragma once

#include "Layout.h"
#include "UIUtils.h"
#include "VUIRenderable.h"
#include "providers/ITreeIconProvider.h"

namespace VUI {

    class VUITree : public VUIRenderable {
    public:
        void Render(const VUIElement& e,const UILayout& InParent) override;

    private:
        void RenderTree(TreeEntry& InRoot, ITreeIconProvider* InProvider,const UILayout& InLayout, const VUIElement& InElement);
        void DeselectAll(TreeEntry& Root);

        void BuildPopup(const TreeEntry& InChild,const VUIElement& InElement,const ImVec2& Position);

        UIDragDrop::DragDropPayload dragdrop{};
    };
}
