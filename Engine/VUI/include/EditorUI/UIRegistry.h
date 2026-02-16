#pragma once
#include <CoreAPI/precomp.h>


class UIRegistry {

public:
    void Initialize();

    void BuildRegistry();
    
private:
    std::unordered_map<std::string,VulcanCore::VClass*> RegisteredClasses;

    VulcanCore::VClass* TreeClass;
};