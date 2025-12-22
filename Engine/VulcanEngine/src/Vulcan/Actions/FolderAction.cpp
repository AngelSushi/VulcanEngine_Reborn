#include <Actions/FolderAction.h>

#include <IRegistry.h>

namespace fs = std::filesystem;

namespace VulcanEngine {
	void FolderAction::RegisterBindings() {
		using namespace VUI;
		
		BindingRegistry.Register(Binding::Register("Folder::ListFolders",this,&FolderAction::ListFolders));
		BindingRegistry.Register(Binding::Register("Folder::ShowInFolder",this,&FolderAction::ShowInFolder));
	}

	TVector<std::string>& FolderAction::ListFolders() {
		Folders.clear();

		fs::path root("assets/");
		Folders.push_back(root.string());

		if (!fs::exists(root) || !fs::is_directory(root)) {
			fmt::print("FolderAction: 'assets/' not found!\n");
			return Folders;  // Liste seulement ["assets/"]
		}
		
		try
		{
			for (const auto& entry : fs::directory_iterator(root)) {
				if (entry.is_directory()) {
					Folders.push_back(entry.path().string());
				}
			}
		}catch (std::exception& e) {
			fmt::print("Error listing folders: {}\n", e.what());
		}
		
		return Folders;
	}

	void FolderAction::ShowInFolder(const std::string& InPath) {
		fs::path path = fs::absolute(InPath);
		std::string command = "explorer /select,\"" + path.string() + "\"";
		system(command.c_str());
	}
}

