#include <functional>
#include <iostream>
#include <sstream>
#include <Parser/Utils.h>

namespace Utils {
    void RemoveEmptyLines(std::string& Content) { // Maybe Trim is the same as this?
        std::stringstream in(Content);
        std::string line;
        std::string out;
        
        while (std::getline(in,line)) {
            bool isEmpty = true;

            for (char c : line) {
                if (std::isspace(c)) {
                    isEmpty = false;
                    break;
                }
            }

            if (!isEmpty) {
                out += line + "\n";
            }
        }

        Content = out;
    }

    std::string GetLine(const std::string& Content, size_t Pos) {
        if (Pos >= Content.size() || Pos == std::string::npos)
            return "";
        
        size_t lineStart = Content.rfind('\n', Pos);
        if (lineStart == std::string::npos)
            lineStart = 0;
        else
            lineStart++;
        
        size_t lineEnd = Content.find('\n', Pos);
        if (lineEnd == std::string::npos)
            lineEnd = Content.size();
        
        return Content.substr(lineStart, lineEnd - lineStart);
    }

    std::vector<std::string> Tokenize(const std::string& Content, std::function<bool(char)> Delimiter) {
        std::vector<std::string> out;
        std::string current;

        for (char c : Content) {
            if (Delimiter(c)) {
                if (!current.empty()) {
                    out.push_back(current);
                    current.clear();
                }
            }
            else {
                current.push_back(c);
            }
        }

        if (!current.empty()) {
            out.push_back(current);
        }

        return out;
    }

    std::vector<std::string> SplitWords(const std::string& Content,size_t Pos,std::function<bool(char)> Delimiter) {
        std::string line = GetLine(Content,Pos);
        return Tokenize(line,Delimiter);
    }

    std::vector<std::string> DetectNamespaces(const std::string& Content,size_t EndPos) {
        std::vector<std::string> out;
        
        std::string Search = Content.substr(0,EndPos);
        std::stringstream in(Search);
        std::string line;
        
        while (std::getline(in,line)) {
            size_t namespacePos = line.find("namespace");

            if (namespacePos != std::string::npos) {
                size_t start = namespacePos + std::strlen("namespace") + 1;
                size_t end = line.find_first_of(" {", start);
                std::string namespaceName = line.substr(start, end - start);

                if (line.find("=") == std::string::npos) {
                    if (namespaceName.find("::") != std::string::npos) {
                        auto parts = Tokenize(namespaceName, [](char c) { return c == ':'; });
                        out.insert(out.end(),parts.begin(),parts.end());
                    }
                    else {
                        out.push_back(namespaceName);
                    }
                }
            }
        }

        return out;
    }

    std::string ExtractBetween(const std::string& Content, char Start, char End) {
        size_t startPos = Content.find(Start);

        if (startPos == std::string::npos) {
            return "";
        }

        size_t endPos = Content.find(End,startPos + 1);

        if (endPos == std::string::npos) {
            return "";
        }

        return Content.substr(startPos + 1, endPos - startPos - 1);
    }

    void Trim(std::string& Str) {
        Str.erase(Str.begin(), std::find_if(Str.begin(), Str.end(), [](unsigned char c) {
            return !std::isspace(c);
        }));

        Str.erase(std::find_if(Str.rbegin(), Str.rend(), [](unsigned char c) {
            return !std::isspace(c);
        }).base(), Str.end());
    }
}
