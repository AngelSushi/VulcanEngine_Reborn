#include <Scanner/Scanner.h>
#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

namespace Scanner {

    static void ListFolder(std::vector<std::pair<std::string,std::string>>& Out, const std::filesystem::path& Path) {
        fs::path blacklist = fs::absolute("Engine/VCore/include/Reflection");
        
        for (auto& entry : fs::directory_iterator(Path)) {
            if (entry.is_directory()) {
                ListFolder(Out,entry.path().string());
            }

            if (entry.path().parent_path() != blacklist && entry.is_regular_file() && entry.path().extension() == ".h") {
                std::ifstream f(entry.path());
                std::stringstream buffer;
                buffer << f.rdbuf();

                Out.emplace_back(entry.path().string(), buffer.str());
            }
        }
    }
    
    std::vector<std::pair<std::string, std::string>> ScanHeaders(const std::string& Root) {
        std::vector<std::pair<std::string, std::string>> out;

        if (!exists(fs::path(Root))) {
            create_directories(fs::path(Root));
            std::cout << "[VHT] Successfully created directories" << std::endl;
        }
        
        for (auto& entry :fs::directory_iterator(Root)) {
            if (entry.is_directory()) {
                ListFolder(out,entry.path().string());
            }
        } 

        return out;
    }
}