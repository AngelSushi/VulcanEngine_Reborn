#pragma once

#include <Reflection/VScruct.h>
#include <Reflection/Function/VFunction.h>

namespace VulcanCore {
    class VClass : public VScruct { // For all class that are "lifeable" objects
    
    public:
        VClass(const std::string& ClassName,const std::string& full_name, size_t ClassSize) : VScruct(std::move(ClassName),std::move(full_name), ClassSize) {}
        
        void AddFunction(std::unique_ptr<VFunctionBase> Fn) {
            Functions.push_back(std::move(Fn));
        }

        const std::vector<std::unique_ptr<VFunctionBase>>& GetFunctions() const { return Functions; }
        
        template<typename T>
        bool IsA() const {
            const VClass* current = this;

            while (current) {
                if (current == &T::StaticClass()) {
                    return true;
                }

                current = current->Parent;
            }

            return false;
        }

        VFunctionBase* find_function(const std::string_view& function_name) {
            auto it = std::find_if(Functions.begin(), Functions.end(),[&function_name](const std::unique_ptr<VFunctionBase>& func) {
                return func->GetName() == function_name;
            });

            return it != Functions.end() ? it->get() : nullptr;
        }
        
        VClass* Parent = nullptr; // Dangerous
    private:
        std::vector<std::unique_ptr<VFunctionBase>> Functions;
    };
}
