
#pragma once

#include <CoreAPI/precomp.h>

#include "UINode.h"
#include "VPath.h"


class UINodeResolver
{
public:
    UINodeResolver(std::string InBasePath);
    UINode Resolve(UINode& Node);

private:
    UINode LoadAndParse(const VPath& Path);

    bool HasRedirects(const UINode& Node,bool& bOutIsSelf);
    
    std::string BasePath;
};
