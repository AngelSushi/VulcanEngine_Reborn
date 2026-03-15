#pragma once
#include <Export.h>
#include <vector>
#include <Entity.h>

#include "IEngineAction.h"

namespace VulcanEngine {
	class VULCAN_ENGINE_API AssetsAction : public IEngineAction {

	public:
		// IEngineAction Functions
		void RegisterBindings() override;

		void ImportAsset();
		void DeleteAsset(const std::string& InAssetPath);
		void CopyPath(const std::string& InAssetPath);
	};

}

