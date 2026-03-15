#pragma once
#include <CoreAPI/precomp.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

namespace VulcanCore {

	class FileManager {
	public:
		static std::vector<std::string> ReadAllAssets(const std::string& Extension) {
			return ReadAll_Internal(Extension, AssetsDirectory);
		}

		static std::vector<std::string> ReadAll(const std::string& Extension,const std::string& Path) {
			return ReadAll_Internal(Extension, Path);
		}
		
	private:
		constexpr static const char* AssetsDirectory = "assets/";

		static std::vector<std::string> ReadAll_Internal(const std::string& Extension, const std::string& Path) {
			std::vector<std::string> FilesContent;

			for (const auto& entry : fs::directory_iterator(Path)) {
				if (entry.is_directory()) {
					auto subDirectoryContents = ReadAll_Internal(Extension, entry.path().string());
					FilesContent.insert(FilesContent.end(), subDirectoryContents.begin(), subDirectoryContents.end());
				} else if (entry.path().extension() == Extension) {
					std::ifstream file(entry.path().string());
					if (file.is_open()) {
						std::stringstream buffer;
						buffer << file.rdbuf();
						FilesContent.push_back(buffer.str());
					} else {
						std::cerr << "Error during reading file: " << entry.path().string() << std::endl;
					}
				}
			}

			return FilesContent;
		}
	};

}