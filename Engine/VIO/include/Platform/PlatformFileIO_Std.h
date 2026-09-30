#pragma once
#include <CoreAPI/precomp.h>

#include "PlatformFileIO.h"
#include "VPath.h"


class VIO_API PlatformFileIO_Std : public PlatformFileIO {

public:

	bool FileExists(const VPath& Path) override;
	bool DirectoryExists(const VPath& Path) override;
	
	bool MakeDirectory(const std::string& Path) override;
	bool DeleteDirectory(const std::string& Path) override;
};

