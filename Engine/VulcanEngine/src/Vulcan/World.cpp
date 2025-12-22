#include <World.h>

#include <IRegistry.h>
#include <Types/Assets/AssetsManager.h>
#include <Types/Assets/Scene.h>

#include "EditorContext.h"
#include "TVector.h"
#include "Components/ComponentRegistry.h"

namespace fs = std::filesystem;

namespace VulcanEngine {
	World::World() {
		BindingRegistry.Register(VUI::Binding::Register("World::GetEntities",this,&World::GetEntities));
	}

	void World::LoadScene(const std::string& SceneName) {
		auto scenePath = AssetsManager::Instance().GetUnloadedAssetPath(SceneName);

		if (!scenePath.empty()) {
			CurrentScene = AssetsManager::Instance().Load<Scene>(scenePath);
			BuildTree();
		}
	}

	void World::LoadScene(const fs::path& ScenePath) {
		AssetsManager::Instance().Load<Scene>(ScenePath.string());
	}

	VUI::TreeEntry& World::GetEntities() {
		return RootTree;
	}

	TVector<std::string>& World::GetAvailableComponentsFor(Entity* Ent) const {
		static TVector<std::string> available; // Maybe static + ref

		if (ComponentRegistry::Instance().GetRegistry().size() != available.size()) {
			available.clear();

			for (auto& [compName, compType] : ComponentRegistry::Instance().GetRegistry()) {
				available.push_back(compName);
			}
		}
		return available;
	}

	void World::BuildTree() {
		RootTree = {};
		
		RootTree.EntryName = CurrentScene->GetName();
		RootTree.Payload = &CurrentScene;
		RootTree.IsDirectory = true;
		

		for (auto& entity : CurrentScene->GetEntities()) {
			VUI::TreeEntry childNode{};
			childNode.EntryName = entity->GetName();
			childNode.Payload = entity;
			childNode.IsDirectory = false;
			childNode.Parent = &RootTree;
			childNode.OnSelectedChanged = [this](VUI::TreeEntry* node, bool selected) {
				if (selected) {
					VUI::EditorContext::Instance().AddSelectedEntity(node);
				}
				else {
					VUI::EditorContext::Instance().RemoveSelectedEntity(node);
				}
			};

			RootTree.Children.push_back(childNode);
		}

	}
}
