
enum class EHorizontalAlignment {
    Left,
    Center,
    Right,
    Fill
};

enum class EVerticalAlignment {
    Top,
    Center,
    Bottom,
    Fill
};

inline std::string_view ToStringHorizontal(EHorizontalAlignment HorizontalAlignment) {
    switch (HorizontalAlignment) {
        case EHorizontalAlignment::Left: return "Left";
        case EHorizontalAlignment::Center: return "Center";
        case EHorizontalAlignment::Right: return "Right";
        case EHorizontalAlignment::Fill: return "Fill";
        default: return "Left";
    }
}

inline EHorizontalAlignment ToEnumHorizontal(std::string_view Value) {
    if (Value == "Left") return EHorizontalAlignment::Left;
    if (Value == "Center") return EHorizontalAlignment::Center;
    if (Value == "Right") return EHorizontalAlignment::Right;
    if (Value == "Fill") return EHorizontalAlignment::Fill;

    return EHorizontalAlignment::Left; // Default value
}

inline std::string_view ToStringVertical(EVerticalAlignment VerticalAlignment) {
    switch (VerticalAlignment) {
        case EVerticalAlignment::Top: return "Top";
        case EVerticalAlignment::Center: return "Center";
        case EVerticalAlignment::Bottom: return "Bottom";
        case EVerticalAlignment::Fill: return "Fill";
        default: return "Top";
    }
}

inline EVerticalAlignment ToEnumVertical(std::string_view Value) {
    if (Value == "Top") return EVerticalAlignment::Top;
    if (Value == "Center") return EVerticalAlignment::Center;
    if (Value == "Bottom") return EVerticalAlignment::Bottom;
    if (Value == "Fill") return EVerticalAlignment::Fill;

    return EVerticalAlignment::Top; // Default value
}