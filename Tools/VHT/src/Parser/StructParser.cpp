#include <iostream>
#include <Parser/StructParser.h>
#include "Parser/Utils.h"

namespace StructParser {
    std::vector<StructInfo> ParseStructs(std::string& content) {
        std::vector<StructInfo> out;

        const std::string macro = "VSTRUCT(";
        size_t searchPos = 0;

        while (true) {
            size_t macroPos = content.find(macro, searchPos);

            if (macroPos == std::string::npos) {
                break;
            }

            std::string_view subContent(content.c_str() + macroPos);
            StructInfo structInfo;

            std::string str = std::string(subContent);
            if (ParseStruct(structInfo,str)) {
                out.push_back(structInfo);
            }

            searchPos = macroPos + macro.size();
        }

        return out;
    }

    bool ParseStruct(StructInfo& Out, std::string& Content) {
        const std::string macro = "VSTRUCT(";
        size_t macroPos = Content.find(macro);
        
        if (macroPos == std::string::npos) {
            return false;
        }

        size_t lineEnd = Content.find('\n', macroPos);
        std::string nextLine = Utils::GetLine(Content,lineEnd + 1);
        size_t classPos = nextLine.find("struct");

        if (classPos == std::string::npos) {
            return false;
        }

        auto parts = Utils::SplitWords(Content,lineEnd + classPos, [](char c){
            return std::isspace(c);
        });

        Out.Name = parts[1];// Warning if DLL exported struct
        Out.ParentName = parts.size() > 3 ? parts[parts.size() - 2] : "";

        Out.Namespaces = Utils::DetectNamespaces(Content,lineEnd + classPos);

        return true;
    }
}
