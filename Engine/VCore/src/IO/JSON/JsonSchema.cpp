#include <IO/JSON/JsonSchema.h>

#include "IO/FileManager.h"

JsonSchema::JsonSchema() {}
JsonSchema::JsonSchema(std::string InModuleDir,const nlohmann::json& InContent) : ModuleDir(std::move(InModuleDir)), Content(InContent) {}

const nlohmann::json& JsonSchema::GetContent() const {
    return Content;
}

std::string JsonSchema::ToString(int Indent) const {
    return Content.dump(Indent);
}

const std::string& JsonSchema::GetModuleDir() const {
    return ModuleDir;
}

bool JsonSchema::WriteToFile(const std::string& Path) const {
    if (Content.is_null()) {
        std::cerr << "Error: Attempted to write an empty JSON schema to file: " << Path << "\n";
        return false;
    }

    std::string Serialized = ToString(2);
    std::vector<uint8_t> Bytes(Serialized.begin(), Serialized.end());
    return VulcanCore::FileManager::Get().Write(Path, Bytes);
}
