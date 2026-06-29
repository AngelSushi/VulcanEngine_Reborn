#pragma once
#include <CoreAPI/precomp.h>

#include <EditorUI/Core/UINode.h>

#include "EditorUI/Core/UINodeBuilder.h"
#include "EditorUI/Core/UIScreen.h"

// The runtime representation of .json UI screen data. This class is responsible for building the UINode structure that represents the UI screen at runtime.
class MainWindowNavbarScreen : public UIScreen {
public:
    UINode Build() override {
        return UINodeBuilder("Navbar","mainwindow-navbar")
        .Window(0)
        .Prop("backgroundColor",UIValue(std::string("#0000ff")))
        .Prop("size",UIValue(ClaySize(
            ClayAxisSize(EClaySizeType::GROW,0.f),
            ClayAxisSize(EClaySizeType::FIXED,20.f)
        )))
        .Prop("focusable",true)
        .Children(MakeButton("button1","Button 1","#ff0000"))
        .Children(MakeButton("button2","Button 2","#00ff00"))
        .Build();
    }

private:
    UINodeBuilder MakeButton(const std::string& Id, const std::string& Text, const std::string& BackgroundColor) {
        return UINodeBuilder("NavButton", Id)
            .Prop("text", UIValue(Text))
            .Prop("backgroundColor", UIValue(BackgroundColor))
            .Prop("focusable",true)
            .Prop("size", UIValue(ClaySize(
                ClayAxisSize(EClaySizeType::FIXED, 100.f),
                ClayAxisSize(EClaySizeType::GROW, 0.f)
            )))
            .Children(MakeText("text_" + Id, Text, "#ffffff"));
    }

    UINodeBuilder MakeText(const std::string& Id, const std::string& Text, const std::string& Color) {
        return UINodeBuilder("Text", Id)
            .Prop("text", UIValue(Text))
            .Prop("color", UIValue(Color))
            .Prop("font", UIValue(std::string("gil.TTF")))
            .Prop("fontSize", UIValue(16));
    }
};
