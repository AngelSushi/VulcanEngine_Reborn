#include <iostream>
#include <Parser/EnumParser.h>
#include "Parser/Utils.h"

namespace EnumParser {
    std::vector<EnumInfo> ParseEnums(std::string& content) {
        std::vector<EnumInfo> out;

        const std::string macro = "VENUM(";
        size_t searchPos = 0;

        while (true) {
            size_t macroPos = content.find(macro, searchPos);

            if (macroPos == std::string::npos) {
                break;
            }

            std::string_view subContent(content.c_str() + macroPos);
            EnumInfo enumInfo;

            std::string str = std::string(subContent);
            if (ParseEnum(enumInfo,str)) {
                out.push_back(enumInfo);
            }

            searchPos = macroPos + macro.size();
        }

        return out;
    }

    void FindParentName(EnumInfo& enum_info,const std::string& content) {
        const std::string classMacro = "VCLASS(";
        const std::string structMacro = "VSTRUCT(";

        size_t macroPos = content.find(classMacro);

        if (macroPos == std::string::npos) {
            macroPos = content.find(structMacro);

            if (macroPos == std::string::npos) {
                return;
            }
        }
        
        size_t lineEnd = content.find('\n', macroPos);
        std::string nextLine = Utils::GetLine(content,lineEnd + 1);

        auto parts = Utils::SplitWords(nextLine,0, [](char c) {
            return std::isspace(c);
        });

        enum_info.ParentName = parts.size() == 6 ? parts[1] : parts[2];
    }

    bool ParseEnum(EnumInfo& out,const std::string& content) {
        const std::string macro = "VENUM(";
        size_t macroPos = content.find(macro);

        if (macroPos == std::string::npos) {
            return false;
        }

        size_t lineEnd = content.find('\n', macroPos);
        std::string nextLine = Utils::GetLine(content,lineEnd + 1);
        
        auto parts = Utils::SplitWords(nextLine,0, [](char c) {
            return std::isspace(c);
        });
        
        Utils::Trim(parts[2]);
        out.Name = parts[2]; // Warning if DLL exported enum

        FindParentName(out,content);

        size_t braceOpen = content.find('{', lineEnd + 1);
        size_t braceClose = content.find('}', braceOpen + 1);

        std::string valuesContent = content.substr(braceOpen + 1, braceClose - braceOpen - 1);
        for (auto& part : Utils::SplitWords(valuesContent,0,[](char c) { return c == ','; })) {
            Utils::Trim(part);
            out.Values.push_back(std::move(part));
        }
        
        return true;
    }
}
