#pragma once
#include <CoreAPI/precomp.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

namespace VulcanCore {
	class VCORE_API FileManager {
	public:
		static FileManager& Get();

		// Modify Path in function of module 
		std::vector<std::string> LoadExtension(const std::string& Path,const std::string& Extension);

		// Not Really Correct Name, more like IsValid or Has ? 
		bool Exists(std::string AbsolutePath);
		std::vector<uint8_t> Read(std::string AbsolutePath);
		bool Write(std::string AbsolutePath, const std::vector<uint8_t>& Data);

		// Maybe Useless Function above ? 
		std::vector<std::string> ReadAllAssets(const std::string& Extension);
		std::vector<std::string> ReadAll(const std::string& Extension,const std::string& Path);
		
	private:
		const char* AssetsDirectory = "assets/";

		std::vector<std::string> ReadAll_Internal(const std::string& Extension, const std::string& Path);
	};

}