#include <Actions/AssetsAction.h>

#include <iostream>

#include "Requests/UIRequest.h"
#include "Requests/UIRequests.h"
#include <IRegistry.h>

#include <Types/Assets/AssetsManager.h>

#include "UIUtils.h"
#include "Actions/FolderAction.h"
#include "Requests/ImportRequestDatas/SpriteImportData.h"

namespace VulcanEngine {
	void AssetsAction::RegisterBindings() {
		using namespace VUI;
		BindingRegistry.Register(Binding::Register("Assets::Delete",this,&AssetsAction::DeleteAsset));
		BindingRegistry.Register(Binding::Register("Assets::Rename",this,&AssetsAction::RenameAsset));
		BindingRegistry.Register(Binding::Register("Assets::MoveTo",this,&AssetsAction::MoveTo));
		BindingRegistry.Register(Binding::Register("Assets::CopyPath",this,&AssetsAction::CopyPath));

		BindingRegistry.Register(Binding::Register("Assets::Import",this,&AssetsAction::ImportAsset));
	}

	void AssetsAction::ImportAsset() {
		auto originPath = fs::current_path();
		
		AssetsManager::OpenFile([&originPath](const std::string& InFilePath){
			auto path = fs::path(InFilePath);
			
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
			}
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

	void AssetsAction::RenameAsset(const UIDragDrop::DragDropPayload& Payload) {
		
	}

	void AssetsAction::MoveTo(const UIDragDrop::DragDropPayload& Payload) {
		auto* src = std::any_cast<AssetsManager::AssetInfo>(&Payload.InEntry->Payload);
		auto* dst = std::any_cast<AssetsManager::AssetInfo>(&Payload.OutEntry->Payload);

		if (!src || !dst)
			return;

		AssetsManager::Instance().MoveAsset(*src,*dst);
		AssetsManager::Instance().SetTreeDirty(true);
	}

	 void AssetsAction::CopyPath(const std::string& InAssetPath) {
		ImGui::SetClipboardText( absolute(fs::path(InAssetPath)).string().c_str());
	}
}

