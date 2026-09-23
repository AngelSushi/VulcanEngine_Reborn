#include <IO/FileManager.h>

VulcanCore::FileManager& VulcanCore::FileManager::Get() {
    static FileManager instance;
    return instance;
}

std::vector<std::string> VulcanCore::FileManager::LoadExtension(const std::string& Path,const std::string& Extension) {

    std::vector<std::string> Paths;
    
    for (const auto& entry : fs::directory_iterator(Path)) {
    
        if (entry.is_directory()) {
            auto subPaths = LoadExtension(entry.path().string(),Extension);
            Paths.insert(Paths.end(), subPaths.begin(), subPaths.end());
        }
        else if (entry.is_regular_file() && entry.path().extension() == Extension)
        {
            // maybe need absolute path on the computer ? 
            Paths.push_back(entry.path().string());
        }
    }
    
    return Paths;
}

bool VulcanCore::FileManager::Exists(std::string AbsolutePath) {
    return fs::exists(AbsolutePath) && fs::is_regular_file(AbsolutePath);
}

std::vector<uint8_t> VulcanCore::FileManager::Read(std::string AbsolutePath) {
    std::ifstream File(AbsolutePath, std::ios::binary | std::ios::ate);

    if (!File.is_open()) {
        return {};
    }

    std::streamsize FileSize = File.tellg();
    File.seekg(0, std::ios::beg);

    std::vector<uint8_t> Buffer(FileSize);
    File.read(reinterpret_cast<char*>(Buffer.data()),FileSize);

    return Buffer;
}

bool VulcanCore::FileManager::Write(std::string AbsolutePath, const std::vector<uint8_t>& Data) {
    // Create directories if they don't exist
    fs::path FilePath(AbsolutePath);
    std::error_code ErrorCode;
    fs::create_directories(FilePath.parent_path(),ErrorCode);

    if (ErrorCode) {
        return false;
    }

    std::ofstream File(AbsolutePath, std::ios::binary);

    if (!File.is_open()) {
        return false;
    }
    
    File.write(reinterpret_cast<const char*>(Data.data()), Data.size());
    return File.good();
}

std::vector<std::string> VulcanCore::FileManager::ReadAllAssets(const std::string& Extension) {
    return ReadAll_Internal(Extension, AssetsDirectory);
}

std::vector<std::string> VulcanCore::FileManager::ReadAll(const std::string& Extension, const std::string& Path) {
    return ReadAll_Internal(Extension, Path);
}

std::vector<std::string> VulcanCore::FileManager::ReadAll_Internal(const std::string& Extension,const std::string& Path) {
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
