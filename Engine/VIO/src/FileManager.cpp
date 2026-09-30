#include <FileManager.h>

FileManager& FileManager::Get() {
    static FileManager instance;
    return instance;
}

void FileManager::SetPlatform(std::unique_ptr<PlatformFileIO> InPlatform) {
    if (Platform) {
        // Warning : cant set platform twice
        return;
    }

    Platform = std::move(InPlatform);
}

VPhysicalPath FileManager::Root() const {
    return Platform->Root();
}

bool FileManager::ResolvePath(const VPath& In,VPhysicalPath& Out) const {
    if (const VPhysicalPath* P_Path = dynamic_cast<const VPhysicalPath*>(&In)) {
        Out = *P_Path;
        return true;
    }
    if (const VRelativePath* R_Path = dynamic_cast<const VRelativePath*>(&In)) {
        Out = R_Path->ToPhysical(Root());
        return true;
    }
    if (const VVirtualPath* V_Path = dynamic_cast<const VVirtualPath*>(&In)) {
        // Add Core here for virtual path
    }

    return false;
}

bool FileManager::Write(const VPath& Path, const std::vector<uint8_t>& Data) {
    if (Path.IsDirectory()) {
        return false;
    }
    
    return WithResolvedPath(Path,[&](const VPhysicalPath& ResolvedPath) {
        return Platform->Write(ResolvedPath,Data);
    });
}

bool FileManager::Read(const VPath& Path,std::vector<uint8_t>& Out) {
    if (Path.IsDirectory()) {
        return false;
    }
    
    return WithResolvedPath(Path,[&](const VPhysicalPath& ResolvedPath) {
        return Platform->Read(ResolvedPath,Out);
    });
}

bool FileManager::Delete(const VPath& Path) {
    if (Path.IsDirectory()) {
        return false;
    }
    
    return WithResolvedPath(Path,[&](const VPath& ResolvedPath) {
        return Platform->Delete(ResolvedPath);
    });
}

bool FileManager::Copy(const VPath& Src, const VPath& Dst) {
    if (Src.IsDirectory() || Dst.IsDirectory()) {
        return false;
    }
    
    return WithResolvedPath(Src,[&](const VPath& SrcResolved){
        return WithResolvedPath(Dst,[&](const VPath& DstResolved){
            return Platform->Copy(Src,Dst);
        });
    });
}

bool FileManager::Move(const VPath& Src, const VPath& Dst) {
    if (Src.IsDirectory() || Dst.IsFile()) {
        return false;
    }
    
    return WithResolvedPath(Src,[&](const VPath& SrcResolved) {
        return WithResolvedPath(Dst,[&](const VPath& DstResolved) {
            return Platform->Move(Src,Dst);
        });
    });
}

bool FileManager::FileExists(const VPath& FilePath) {
    if (FilePath.IsDirectory()) {
        return false;
    }

    return WithResolvedPath(FilePath,[&](const VPath& ResolvedPath) {
        return Platform->FileExists(ResolvedPath);
    });
    
}

bool FileManager::DirectoryExists(const VPath& DirectoryPath) {
    if (DirectoryPath.IsFile()) {
        return false;
    }

    return WithResolvedPath(DirectoryPath,[&](const VPath& ResolvedPath) {
        return Platform->DirectoryExists(ResolvedPath);
    });
}

bool FileManager::MakeDirectory(const VPath& DirectoryPath, bool bRecursive) {
    if (DirectoryPath.IsFile()) {
        return false;
    }

    VRelativePath Relative;
    if (const VPhysicalPath* P_Path = dynamic_cast<const VPhysicalPath*>(&DirectoryPath)) {
        // Not really good way to do it i guess ? 
        VPhysicalPath Root_ = Root();
        Relative = P_Path->ToRelative(&Root_);
    }
    else if (const VRelativePath* R_Path = dynamic_cast<const VRelativePath*>(&DirectoryPath)) {
        Relative = *R_Path;
    }
    // Add Virtual

    std::vector<std::string> Directories;
    
    if (bRecursive) {
        FindDirectoryRecursive(Directories,Relative.String());
    }
    
    for (const std::string& Directory : Directories) {
        if (!Platform->MakeDirectory(Directory)) {
            return false;
        }
    }

    return true;
}

bool FileManager::DeleteDirectory(const VPath& DirectoryPath) {
    if (DirectoryPath.IsFile()) {
        return false;
    }

    return WithResolvedPath(DirectoryPath,[&](const VPath& ResolvedPath) {
        return Platform->DeleteDirectory(ResolvedPath.String());
    });
}

std::string FileManager::FindDirectory(const std::string& StartDirectory) {
    size_t Index = StartDirectory.find_last_of("/\\",StartDirectory.length() - 1);

    if (Index == std::string::npos) {
        return StartDirectory;
    }

    return StartDirectory.substr(0,Index);
}

void FileManager::FindDirectoryRecursive(std::vector<std::string>& FoundDirectories, const std::string& StartDirectory) {
    size_t Index = StartDirectory.find_last_of("/\\",StartDirectory.length());

    if (Index == std::string::npos) {
        return;
    }

    std::string CurrentDirectory = StartDirectory.substr(0,Index);
    FoundDirectories.push_back(CurrentDirectory);
    FindDirectoryRecursive(FoundDirectories,CurrentDirectory);
}

