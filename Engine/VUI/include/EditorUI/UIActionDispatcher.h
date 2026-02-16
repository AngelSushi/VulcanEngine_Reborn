#pragma once
#include <CoreAPI/precomp.h>

#include "UIValue.h"

struct UIActionContext {
    std::string WidgetId;
    std::unordered_map<std::string,UIValue> Values;
};

class UIActionDispatcher {

public:
    using Handler = std::function<void(const UIActionContext&)>;
    
    void Register(const std::string& InActionName, Handler InHandler);
    void Unregister(const std::string& InActionName);

    bool Has(const std::string& InActionName) const;
    void Dispatch(const std::string& InActionName, const UIActionContext& InContext) const;

private:
    std::unordered_map<std::string,Handler> Handlers;
};