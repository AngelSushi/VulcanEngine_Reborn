#pragma once
#include <CoreAPI/precomp.h>

#include <EditorUI/Core/UINode.h>

// The runtime representation of .json UI screen data. This class is responsible for building the UINode structure that represents the UI screen at runtime.
class UIScreen {
public:
    virtual ~UIScreen() = default;
    virtual UINode Build() = 0;
};
