
#include <ostream>
#include <Parser/Parser.h>

#include "Parser/ClassParser.h"
#include "Parser/EnumParser.h"
#include "Parser/FunctionParser.h"
#include "Parser/PropertyParser.h"
#include "Parser/StructParser.h"
#include "Parser/Utils.h"

namespace Parser {
    
    ParseResult Parse(const std::vector<std::pair<std::string, std::string>>& Files) {
        ParseResult Result;

        for (auto [path,content] : Files) {
            Utils::RemoveEmptyLines(content);

            auto classes = ClassParser::ParseClasses(content);
            for (auto& c : classes) {
                c.Namespaces = Utils::DetectNamespaces(content,content.size());
                c.RootPath = path;

                PropertyParser::ParseAllProperties(c,content);
                FunctionParser::ParseAllFunctions(c,content);

                Result.Classes.push_back(c);
            }

            auto structs = StructParser::ParseStructs(content);
            for (auto& s : structs) {
                s.Namespaces = Utils::DetectNamespaces(content,content.size());
                s.RootPath  = path;

                PropertyParser::ParseAllProperties(s,content);

                Result.Structs.push_back(s);
            }

            auto enums = EnumParser::ParseEnums(content);
            for (auto& e : enums) {
                e.Namespaces = Utils::DetectNamespaces(content,content.size());
                e.RootPath = path;

                Result.Enums.push_back(e);
            }
        }

        return Result;
    }
}
