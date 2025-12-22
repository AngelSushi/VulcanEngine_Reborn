// Binding.h
#pragma once
#include <functional>
#include <set>
#include <string>
#include <vector>

namespace VUI {

class ConsoleCommandSystem {
    using CommandCallback = std::function<void(const std::vector<std::string>&)>;

public:

    static ConsoleCommandSystem& Instance() {
        static ConsoleCommandSystem instance;
        return instance;
    }
    
    void RegisterCommand(const std::string& InName,const std::string& InDescription, CommandCallback InCallback) {
        Commands.push_back({"console." + InName, InDescription, InCallback});
    }

    bool Execute(const std::string& InCommand);

    std::vector<std::string> SplitCommand(const std::string& InCommand, char InDelimiter) const;
private:
    struct CommandInfo {
        std::string Name{};
        std::string Description{};
        CommandCallback Callback;
    };

    std::vector<CommandInfo> Commands;
    std::set<std::string> History;
};

} // namespace VUI
