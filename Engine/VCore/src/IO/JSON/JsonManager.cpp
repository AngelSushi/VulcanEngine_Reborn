#include <IO/JSON/JsonManager.h>

JsonManager& JsonManager::Get() {
    static JsonManager Instance;
    return Instance;
}

void JsonManager::RegisterSchema(std::string TypeName,std::string ModuleDir, std::function<nlohmann::json()> Builder) {
    Builders[TypeName] = { ModuleDir, Builder};
}

void JsonManager::GenerateAll(const std::string& OutputDir) {
    for (auto& Builder : Builders) {
        auto& [ModuleDir, BuildFunc] = Builder.second;
        nlohmann::json Content = BuildFunc();
        Cache[Builder.first] = JsonSchema(ModuleDir,Content);
    }

    for (auto& [TypeName, Schema] : Cache) {
        std::string FilePath = Schema.GetModuleDir() + "/" + OutputDir + "/" + TypeName + ".schema.json";
        if (!Schema.WriteToFile(FilePath)) {
            std::cerr << "Error writing to file " << FilePath << "\n";
        }
    }
}

const JsonSchema* JsonManager::GetSchema(const std::string& TypeName) const {
    return Cache.contains(TypeName) ? &Cache.at(TypeName) : nullptr;
}
