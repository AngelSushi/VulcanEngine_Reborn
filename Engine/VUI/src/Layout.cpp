
#include <Layout.h>

namespace VUI {
    AnchorLayout::AnchorLayout(AnchorType InAnchor) : Type(InAnchor) {}

    AnchorLayout AnchorLayout::FromString(const std::string_view& InAnchorStr) {
        if (InAnchorStr == "TopLeft") return AnchorLayout(TopLeft);
        if (InAnchorStr == "TopCenter") return AnchorLayout(TopCenter);
        if (InAnchorStr == "TopRight") return AnchorLayout(TopRight);
        if (InAnchorStr == "CenterLeft") return AnchorLayout(CenterLeft);
        if (InAnchorStr == "Center") return AnchorLayout(Center);
        if (InAnchorStr == "CenterRight") return AnchorLayout(CenterRight);
        if (InAnchorStr == "BottomLeft") return AnchorLayout(BottomLeft);
        if (InAnchorStr == "BottomCenter") return AnchorLayout(BottomCenter);
        if (InAnchorStr == "BottomRight") return AnchorLayout(BottomRight);

        return AnchorLayout(None);
    }

    std::string AnchorLayout::ToString() const {
        if (Type == TopLeft) return "TopLeft";
        if (Type == TopCenter) return "TopCenter";
        if (Type == TopRight) return "TopRight";
        if (Type == CenterLeft) return "CenterLeft";
        if (Type == Center) return "Center";
        if (Type == CenterRight) return "CenterRight";
        if (Type == BottomLeft) return "BottomLeft";
        if (Type == BottomCenter) return "BottomCenter";
        if (Type == BottomRight) return "BottomRight";

        return "None";
    }

    VMath::Vector2f AnchorLayout::ToVec() const {
        switch (Type) {
            case None: return VMath::Vector2f(0.f, 0.f);
            case TopLeft: return VMath::Vector2f(0.f, 0.f);
            case TopCenter: return VMath::Vector2f(0.5f, 0.f);
            case TopRight: return VMath::Vector2f(1.f, 0.f);
            case CenterLeft: return VMath::Vector2f(0.f, 0.5f);
            case Center: return VMath::Vector2f(0.5f, 0.5f);
            case CenterRight: return VMath::Vector2f(1.f, 0.5f);
            case BottomLeft: return VMath::Vector2f(0.f, 1.f);
            case BottomCenter: return VMath::Vector2f(0.5f, 1.f);
            case BottomRight: return VMath::Vector2f(1.f, 1.f);
        }

        return VMath::Vector2f(0.f, 0.f);
    }
}
