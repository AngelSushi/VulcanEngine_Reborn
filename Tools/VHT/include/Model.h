#pragma once
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

struct MetaExtract {
    using MetaValue = std::variant<std::string, std::vector<std::string>>;
    using MetaMap = std::unordered_map<std::string, MetaValue>;
    
    std::vector<std::string> SimpleAttributes;
    MetaMap MetaPairs;
};

struct PropertyInfo {
    std::string Name;
    std::string Type;
    MetaExtract Meta;
};

struct FunctionInfo {
    std::string Name;
    std::string ReturnType;
    std::vector<std::pair<std::string,std::string>> Parameters;
    bool isStatic;
};

struct TypeInfoBase {
    std::string Name;
    std::vector<std::string> Namespaces;
    std::string ParentName;
    std::string dll; // For DLL import/export macros, not sure if struct can have dll but just in case
    std::string RootPath;

    std::string GetRelativePath() const {
        size_t pos = RootPath.find("include");
        std::string rel = RootPath.substr(pos + std::string("include").size() + 1);

        return rel;
    }
    
    std::string GetFullName() const {
        if (Namespaces.empty()) {
            return Name;
        }

        std::string fullname;

        for (auto& ns : Namespaces) {
            fullname += ns + "::";
        }

        fullname += Name;
        return fullname;
    }
};

struct ClassInfo : TypeInfoBase {
    std::vector<FunctionInfo> Functions;
    std::vector<PropertyInfo> Properties;
};

struct StructInfo : TypeInfoBase {
    std::vector<PropertyInfo> Properties;
};

struct EnumInfo {
    std::string Name;
    std::vector<std::string> Namespaces;
    std::vector<std::string> Values;
    std::string ParentName;
    std::string RootPath;

    std::string GetRelativePath() const {
        size_t pos = RootPath.find("include");
        std::string rel = RootPath.substr(pos + std::string("include").size() + 1);

        return rel;
    }

    std::string GetFullName() const {
        if (Namespaces.empty()) {
            return Name;
        }

        std::string fullname;

        for (auto& ns : Namespaces) {
            fullname += ns + "::";
        }

        fullname += Name;
        return fullname;
    }
};
