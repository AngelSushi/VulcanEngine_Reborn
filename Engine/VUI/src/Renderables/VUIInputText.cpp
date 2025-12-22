
#include "Binding.h"
#include "ConsoleCommandSystem.h"
#include <Layout.h>
#include "VUIHelper.h"
#include <IRegistry.h>
#include <Renderables/VUIInputText.h>


namespace VUI {
    
    void VUIInputText::Render( const VUIElement& e,const UILayout& InParent) {
        UILayout itemLayout = UILayout::ParseLayout(e.Properties,{InParent.size.x,InParent.size.y},InParent);

        auto label = VUIHelper::json_or<std::string>(e.Properties,"label","");
        auto bind = VUIHelper::json_or<std::string>(e.Properties,"bind","");
        auto bindMethod = VulcanEngine::BindingRegistry.FindIf([&bind](const Binding& b) {
            return b.GetName() == bind;
        });

        if (bindMethod) {
            ImGui::SetNextItemWidth(itemLayout.size.x);
            std::string inputLabel = "##" + label;
            char buffer[256] = "";
            if (ImGui::InputText(inputLabel.c_str(),buffer,sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
                ConsoleCommandSystem::Instance().Execute(buffer);
            }

            bindMethod->Invoke( std::string(buffer));
        }
    }
}
