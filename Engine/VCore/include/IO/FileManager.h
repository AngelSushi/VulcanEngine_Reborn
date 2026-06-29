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
		static FileManager& Get() {
			static FileManager instance;
			return instance;
		}

		// Modify Path in function of module 
		std::vector<std::string> LoadExtension(const std::string& Path,const std::string& Extension);

		// Not Really Correct Name, more like IsValid or Has ? 
		bool Load(std::string AbsolutePath);
		std::vector<uint8_t> Read(std::string AbsolutePath);

		// Maybe Useless Function above ? 
		std::vector<std::string> ReadAllAssets(const std::string& Extension);
		std::vector<std::string> ReadAll(const std::string& Extension,const std::string& Path);
		
	private:
		const char* AssetsDirectory = "assets/";

		std::vector<std::string> ReadAll_Internal(const std::string& Extension, const std::string& Path);
	};

}