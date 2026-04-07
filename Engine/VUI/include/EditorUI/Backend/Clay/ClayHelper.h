#pragma once

#include <CoreAPI/precomp.h>


enum class EClaySizeType {
    GROW,
    FIXED
};

inline EClaySizeType ClaySizeTypeFromString(const std::string& TypeStr) {
    if (TypeStr == "GROW") {
        return EClaySizeType::GROW;
    } else if (TypeStr == "FIXED") {
        return EClaySizeType::FIXED;
    } else {
        return EClaySizeType::GROW;
    }
}

inline std::string ClaySizeTypeToString(const EClaySizeType& Type) {
    switch (Type) {
        default:
        case EClaySizeType::GROW:
            return "GROW";
        case EClaySizeType::FIXED:
            return "FIXED";
    }
}

struct ClayAxisSize {
    EClaySizeType Type;
    float Value = 0.f;

    Clay_SizingAxis ToClayAxis() const {
        switch (Type) {
            default:
                return CLAY_SIZING_GROW(0);
            case EClaySizeType::GROW:
                return CLAY_SIZING_GROW(Value);
            case EClaySizeType::FIXED:
                return CLAY_SIZING_FIXED(Value);
        }
    }
};

inline void from_json(const nlohmann::json& j, ClayAxisSize& AxisSize) {
    std::string TypeStr = j.at("type");

    AxisSize.Type = ClaySizeTypeFromString(TypeStr);
    AxisSize.Value = j.at("value");
}

inline void to_json(nlohmann::json& j, const ClayAxisSize& AxisSize) {
    j = {
        {"type", ClaySizeTypeToString(AxisSize.Type)},
        {"value", AxisSize.Value}
    };
}

class ClaySize {
public:
    ClaySize() = default;
    
    Clay_Sizing ToClaySize() const {
        return { X.ToClayAxis(), Y.ToClayAxis() };
    }
    
    ClayAxisSize X;
    ClayAxisSize Y;
};

inline void from_json(const nlohmann::json& j, ClaySize& Size) {
    j.at("x").get_to(Size.X);
    j.at("y").get_to(Size.Y);
}

inline void to_json(nlohmann::json& j, const ClaySize& Size) {
    j = {
        {"x", Size.X},
        {"y", Size.Y}
    };
}
