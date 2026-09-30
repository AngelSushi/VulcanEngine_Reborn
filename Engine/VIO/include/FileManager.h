#pragma once
#include <CoreAPI/precomp.h>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

#include "VPath.h"
#include "Platform/PlatformFileIO.h"

namespace fs = std::filesystem;

class VIO_API FileManager {
public:
	static FileManager& Get();


	void SetPlatform(std::unique_ptr<PlatformFileIO> InPlatform);
	VPhysicalPath Root() const;
	
	bool Write(const VPath& Path,const std::vector<uint8_t>& Data);
	bool Read(const VPath& Path,std::vector<uint8_t>& Out);

	bool Delete(const VPath& Path);
	bool Copy(const VPath& Src, const VPath& Dst);
	bool Move(const VPath& Src, const VPath& Dst);

	bool FileExists(const VPath& FilePath);
	bool DirectoryExists(const VPath& DirectoryPath);
	bool MakeDirectory(const VPath& DirectoryPath, bool bRecursive = false);
	bool DeleteDirectory(const VPath& DirectoryPath);
	
	std::string FindDirectory(const std::string& StartDirectory);
	void FindDirectoryRecursive(std::vector<std::string>& FoundDirectories,const std::string& StartDirectory);

	template<typename E>
	bool WithResolvedPath(const VPath& Path, E&& Execute) {
		if (!Platform) {
			return false;
		}

		VPhysicalPath ResolvedPath;

		if (!ResolvePath(Path, ResolvedPath)) {
			return false;
		}

		return std::forward<E>(Execute)(ResolvedPath);
	}

private:
	const char* AssetsDirectory = "assets/";

	bool ResolvePath(const VPath& In,VPhysicalPath& Out) const;

	std::unique_ptr<PlatformFileIO> Platform;
	
};

