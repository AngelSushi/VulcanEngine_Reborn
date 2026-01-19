#pragma once
#include <CoreAPI/precomp.h>


struct UIValue;

struct UIPropSchema {
    std::string Name;
    UIValue DefaultValue;
    std::function<bool(const UIValue&)> Validator; // std::function can not work on certain sdk, we may need to replace it later.
};
