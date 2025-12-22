#pragma once
#include <string>
#include <Vector2.h>
#include <VUIHelper.h>
#include <LogSystem.h>

namespace VUI {
    
    using namespace VMath;
    
    enum AnchorType {
        None,
        TopLeft,
        TopCenter,
        TopRight,
        CenterLeft,
        Center,
        CenterRight,
        BottomLeft,
        BottomCenter,
        BottomRight
    };
    
    struct AnchorLayout {
        AnchorLayout(AnchorType InAnchor);
        ~AnchorLayout() = default;

        static AnchorLayout FromString(const std::string_view& InAnchorStr);
        std::string ToString() const;
        VMath::Vector2f ToVec() const;
        
        void SetAnchor(AnchorType InAnchor) { Type = InAnchor; }

        float X() const { return ToVec().x; }
        float Y() const { return ToVec().y; }
        
        // operator ImVec2() const;
        operator ImVec2() const { 
            return ToVec();
        }
        
        AnchorType Type;
    };
    
    struct UILayout {
        
        using UIMargin = std::array<float,4>;

        UIMargin margin{};
        Vector2f spacing{};
        Vector2f size{};
        Vector2f position{};
        AnchorLayout anchor{ TopLeft };
        AnchorLayout childAnchor{ TopLeft };

        static UILayout ParseLayout(const nlohmann::json& props,ImVec2 windowSize,const UILayout& parent = {}) {
            UILayout layout;

            layout.anchor = AnchorLayout::FromString(VUIHelper::json_or<std::string>(props,"anchor",parent.anchor.ToString()));
            layout.childAnchor = AnchorLayout::FromString(VUIHelper::json_or<std::string>(props,"childAnchor",""));
            
            Compute(layout,props,"spacing",windowSize,&UILayout::spacing);
            
            auto position = VUIHelper::json_or<std::pair<float,float>>(props,"position",{-0.01f,-0.01f});

            if (position.first >= 0 && position.second >= 0) {
                Compute(layout,props,"position",windowSize,&UILayout::position);
                return layout;
            }

            Compute(layout, props, "size", windowSize, &UILayout::size);
            Compute(layout,props,"margin",windowSize,&UILayout::margin);
            
            ComputePosition(layout,parent,layout.childAnchor.Type != None ? layout.anchor : parent.childAnchor);
            
            if (layout.size.x == 0.f || layout.size.y == 0.f) {
               // VLOG_WARN(EditorUI, "UILayout::ParseLayout - width or height is zero, can cause rendering issues.");
            }

            return layout;
        }
    private:
        static void ComputePosition(UILayout& InCurrent, const UILayout& Parent,const AnchorLayout& InAnchor) {
            Vector2f parentAnchor = InAnchor.ToVec();
            Vector2f parentPivot  = Parent.size * parentAnchor;

            Vector2f marginOffset = { InCurrent.margin[3],InCurrent.margin[0] };

            Vector2f sizeOffset = -InCurrent.size * InAnchor.ToVec();
            
            InCurrent.position = parentPivot + marginOffset + sizeOffset;
        }
        
        template <typename T>
        static void Compute(UILayout& layout, const nlohmann::json& props,const char* key, ImVec2 windowSize, T UILayout::*target) {
            if (!props.contains(key))
                return;

            T value = props[key].get<T>();

            if constexpr (std::is_same_v<T, ImVec2>) {
                if (value.x > 0 && value.x <= 1) value.x *= windowSize.x;
                if (value.y > 0 && value.y <= 1) value.y *= windowSize.y;
            }
            else if constexpr (std::is_same_v<T, Vector2f>) {
                if (value.x > 0 && value.x <= 1) value.x *= windowSize.x;
                if (value.y > 0 && value.y <= 1) value.y *= windowSize.y;
            }
            else if constexpr (std::is_same_v<T, std::array<float, 4>>) {
                for (size_t i = 0; i < 4; i++) {
                    if (value[i] > 0 && value[i] <= 1) 
                        value[i] *= (i % 2 == 0 ? windowSize.y : windowSize.x);
                }
            }

            layout.*target = value;
        }
    };
}
