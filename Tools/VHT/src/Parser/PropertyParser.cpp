#include <iostream>
#include <optional>
#include <Parser/PropertyParser.h>
#include "Parser/Utils.h"

namespace PropertyParser {
    std::vector<std::string> ParseArgumentList(const std::string& s) {
        std::vector<std::string> out;
        std::string current;

        int depth = 0;

        for (char c : s) {
            if (c == '[' || c == '(') {
                depth++;
                current += c;
            }
            else if (c == ']' || c == ')') {
                depth--;
                current += c;
            }
            else if (c == ',' && depth == 0) {
                Utils::Trim(current);
                
                if (!current.empty()) {
                    out.push_back(current);
                }

                current.clear();
            }
            else {
                current += c;
            }
        }

        Utils::Trim(current);
        if (!current.empty()) {
            out.push_back(current);
        }
        return out;
    }

    MetaExtract ExtractMeta(const std::vector<std::string>& args) {
        MetaExtract metaExtract;

        for (const auto& arg : args) {
            if (arg.starts_with("meta=")) {

                size_t eqPos = arg.find('=');
                if (eqPos == std::string::npos) {
                    continue;
                }

                std::string right = arg.substr(eqPos + 1);
                Utils::Trim(right);

                if (right.size() >= 2 && right.front() == '[' && right.back() == ']') {
                    std::string allMetas = right.substr(1, right.size() - 2);

                    auto parts = ParseArgumentList(allMetas);
                    
                    for (auto& part : parts) {
                        auto subParts = Utils::SplitWords(part,0,[](char c){ return c == '='; });

                        if (subParts.size() == 2) {
                            std::string key = subParts[0];
                            std::string value = subParts[1];

                            if (value.find('[') == 0 && value.find(']') == value.size() - 1) {
                                value = value.substr(1, value.size() - 2);
                                auto vals = Utils::SplitWords(value,0,[](char c){ return c == ','; });
                                metaExtract.MetaPairs[key] = vals;
                            }
                            else {
                                metaExtract.MetaPairs[key] = value;
                            }
                        }
                    }
                }
            }
            else {
                if (arg.find("=") != std::string::npos) {
                    auto parts = Utils::SplitWords(arg,0,[](char c){return c == '='; });
                    
                    if (parts.size() == 2) {
                        std::string key = parts[0];
                        std::string value = parts[1];
                        
                        metaExtract.MetaPairs[key] = value;
                    }
                }
                else {
                    metaExtract.SimpleAttributes.push_back(arg);
                }
            }
        }

        return metaExtract;
    }

    std::vector<std::pair<std::string, std::string>> ParseMetaKeyValues(const std::string& s) {
        std::vector<std::pair<std::string, std::string>> out;

        auto chunks = ParseArgumentList(s);

        for (auto& chunk : chunks) {
            size_t eq = chunk.find('=');
            if (eq == std::string::npos) {
                continue;
            }

            std::string key = chunk.substr(0, eq);
            std::string value = chunk.substr(eq + 1);

            Utils::Trim(key);
            Utils::Trim(value);

            out.emplace_back(key, value);
        }

        return out;
    }


    void ParseAllProperties(ClassInfo& out, std::string& content) {
        const std::string macro = "VPROPERTY(";
        size_t searchPos = 0;

        while (true) {
            size_t macroPos = content.find(macro, searchPos);

            if (macroPos == std::string::npos) {
                break;
            }

            std::string_view subContent(content.c_str() + macroPos);

            std::string str = std::string(subContent);
            ParseProperty(out,str);
            searchPos = macroPos + macro.size();
        }
    }

    void ParseAllProperties(StructInfo& out, std::string& content) {
        const std::string macro = "VPROPERTY(";
        size_t searchPos = 0;

        while (true) {
            size_t macroPos = content.find(macro, searchPos);

            if (macroPos == std::string::npos) {
                break;
            }

            std::string_view subContent(content.c_str() + macroPos);

            std::string str = std::string(subContent);
            ParseProperty(out, str);
            searchPos = macroPos + macro.size();
        }
    }

    void ParseProperty(ClassInfo& Out, std::string& Content) {
        const char* MACRO = "VPROPERTY(";
        PropertyInfo pInfo;
        
        size_t macroPos = Content.find(MACRO);
        if (macroPos == std::string::npos) {
            return;
        }

        std::string line = Utils::GetLine(Content, macroPos);
        std::string inside = Utils::ExtractBetween(line, '(', ')');

        auto args = ParseArgumentList(inside);
        auto metaExtract = ExtractMeta(args);

        pInfo.Meta = metaExtract;
        
        size_t lineEnd = Content.find('\n', macroPos);
        std::string nextLine = Utils::GetLine(Content, lineEnd + 1);

        auto parts = Utils::SplitWords(nextLine, 0, [](char c) {
            return std::isspace(c) || c == ';';
        });

        if (parts.size() >= 2) {
            pInfo.Type = parts[0];
            pInfo.Name = parts[1];
        }

        Out.Properties.push_back(std::move(pInfo));
    }

    void ParseProperty(StructInfo& Out, std::string& Content) {
        constexpr const char* MACRO = "VPROPERTY(";
        PropertyInfo pInfo;
        
        size_t macroPos = Content.find(MACRO);
        if (macroPos == std::string::npos) {
            return;
        }

        std::string line = Utils::GetLine(Content, macroPos);
        std::string inside = Utils::ExtractBetween(line, '(', ')');

        auto args = ParseArgumentList(inside);
        auto metaExtract = ExtractMeta(args);

        pInfo.Meta = metaExtract;
        
        size_t lineEnd = Content.find('\n', macroPos);
        std::string nextLine = Utils::GetLine(Content, lineEnd + 1);

        auto parts = Utils::SplitWords(nextLine, 0, [](char c) {
            return std::isspace(c) || c == ';';
        });

        if (parts.size() >= 2) {
            pInfo.Type = parts[0];
            pInfo.Name = parts[1];
        }

        Out.Properties.push_back(std::move(pInfo));
    }


} 
