 #include <ConsoleCommandSystem.h>
#include <ranges>
#include <sstream>
#include <fmt/core.h>

#include <LogSystem.h>
#include <Systems/EditorSystem.h>

 namespace VUI {


     bool ConsoleCommandSystem::Execute(const std::string& InCommand) {
         auto tokens = SplitCommand(InCommand, ' ');

         if (tokens.empty())
             return false;

         auto cmd = tokens[0];
         tokens.erase(tokens.begin());
         
         auto it = std::find_if(Commands.begin(), Commands.end(), [&](const CommandInfo& command) {
             return command.Name == cmd;
         });

         if (it != Commands.end()) {
            it->Callback(tokens);
             History.insert(cmd);
             return true;
         }
         
         VLOG_ERROR(EditorUI,"Command '{}' not found.", cmd);
         return false;
     }

     std::vector<std::string> ConsoleCommandSystem::SplitCommand(const std::string& InCommand,char InDelimiter) const {
         std::vector<std::string> tokens;
         std::stringstream ss(InCommand);
         std::string item;

         while (std::getline(ss,item,InDelimiter)) {
             if (!item.empty()) {
                 tokens.push_back(item);
             }
         }


         return tokens;
     }
 } // namespace VUI
