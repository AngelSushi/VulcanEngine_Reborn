#pragma once
#include <CoreAPI/precomp.h>
#include <functional>
#include <string>

#include <IO/JSON/JsonSchema.h>


class VCORE_API JsonManager {

public:
    static JsonManager& Get();
    void RegisterSchema(std::string TypeName,std::string ModuleDir, std::function<nlohmann::json()> Builder);
    void GenerateAll(const std::string& OutputDir);
    const JsonSchema* GetSchema(const std::string& TypeName) const;

private:
    // Std::pair maybe not be supported by all plateforms, we need to replace it after 
    std::unordered_map<std::string,std::pair<std::string,std::function<nlohmann::json()>>> Builders;
    std::unordered_map<std::string,JsonSchema> Cache;
};
