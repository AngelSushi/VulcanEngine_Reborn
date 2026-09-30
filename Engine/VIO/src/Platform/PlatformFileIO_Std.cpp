#include <Platform/PlatformFileIO_Std.h>

bool PlatformFileIO_Std::FileExists(const VPath& Path) {
    if (!Path.IsFile()) {
        return false;
    }
    
    return std::filesystem::exists(Path.String());
}

bool PlatformFileIO_Std::DirectoryExists(const VPath& Path) {
    if (Path.IsFile()) {
        return false;
    }
    
    return std::filesystem::exists(Path.String());
}

bool PlatformFileIO_Std::MakeDirectory(const std::string& Path) {
    return std::filesystem::create_directory(Path);
}

bool PlatformFileIO_Std::DeleteDirectory(const std::string& Path) {
    return std::filesystem::remove(Path);
}
