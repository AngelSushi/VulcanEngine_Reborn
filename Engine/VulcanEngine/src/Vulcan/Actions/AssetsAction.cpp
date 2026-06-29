#include <Actions/AssetsAction.h>

#include <iostream>

#include <IRegistry.h>

#include <Types/Assets/AssetsManager.h>

#include "Actions/FolderAction.h"

namespace VulcanEngine {
	void AssetsAction::RegisterBindings() {
		/*using namespace VUI;
		BindingRegistry.Register(Binding::Register("Assets::Delete",this,&AssetsAction::DeleteAsset));
		BindingRegistry.Register(Binding::Register("Assets::CopyPath",this,&AssetsAction::CopyPath));

		BindingRegistry.Register(Binding::Register("Assets::Import",this,&AssetsAction::ImportAsset));
*/
	}

	void AssetsAction::ImportAsset() {
		auto originPath = fs::current_path();
		
		AssetsManager::OpenFile([&originPath](const std::string& InFilePath){
			/*auto path = fs::path(InFilePath);
			
			std::unique_ptr<VUI::SpriteImportData> data = std::make_unique<VUI::SpriteImportData>();

			auto folderActionPtr = dynamic_cast<FolderAction*>(EngineActionRegistry.FindIf([](const IEngineAction& action) {
				return dynamic_cast<const FolderAction*>(&action) != nullptr;
			}));

			if (folderActionPtr) {
				std::filesystem::current_path(originPath);
				
				data->Folders = folderActionPtr->ListFolders();
				data->AssetName = path.filename().string();
				
				VUI::UIRequests::Instance().PushRequest({
					.RequestType = VUI::UIRequestType::ImportAsset,
					.Data = std::move(data)
				});
			}*/
		});
	}

	void AssetsAction::DeleteAsset(const std::string& InAssetPath) {
		try {
			std::filesystem::remove(InAssetPath);
		}catch (const std::filesystem::filesystem_error& e) {
			std::cerr << e.what();
		}

		AssetsManager::Instance().SetTreeDirty(true);
	}

	 void AssetsAction::CopyPath(const std::string& InAssetPath) {
	}
}

