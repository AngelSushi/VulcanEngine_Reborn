
#include "Renderables/VUIFactory.h"

#include "Renderables/VUIButton.h"
#include "Renderables/VUICheckbox.h"
#include "Renderables/VUICombo.h"
#include "Renderables/VUIFlagCheckbox.h"
#include "Renderables/VUIGrid.h"
#include "Renderables/VUIHeader.h"
#include "Renderables/VUIInputText.h"
#include "Renderables/VUILogger.h"
#include "Renderables/VUISeparator.h"
#include "Renderables/VUIText.h"
#include "Renderables/VUITextureButton.h"
#include "Renderables/VUITree.h"

namespace VUI {

    std::unordered_map<std::string, VUIFactory::FactoryFunc> VUIFactory::Registry;

    void VUIFactory::RegisterBuildInWidgets(const VUIElement& e) {
        Registry["Text"] = []() { return std::make_unique<VUIText>(); };
        Registry["Button"] = []() { return std::make_unique<VUIButton>(); };
        Registry["TextureButton"] = []() { return std::make_unique<VUITextureButton>(); };
        Registry["Grid"] = [&]() { return std::make_unique<VUIGrid>(e); };
        Registry["Separator"] = []() { return std::make_unique<VUISeparator>(); };
        Registry["Tree"] = []() { return std::make_unique<VUITree>(); };

        Registry["Logger"] = []() { 
            LoggerConfig config{};
            return std::make_unique<VUILogger>(config); 
        };

        Registry["Checkbox"] = []() { return std::make_unique<VUICheckbox>(); };
        Registry["FlagCheckbox"] = []() { return std::make_unique<VUIFlagCheckbox>(); };
        Registry["Combo"] = []() { return std::make_unique<VUICombo>(); };
        Registry["InputText"] = []() { return std::make_unique<VUIInputText>(); };
        Registry["Header"] = []() { return std::make_unique<VUIHeader>(); };
        
    }

    std::unique_ptr<VUIRenderable> VUIFactory::Create(const VUIElement& e) {
        if (Registry.empty()) RegisterBuildInWidgets(e);
        
        auto it = Registry.find(e.Type);
        
        if (it != Registry.end())
            return it->second();

        return nullptr;
    }
}
