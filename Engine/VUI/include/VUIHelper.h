#pragma once 
#include <string>
#include <fmt/color.h>
#include <imgui.h>

#include <VUIElement.h>


namespace VUI {
    using ColorFlags = ImGuiCol;
    using WindowFlags = ImGuiWindowFlags;
    
    struct ColorFlagMap { std::string_view name; ColorFlags flag; };
    struct StyleVarMap { std::string_view name; ImGuiStyleVar flag; };
    struct WindowFlagMap { std::string_view name; WindowFlags flag; };

    static constexpr WindowFlagMap WindowFlagMap[] = {
        {"no_title_bar",ImGuiWindowFlags_NoTitleBar},
        {"no_resize",ImGuiWindowFlags_NoResize},
        {"no_move",ImGuiWindowFlags_NoMove},
        {"no_scrollbar",ImGuiWindowFlags_NoScrollbar},
        {"no_collapse",ImGuiWindowFlags_NoCollapse},
        {"always_auto_resize",ImGuiWindowFlags_AlwaysAutoResize},
        {"no_background",ImGuiWindowFlags_NoBackground},
        {"no_bring_to_front_on_focus",ImGuiWindowFlags_NoBringToFrontOnFocus},
        {"no_docking",ImGuiWindowFlags_NoDocking},
        {"no_nav_inputs",ImGuiWindowFlags_NoNavInputs},
        {"no_nav_focus",ImGuiWindowFlags_NoNavFocus},
        {"unsaved_document",ImGuiWindowFlags_UnsavedDocument},
        {"no_mouse_inputs",ImGuiWindowFlags_NoMouseInputs},
    };
    
    static constexpr ColorFlagMap ColorFlagMap[] = {
        {"Text",ImGuiCol_Text},
        {"TextDisabled",ImGuiCol_TextDisabled},
        {"WindowBg",ImGuiCol_WindowBg},
        {"ChildBg",ImGuiCol_ChildBg},
        {"PopupBg",ImGuiCol_PopupBg},
        {"Border",ImGuiCol_Border},
        {"BorderShadow",ImGuiCol_BorderShadow},
        {"FrameBg",ImGuiCol_FrameBg},
        {"FrameBgHovered",ImGuiCol_FrameBgHovered},
        {"FrameBgActive",ImGuiCol_FrameBgActive},
        {"TitleBg",ImGuiCol_TitleBg},
        {"TitleBgActive",ImGuiCol_TitleBgActive},
        {"TitleBgCollapsed",ImGuiCol_TitleBgCollapsed},
        {"MenuBarBg",ImGuiCol_MenuBarBg},
        {"ScrollbarBg",ImGuiCol_ScrollbarBg},
        {"ScrollbarGrab",ImGuiCol_ScrollbarGrab},
        {"ScrollbarGrabHovered",ImGuiCol_ScrollbarGrabHovered},
        {"ScrollbarGrabActive",ImGuiCol_ScrollbarGrabActive},
        {"CheckMark",ImGuiCol_CheckMark},
        {"SliderGrab",ImGuiCol_SliderGrab},
        {"SliderGrabActive",ImGuiCol_SliderGrabActive},
        {"Button",ImGuiCol_Button},
        {"ButtonHovered",ImGuiCol_ButtonHovered},
        {"ButtonActive",ImGuiCol_ButtonActive},
        {"Header",ImGuiCol_Header},
        {"HeaderHovered",ImGuiCol_HeaderHovered},
        {"HeaderActive",ImGuiCol_HeaderActive},
        {"Separator",ImGuiCol_Separator},
        {"SeparatorHovered",ImGuiCol_SeparatorHovered},
        {"SeparatorActive",ImGuiCol_SeparatorActive},
        {"ResizeGrip",ImGuiCol_ResizeGrip},
        {"ResizeGripHovered",ImGuiCol_ResizeGripHovered},
        {"ResizeGripActive",ImGuiCol_ResizeGripActive},
        
        {"Tab",ImGuiCol_Tab},
        {"TabHovered",ImGuiCol_TabHovered},
{"TabSelected",ImGuiCol_TabSelected},
        {"TabActive",ImGuiCol_TabActive},
        {"TabUnfocused",ImGuiCol_TabUnfocused},
        {"TabUnfocusedActive",ImGuiCol_TabUnfocusedActive},
            {"TabDimmed",ImGuiCol_TabDimmed},
        {"TabDimmedSelected",ImGuiCol_TabDimmedSelected},
        {"TabDimmedSelectedOverline",ImGuiCol_TabDimmedSelectedOverline},
{"TabSelectedOverline",ImGuiCol_TabSelectedOverline},
        {"DockingPreview",ImGuiCol_DockingPreview},
        {"DockingEmptyBg",ImGuiCol_DockingEmptyBg},
        {"PlotLines",ImGuiCol_PlotLines},
        {"PlotLinesHovered",ImGuiCol_PlotLinesHovered},
        {"PlotHistogram",ImGuiCol_PlotHistogram},
        {"PlotHistogramHovered",ImGuiCol_PlotHistogramHovered},
        {"TableHeaderBg",ImGuiCol_TableHeaderBg},
        {"TableBorderStrong",ImGuiCol_TableBorderStrong},
        {"TableBorderLight",ImGuiCol_TableBorderLight},
        {"TableRowBg",ImGuiCol_TableRowBg},
        {"TableRowBgAlt",ImGuiCol_TableRowBgAlt},
        {"TextSelectedBg",ImGuiCol_TextSelectedBg},
        {"DragDropTarget",ImGuiCol_DragDropTarget},
        {"NavHighlight",ImGuiCol_NavHighlight},
        {"NavWindowingHighlight",ImGuiCol_NavWindowingHighlight},
        {"NavWindowingDimBg",ImGuiCol_NavWindowingDimBg},
    };

    static constexpr StyleVarMap StyleVarMap[] = {
        {"Alpha",ImGuiStyleVar_Alpha},
        {"WindowPadding",ImGuiStyleVar_WindowPadding},
        {"WindowRounding",ImGuiStyleVar_WindowRounding},
        {"WindowBorderSize",ImGuiStyleVar_WindowBorderSize},
        {"WindowMinSize",ImGuiStyleVar_WindowMinSize},
        {"WindowTitleAlign",ImGuiStyleVar_WindowTitleAlign},
        {"ChildRounding",ImGuiStyleVar_ChildRounding},
        {"ChildBorderSize",ImGuiStyleVar_ChildBorderSize},
        {"PopupRounding",ImGuiStyleVar_PopupRounding},
        {"PopupBorderSize",ImGuiStyleVar_PopupBorderSize},
        {"FramePadding",ImGuiStyleVar_FramePadding},
        {"FrameRounding",ImGuiStyleVar_FrameRounding},
        {"FrameBorderSize",ImGuiStyleVar_FrameBorderSize},
        {"ItemSpacing",ImGuiStyleVar_ItemSpacing},
        {"ItemInnerSpacing",ImGuiStyleVar_ItemInnerSpacing},
        {"IndentSpacing",ImGuiStyleVar_IndentSpacing},
        {"CellPadding",ImGuiStyleVar_CellPadding},
        {"ScrollbarSize",ImGuiStyleVar_ScrollbarSize},
        {"ScrollbarRounding",ImGuiStyleVar_ScrollbarRounding},
        {"GrabMinSize",ImGuiStyleVar_GrabMinSize},
        {"GrabRounding",ImGuiStyleVar_GrabRounding},
        {"TabRounding",ImGuiStyleVar_TabRounding},
        {"ButtonTextAlign",ImGuiStyleVar_ButtonTextAlign},
        {"SelectableTextAlign",ImGuiStyleVar_SelectableTextAlign},
    };
    
    class VUIHelper {
    public:

        template<typename T>
        static T json_or(const nlohmann::json& json,const char* key,const T& def) {
            if (!json.is_object()) {
                return def;
            }

            auto it = json.find(key);
            if (it == json.end()) {
                return def;
            }
            
            try { return it->get<T>(); } catch (...) { return def; }
        }


        static WindowFlags GetWindowFlagByName(const std::string& InName) {
            for (const auto& entry : WindowFlagMap) {
                if (entry.name == InName) {
                    return entry.flag;
                }
            }
            
            fmt::print(fg(fmt::color::red), "Color flag '{}' not found. Defaulting to -1.\n", InName);
            return -1; 
        }
        
        static ColorFlags GetColorFlagByName(const std::string& name) {
            for (const auto& entry : ColorFlagMap) {
                if (entry.name == name) {
                    return entry.flag;
                }
            }
            
            fmt::print(fg(fmt::color::red), "Color flag '{}' not found. Defaulting to -1.\n", name);
            return -1; 
        }

        static ImGuiStyleVar GetStyleVarByName(const std::string& name) {
            for (const auto& entry : StyleVarMap) {
                if (entry.name == name) {
                    return entry.flag;
                }
            }
            
            fmt::print(fg(fmt::color::red), "Style var '{}' not found. Defaulting to -1.\n", name);
            return -1; 
        }

    private:

    };
    
}
