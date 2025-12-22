#pragma once
#include <CoreAPI/IRegistry.h>

#include <Binding.h>
#include <Actions/IEngineAction.h>

#include <providers/ITreeIconProvider.h>
#include <ThemeAsset.h>

#include <Types/Assets/Scene.h>

#include "CoreAPI/ObjectRegistry.h"

namespace VulcanEngine {
	extern VULCAN_ENGINE_API ObjectRegistry<VUI::ThemeAsset>  ThemeRegistry; // Don't use inline because of dll export issues
	extern VULCAN_ENGINE_API IRegistry<VUI::Binding> BindingRegistry;
	extern VULCAN_ENGINE_API IRegistry<VUI::ITreeIconProvider> TreeIconProviderRegistry;
	extern VULCAN_ENGINE_API IRegistry<IEngineAction> EngineActionRegistry;
	extern VULCAN_ENGINE_API IRegistry<ComponentType> ComponentTypeRegistry;

}

