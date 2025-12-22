#include <IRegistry.h>

#include <Binding.h>
#include <ThemeAsset.h>
#include <providers/ITreeIconProvider.h>
#include <Actions/IEngineAction.h>
#include <Types/Assets/Scene.h>


namespace VulcanEngine {
    VULCAN_ENGINE_API ObjectRegistry<VUI::ThemeAsset> ThemeRegistry;
    VULCAN_ENGINE_API IRegistry<VUI::Binding> BindingRegistry;
    VULCAN_ENGINE_API IRegistry<VUI::ITreeIconProvider> TreeIconProviderRegistry;
    VULCAN_ENGINE_API IRegistry<IEngineAction> EngineActionRegistry;
    VULCAN_ENGINE_API IRegistry<ComponentType> ComponentTypeRegistry;

}
