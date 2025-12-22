#pragma once
#include <imgui_internal.h>
#include <Export.h>
#include <vector>
#include <Entity.h>

#include "IEngineAction.h"

namespace VulcanEngine {
	class VULCAN_ENGINE_API FolderAction : public IEngineAction {

	public:
		// IEngineAction Functions
		void RegisterBindings() override;

		TVector<std::string>& ListFolders();
		void ShowInFolder(const std::string& InPath);

	private:
		TVector<std::string> Folders{};
	};

}

