#include <Types/Assets/AssetsManager.h>
#include <ResourceManager.h>
#include <string>
#include <fmt/core.h>
#include <fstream>

#include <filesystem>

#include "ThemeAsset.h"
#include "Themehandler.h"
#include <Game.h>
#include <IRegistry.h>
#include <Handlers/SceneHandler.h>
#include <Types/Assets/Scene.h>
#include <Types/Assets/UIAsset.h>

#include "CoreAPI/VSurface.h"
#include "Handlers/SpriteAssetHandler.h"
#include "Handlers/UIAssetHandler.h"
#include "Types/Assets/SpriteAsset.h"
#include <Windows.h>

using namespace std;

namespace fs = std::filesystem;

namespace VulcanEngine {

	AssetsManager::AssetsManager() {
		RegisterHandler<SpriteAsset>(std::make_unique<SpriteAssetHandler>());
		RegisterHandler<UIAsset>(std::make_unique<UIAssetHandler>());
		RegisterHandler<VUI::ThemeAsset>(std::make_unique<VUI::ThemeHandler>());
		RegisterHandler<Scene>(std::make_unique<SceneHandler>());


		BindingRegistry.Register(VUI::Binding::Register("AssetsManager::GetAssetsTree",this,&AssetsManager::GetAssetsTree));

		Game::GetFrameBeginEvent().Register(this,&AssetsManager::OnFrameBegin,LOW);
		Game::GetStartEngineEvent().Register(this,&AssetsManager::OnStart,LOW);
		Game::GetQuitEngineEvent().Register(this,&AssetsManager::OnQuit,LOW);
	}

	const std::string& AssetsManager::GetUnloadedAssetName(const std::string& AssetPath) {
		return UnloadedAssets[AssetPath];
	}

	std::string AssetsManager::GetUnloadedAssetPath(const std::string& AssetName) {
		for (const auto& [path, name] : UnloadedAssets) {
			if (name == AssetName) {
				return path.string();
			}
		}

		return "";
	}

	void AssetsManager::MoveAsset(AssetInfo& asset, AssetInfo& targetFolder) {
		auto oldPath = asset.FullPath;
		auto newPath = std::filesystem::path(targetFolder.FullPath) / std::filesystem::path(oldPath).filename();

		std::filesystem::rename(oldPath, newPath);

		asset.FullPath = newPath.string();
		if (asset.LoadedAsset)
			asset.LoadedAsset->SetFilePath(newPath.string());
		
		auto metaOld = ReplaceExtension(oldPath, ".vasset");
		auto metaNew = ReplaceExtension(newPath, ".vasset");

		std::filesystem::rename(metaOld, metaNew);
	}
	
	std::string AssetsManager::ReplaceExtension(const fs::path& InPath, const std::string& InNewExtension) {
		auto newPath = InPath;
		newPath.replace_extension(InNewExtension);
		return newPath.string();
	}
	
	void AssetsManager::OnStart() {
		EnumerateAssets("assets/");
		ConstructAssetTree();
	}

	void AssetsManager::OnQuit() {
		for (auto& obj : VulcanCore::ObjectManager::Instance().GetAssetContext().GetObjects()) {
			auto asset = VulcanCore::Cast<VAsset>(obj);
			if (asset) {
				auto& type = typeid(*asset);
				auto it = Handlers.find(type);

				if (it != Handlers.end()) {
					it->second->Save(asset->GetFilePath(), *asset);
				}	
			}
		}
	}

	void AssetsManager::OnFrameBegin() {
		if (TreeDirty) {
			ConstructAssetTree();
			TreeDirty = false;
		}
	}
	

	void AssetsManager::ConstructAssetTree() {
		RootTree = BuildTree("assets/");
		OrderTree(RootTree);
		SetTreeParent(RootTree, nullptr);
	}

	VUI::TreeEntry AssetsManager::BuildTree(const std::string_view& RootPath) {
		VUI::TreeEntry node{};

		fs::path path(RootPath);
		std::string name = path.filename().empty() ? path.string() : path.filename().string();
		std::replace(name.begin(),name.end(),'/',' ');
		
		std::string inPathStr = path.string();
		std::replace(inPathStr.begin(),inPathStr.end(),'\\','/');
		
		node.EntryName = name;
		node.Payload = AssetInfo { inPathStr, typeid(void), nullptr};
		node.IsDirectory = true;

		for (const auto& entry : fs::directory_iterator(RootPath)) {
			std::string pathStr = entry.path().string();
			std::replace(pathStr.begin(),pathStr.end(),'\\','/');
			
			if (entry.is_directory()) {
				node.Children.push_back(BuildTree(entry.path().string()));
			}
			else if (entry.is_regular_file()) {
				const auto& availableExt = VAsset::GetAvailableExtensions();
				if (std::find(availableExt.begin(), availableExt.end(), entry.path().extension().string()) == availableExt.end()) {
					continue;
				}
				
				auto obj = VulcanCore::ObjectManager::Instance().GetAssetContext().FindIf([&](VObject* o) {
					auto asset = VulcanCore::Cast<VAsset>(o);
					if (asset) {
						return asset->GetFilePath() == pathStr;
					}
					return false;
				});
				
				VUI::TreeEntry fileNode{};
				fileNode.EntryName = entry.path().filename().string();
				fileNode.Payload = AssetInfo {pathStr, obj ? typeid(*obj) : typeid(void), obj ? VulcanCore::Cast<VAsset>(obj) : nullptr};
				node.Children.push_back(std::move(fileNode));
			}
		}

		return node;
	}

	void AssetsManager::OrderTree(VUI::TreeEntry& InRoot) {
		std::sort(InRoot.Children.begin(), InRoot.Children.end(), [](const VUI::TreeEntry& a, const VUI::TreeEntry& b) {
			if (a.IsDirectory != b.IsDirectory) {
				return a.IsDirectory > b.IsDirectory; // Directories first
			}
			
			return a.EntryName < b.EntryName; // Then by name
		});
		
		if (!InRoot.Children.empty()) {
			for (size_t i = 0; i < InRoot.Children.size();) {
				if (InRoot.Children[i].IsDirectory && InRoot.Children[i].Children.empty()) {
					InRoot.Children.erase(InRoot.Children.begin() + i);
					continue;
				}

				OrderTree(InRoot.Children[i]);
				i++;
			}
		}
	}

	void AssetsManager::SetTreeParent(VUI::TreeEntry& n, VUI::TreeEntry* parent) {
		n.Parent = parent;
		for (auto& c : n.Children) {
			SetTreeParent(c, &n);
		}
	}

	void AssetsManager::EnumerateAssets(const fs::path& Path) {
		for (const auto& entry : fs::directory_iterator(Path)) {
			std::string pathStr = entry.path().string();
			std::replace(pathStr.begin(),pathStr.end(),'\\','/');
			
			if (entry.is_directory()) {
				EnumerateAssets(entry.path());
			}
			else if (entry.is_regular_file()) {
				UnloadedAssets[pathStr] = entry.path().filename().string();

				auto availableExt = Graphics::VSurface::GetAvailableExtensions();

				if (std::find(availableExt.begin(), availableExt.end(), entry.path().extension().string()) != availableExt.end()) {
					Load<SpriteAsset>(pathStr);
				}
			}
		}
	}

	void AssetsManager::OpenFile(std::function<void(const std::string&)> OnFileSelected) {
		OPENFILENAME ofn;
		char szFile[260] = { 0 };

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		//ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&ofn)) {
			OnFileSelected(ofn.lpstrFile);
		}
	}

}

