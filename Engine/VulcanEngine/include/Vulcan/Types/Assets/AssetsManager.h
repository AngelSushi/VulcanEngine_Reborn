#pragma once
#include <any>
#include <Export.h>
#include <vector>
#include <string>
#include <memory>

#include <functional>
#include <stdexcept>

#include <filesystem>

#include <Entries/TreeEntry.h>
#include <fmt/color.h>

#include "VCast.h"
#include "Handlers/IAssetHandler.h"

#include <AssetsManager.vht.h>

namespace fs = std::filesystem;

namespace VulcanEngine {
	
	VCLASS()
	class VULCAN_ENGINE_API AssetsManager : public VulcanCore::VObject {
		
		VCLASS_BODY()

	public:
		struct AssetInfo {
			std::string FullPath;
			std::type_index Type;
			VAsset* LoadedAsset;
		};
		
		AssetsManager();

		VFUNCTION()
		static VulcanEngine::AssetsManager& Instance() {
			static AssetsManager instance;
			return instance;
		}
		
		AssetsManager(const AssetsManager&) = delete;
		AssetsManager& operator=(const AssetsManager&) = delete;

		void ConstructAssetTree();

		VUI::TreeEntry& GetAssetsTree() {
			return RootTree;
		}

		void SetTreeDirty(bool InDirty) {
			TreeDirty = InDirty;
		}

		template<typename T>
		T* Load(const std::string& path) {
			auto it = Handlers.find(typeid(T));
			
			if (it == Handlers.end()) {
				throw std::runtime_error("No handler for this asset type");
			}

			ResolveAsset<T>(path);
			
			return VulcanCore::Cast<T>(it->second->Load(path));
		}

		template<typename T>
		std::string ResolveAsset(const std::string& AssetPath) {
			std::string vasssetPath = AssetPath.substr(0,AssetPath.find_last_of('.')) +  ".vasset";

			if (fs::exists(vasssetPath)) {
				return vasssetPath;
			}

			auto it = Handlers.find(typeid(T));
			
			if (it == Handlers.end()) {
				throw std::runtime_error("No handler for this asset type");
			}
			
			it->second->CreateDefaultMetadata(vasssetPath,AssetPath);
			return vasssetPath;
		}
		
		template<typename T>
		TVector<T*> LoadAll(const std::string& extension) {
			auto it = Handlers.find(typeid(T));

			if (it == Handlers.end()) {
				throw std::runtime_error("No handler for this asset type");
			}

			// Modify with TVector class or smth else
			auto rawAssets = it->second->LoadAll(extension);
			TVector<T*> typedAssets;
			typedAssets.reserve(rawAssets.size());

			for (auto asset : rawAssets) {
				auto typed = static_cast<T*>(asset);
				typedAssets.push_back(typed);
			}

			return typedAssets;
		}

		
		template<typename T>
		void Save(const std::string& path,std::shared_ptr<T> asset){
			auto it = Handlers.find(typeid(T));

			if (it == Handlers.end()) {
				throw std::runtime_error("No handler for this asset type");
			}

			it->second->Save(path, asset);
		}

		template<typename T>
		void RegisterHandler(std::unique_ptr<IAssetHandler> handler) {
			Handlers[typeid(T)] = std::move(handler);
		}

		const std::string& GetUnloadedAssetName(const std::string& AssetPath);
		std::string GetUnloadedAssetPath(const std::string& AssetName);

		void MoveAsset(AssetInfo& asset, AssetInfo& targetFolder);

		static void OpenFile(std::function<void(const std::string&)> OnFileSelected);

	private:
		
		void OnStart();
		void OnQuit();
		void OnFrameBegin();
		VUI::TreeEntry BuildTree(const std::string_view& RootPath);
		void OrderTree(VUI::TreeEntry& InRoot);
		void SetTreeParent(VUI::TreeEntry& n,VUI::TreeEntry* parent);

		void EnumerateAssets(const fs::path& Path);
		std::string ReplaceExtension(const fs::path& InPath, const std::string& InNewExtension);

		bool TreeDirty{};
		
		VUI::TreeEntry RootTree{};
		std::unordered_map<std::type_index, std::unique_ptr<IAssetHandler>> Handlers{};
		std::unordered_map<fs::path,std::string> UnloadedAssets{};
	};
}


