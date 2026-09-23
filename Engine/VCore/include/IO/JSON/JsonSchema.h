#pragma once
#include <CoreAPI/precomp.h>

class JsonSchema {
    
public:
    static constexpr const char* SCHEMA_VERSION = "https://json-schema.org/draft/2020-12/schema";
    
    JsonSchema();
    JsonSchema(std::string InModuleDir, const nlohmann::json& InContent);
    const nlohmann::json& GetContent() const;
    std::string ToString(int Indent = 2) const;
    const std::string& GetModuleDir() const;
    bool WriteToFile(const std::string& Path) const;

private:
    std::string ModuleDir;
    nlohmann::json Content; 
};
