#include <Types/Assets/VAsset.h>

#include "Types/VFont.h"
#include "Types/Assets/Scene.h"

namespace VulcanEngine {
	

	VAsset::VAsset(std::string FilePath) : FilePath(FilePath)
	{
		
	}

	VAsset::VAsset(std::string FilePath, std::string Name) : FilePath(FilePath), AssetName(Name) {}

	std::vector<std::string> VAsset::GetAvailableExtensions() {
		std::vector<std::string> extensions;

		const auto& availableSurfaces = Graphics::VSurface::GetAvailableExtensions();
		const auto& availableScenes = Scene::GetAvailableExtensions();
		const auto& availableFonts = VFont::GetAvailableExtensions();

		extensions.reserve(availableSurfaces.size()+ availableScenes.size() + availableFonts.size());

		extensions.insert(extensions.end(), availableSurfaces.begin(), availableSurfaces.end());
		extensions.insert(extensions.end(), availableScenes.begin(), availableScenes.end());
		extensions.insert(extensions.end(), availableFonts.begin(), availableFonts.end());

		return extensions;
	}
	
}
