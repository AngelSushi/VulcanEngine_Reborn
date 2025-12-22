
#include <iostream>
#include <Parser/FunctionParser.h>
#include "Parser/Utils.h"

namespace FunctionParser {
    void ParseAllFunctions(ClassInfo& out, std::string& content) {
        const std::string macro = "VFUNCTION(";
        size_t searchPos = 0;

        while (true) {
            size_t macroPos = content.find(macro, searchPos);

            if (macroPos == std::string::npos) {
                break;
            }

            std::string_view subContent(content.c_str() + macroPos);

            std::string str = std::string(subContent);
            ParseFunction(out,str);
            searchPos = macroPos + macro.size();
        }
    }

    void ParseFunction(ClassInfo& Out, std::string& Content) {
        constexpr const char* MACRO = "VFUNCTION(";
        FunctionInfo fInfo;

        size_t macroPos = Content.find(MACRO);

        if (macroPos == std::string::npos) {
            return;
        }

        size_t lineEnd = Content.find('\n', macroPos);
        std::string functionLine = Utils::GetLine(Content, lineEnd + 1);

        Utils::Trim(functionLine);
        std::string args = Utils::ExtractBetween(functionLine, '(', ')');
        auto argParts = Utils::SplitWords(args,0, [](char c) {
            return c == ',';
        });

        for (auto& part : argParts) {

            auto typeAndName = Utils::SplitWords(part,0, [](char c) {
                return std::isspace(c);
            });

            std::string type = typeAndName.size() == 2 ? typeAndName[0] : typeAndName[0] + " " + typeAndName[1];
            std::string paramName = typeAndName[typeAndName.size() - 1];
            
            Utils::Trim(type);
            Utils::Trim(paramName);
            fInfo.Parameters.push_back({ type, paramName });
        }

        std::string beforeParams = functionLine.substr(0, functionLine.find('('));
        auto defParts = Utils::SplitWords(beforeParams,0, [](char c) {
            return std::isspace(c);
        });

        fInfo.isStatic = defParts.size() == 3 && defParts[0] == "static";

        fInfo.ReturnType = defParts.size() == 3 ? defParts[1] : defParts[0];
        fInfo.Name = defParts[defParts.size() - 1];

        Out.Functions.push_back(std::move(fInfo));
    }
} 
