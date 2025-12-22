#pragma once
#include <string>
#include <vector>
#include <functional>

namespace Utils {
    
    void RemoveEmptyLines(std::string& Content);
    std::string GetLine(const std::string& Content,size_t Pos);
    std::vector<std::string> SplitWords(const std::string& Content,size_t Pos,std::function<bool(char)> Delimiter);
    std::vector<std::string> Tokenize(const std::string& Content, std::function<bool(char)> Delimiter);
    std::vector<std::string> DetectNamespaces(const std::string& Content,size_t EndPos);
    std::string ExtractBetween(const std::string& Content,char Start,char End);

    void Trim(std::string& Str);
}
