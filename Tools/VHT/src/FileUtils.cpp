#include <filesystem>
#include <FileUtils.h>
#include <fstream>

namespace FileUtils {
    void WriteFile(const std::string& Path, const std::string& Text) {
        create_directories(std::filesystem::path(Path).parent_path());

        std::ofstream f(Path, std::ios::trunc);
        f << Text;
    }
}
