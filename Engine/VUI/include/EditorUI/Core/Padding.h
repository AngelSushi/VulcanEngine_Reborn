#pragma once
#include <nlohmann/json_fwd.hpp>


struct Padding {
    float Top;
    float Right;
    float Bottom;
    float Left;

    Padding() : Top(0), Right(0), Bottom(0), Left(0) {}
    Padding(float InTop, float InRight, float InBottom, float InLeft): Top(InTop), Bottom(InBottom), Left(InLeft), Right(InRight) {}
    
};

inline void to_json(nlohmann::json& j, const Padding& p) {
    j = nlohmann::json::array({p.Top,p.Right,p.Bottom,p.Left});
}

inline void from_json(const nlohmann::json& j, Padding& p) {
    p.Top = j.at(0).get<float>();
    p.Right = j.at(1).get<float>();
    p.Bottom = j.at(2).get<float>();
    p.Left = j.at(3).get<float>();
}
