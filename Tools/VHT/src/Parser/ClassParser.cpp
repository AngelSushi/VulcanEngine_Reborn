#include <iostream>
#include <Parser/ClassParser.h>
#include "Parser/Utils.h"

namespace ClassParser {
    std::vector<ClassInfo> ParseClasses(std::string& content) {
        std::vector<ClassInfo> out;

        const std::string macro = "VCLASS(";
        size_t searchPos = 0;

        while (true) {
            size_t macroPos = content.find(macro, searchPos);

            if (macroPos == std::string::npos) {
                break;
            }

            std::string_view subContent(content.c_str() + macroPos);
            ClassInfo classInfo;

            std::string str = std::string(subContent);
            if (ParseClass(classInfo,str)) {
                out.push_back(classInfo);
            }

            searchPos = macroPos + macro.size();
        }

        return out;
    }

    bool ParseClass(ClassInfo& out, std::string& content) {
        const std::string macro = "VCLASS(";
        size_t macroPos = content.find(macro);
        
        if (macroPos == std::string::npos) {
            return false;
        }

        size_t lineEnd = content.find('\n', macroPos);
        std::string nextLine = Utils::GetLine(content,lineEnd + 1);
        size_t classPos = nextLine.find("class");

        if (classPos == std::string::npos) {
            return false;
        }

        auto parts = Utils::SplitWords(content,lineEnd + classPos, [](char c){
            return std::isspace(c);
        });

        out.Name = parts.size() == 6 ? parts[1] : parts[2];
        out.dll = parts.size() == 7 ? parts[1] : "";
        out.ParentName = parts[parts.size() - 2];
        
        out.Namespaces = Utils::DetectNamespaces(content,lineEnd + classPos);

        return true;
    }
}
