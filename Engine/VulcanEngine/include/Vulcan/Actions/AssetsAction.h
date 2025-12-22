#pragma once
#include <imgui_internal.h>
#include <Export.h>
#include <vector>
#include <Entity.h>

#include "IEngineAction.h"
#include "UIUtils.h"

namespace VulcanEngine {
	class VULCAN_ENGINE_API AssetsAction : public IEngineAction {

	public:
		// IEngineAction Functions
		void RegisterBindings() override;

		void ImportAsset();
		void DeleteAsset(const std::string& InAssetPath);
		void RenameAsset(const UIDragDrop::DragDropPayload& Payload);
		void MoveTo(const UIDragDrop::DragDropPayload& Payload);
		void CopyPath(const std::string& InAssetPath);
	};

}

