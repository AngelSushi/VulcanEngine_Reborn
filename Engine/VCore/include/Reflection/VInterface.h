#pragma once
#include <memory>
#include <string>
#include <typeindex>
#include <vector>

namespace VulcanCore {

    struct ParameterSignature {
        std::type_index CanonicalType;
        bool IsConst{};
        bool IsRef{};
        bool IsPtr{};
    };
    
    struct FunctionSignature { // Prob need ReturnType Name for Editor/Tools etc ? 
        std::string Name;
        std::type_index ReturnType;
        std::vector<ParameterSignature> Params;
        std::vector<std::string> Attributes;
        
    };
    class VInterface {
        
    public:
        VInterface(const std::string_view& InName) : Name(InName) {}

        const std::string& GetName() const {
            return Name;
        }

        void AddFunctionSignature(const FunctionSignature& InFunctionSignature) {
           FunctionsSignature.push_back(InFunctionSignature);
        }
        
    
    private:
        std::string Name;
        std::vector<FunctionSignature> FunctionsSignature;
    };
    

    class InterfaceRegistry {
    public:
        static InterfaceRegistry& Instance() {
            static InterfaceRegistry registry;
            return registry;
        }

         void Register(VInterface* Interface) {
            Interfaces.push_back(std::make_shared<VInterface>(*Interface));
        }
        
    private:
        std::vector<std::shared_ptr<VInterface>> Interfaces;
    };
    
}
