#include <imgui.h>
#include <Renderables/VUILogger.h>

#include "IRegistry.h"
#include "Layout.h"
#include "LogSystem.h"

#include "ConsoleCommandSystem.h"
#include <Systems/EditorSystem.h>

#include "Reflection/VEnum.h"


namespace VUI {
    
    VUILogger::VUILogger(LoggerConfig& config) {
        Config = config;
        VulcanEngine::BindingRegistry.Register(Binding::Register("console.clearonplay", Config.clearOnPlay));

        VulcanEngine::BindingRegistry.Register(std::make_unique<Binding>("console.logger.flags", [this](const std::vector<std::any>& args) -> std::any {
            if (args.empty()) {
                return std::any(this->Config.GetFlags());
            }
            if (args.size() == 1) {
                const auto& name = std::any_cast<const std::string&>(args[0]);
                return std::any(this->Config.GetFlag(name));
            }
            if (args.size() == 2) {
                const auto& name = std::any_cast<const std::string&>(args[0]);
                bool enabled = std::any_cast<bool>(args[1]);
                this->Config.SetFlag(name, enabled);
                return std::any(this->Config.GetFlag(name));
            }
                
            return {};
        }));

        VulcanEngine::BindingRegistry.Register(Binding::Register("console.search",this,&VUILogger::GetSearchText,&VUILogger::SetSearchText));
        VulcanEngine::BindingRegistry.Register(Binding::Register("console.categories", this, &VUILogger::GetCategories));
        VulcanEngine::BindingRegistry.Register(Binding::Register("console.clear", &VulcanEngine::LogSystem::Instance(), &VulcanEngine::LogSystem::Clear));

        ConsoleCommandSystem::Instance().RegisterCommand("flags","Manage console flags", [&](auto args) {
            if (args.empty()) {
                for (auto [flagName,flagEnabled] : Config.GetFlags()) {
                    VLOG_INFO(EditorUI, "Flag '{}' is {}", flagName, flagEnabled ? "1" : "0");
                }
            }
            if (args.size() == 1) {
                bool flagEnabled = Config.GetFlag(args[0]);
                VLOG_INFO(EditorUI, "Flag '{}' is {}", args[0], flagEnabled ? "1" : "0");
            }
            if (args.size() == 2) {
                bool enabled = args[1] == "true";
                Config.SetFlag(args[0], enabled);
                bool flagEnabled = Config.GetFlag(args[0]);
                VLOG_INFO(EditorUI, "Flag '{}' set to {}", args[0], flagEnabled ? "1" : "0");
            }
        });

        ConsoleCommandSystem::Instance().RegisterCommand("clear","Clears the console log", [&](auto args) {
            VulcanEngine::LogSystem::Instance().Clear();
        });
    }

    void VUILogger::Render( const VUIElement& e,const UILayout& InParent) {
        
        UILayout layout = UILayout::ParseLayout(e.Properties,ImGui::GetContentRegionAvail());

        bool border = VUIHelper::json_or<bool>(e.Properties, "border", false);
        auto fontScale = VUIHelper::json_or<float>(e.Properties, "fontScale", 1.0f);

        ImGui::SetCursorPos({ImGui::GetCursorPosX() + layout.position.x, ImGui::GetCursorPosY() + layout.position.y});
        ImGui::BeginChild("##LoggerRegion", {layout.size.x, layout.size.y}, border,ImGuiWindowFlags_AlwaysVerticalScrollbar);

        if (LastScrollY != -1.f && LastScrollY != ImGui::GetScrollY()) {
            FixScroll = false;
        }
        else if (!FixScroll && ImGui::GetScrollY() == ImGui::GetScrollMaxY()) {
            FixScroll = true;
        }

        if (FixScroll) {
            ImGui::SetScrollY(ImGui::GetScrollMaxY());
        }
        
         for (auto& message : VulcanEngine::LogSystem::Instance().GetMessages()) {
             if ((!message.Message.empty() && message.Message.find(Search) == std::string::npos) || !message.Category.IsEnabled() || !(Config.EnumToMask(message.Level) & Config.loggerFlags)) {
                 continue;
             }

             auto levelName = VulcanCore::EnumToString<VulcanEngine::LogLevel>(message.Level);
             auto color = message.GetColorForLevel();
            
             ImGui::SetWindowFontScale(fontScale);
             ImGui::TextColored(ImVec4(color.x,color.y,color.z,1.0f),"[%s] [%s:%d] [%s] %s", message.Timestamp.c_str(), message.File.c_str(), message.Line,levelName, message.Message.c_str());
             ImGui::SetWindowFontScale(1.0f);
         }

        LastScrollY = ImGui::GetScrollY();
        ImGui::EndChild();
    }
}
