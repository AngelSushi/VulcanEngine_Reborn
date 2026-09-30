#pragma once
#include <CoreAPI/precomp.h>

#include "VPath.h"


class VIO_API PlatformFileIO {

public:
	virtual ~PlatformFileIO() = default;
	
	virtual VPhysicalPath Root() = 0;
	virtual bool Write(VPhysicalPath Path,const std::vector<uint8_t>& Data) = 0;
	virtual bool Read(const VPath& Path,std::vector<uint8_t>& Out) = 0;
	virtual bool Delete(const VPath& Path) = 0;
	virtual bool Copy(const VPath& Src,const VPath& Dst) = 0;
	virtual bool Move(const VPath& Src,const VPath& Dst) = 0;

	virtual bool FileExists(const VPath& Path) = 0;
	virtual bool DirectoryExists(const VPath& Path) = 0;
	virtual bool MakeDirectory(const std::string& Path) = 0;
	virtual bool DeleteDirectory(const std::string& Path) = 0;
	
};

