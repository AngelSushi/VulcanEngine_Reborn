#pragma once
#include <CoreAPI/precomp.h>

struct UINode;

class UIBuilder {

public:
    void Construct(const UINode& InNode);

    void HotReload();
private:
    
};