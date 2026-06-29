
#pragma once

#include <CoreAPI/precomp.h>

#include "UINode.h"


class UINodeResolver
{
public:
    UINodeResolver(std::string InBasePath);
    UINode Resolve(UINode& Node);

private:
    UINode LoadAndParse(const std::string& Path);

    bool HasRedirects(const UINode& Node);
    
    std::string BasePath;
};
