#pragma once
#include <nlohmann/json.hpp>

#include <Renderables/VUIRenderable.h>

namespace VUI {

    class VUIFactory {
        using FactoryFunc = std::function<std::unique_ptr<VUIRenderable>()>;
    public:

        static std::unique_ptr<VUIRenderable> Create(const VUIElement& e);
        
        static void Register(const std::string& className, FactoryFunc func) {
            Registry[className] = func;
        }
        
    private:
        static void RegisterBuildInWidgets(const VUIElement& e);
        static std::unordered_map<std::string, FactoryFunc> Registry;
    };
}
