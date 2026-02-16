#include <EditorUI/UIActionDispatcher.h>

#include "LogSystem.h"
#include "Systems/EditorSystem.h"

void UIActionDispatcher::Register(const std::string& InActionName, Handler InHandler) {
    if (Has(InActionName)) {
        VLOG_WARN(EditorUI,"[EditorUI] {} already exist in dispatcher.",InActionName);
        return;
    }
    
    Handlers[InActionName] = InHandler;
}

void UIActionDispatcher::Unregister(const std::string& InActionName) {
    Handlers.erase(InActionName);
}

bool UIActionDispatcher::Has(const std::string& InActionName) const {
    return Handlers.find(InActionName) != Handlers.end();
}

void UIActionDispatcher::Dispatch(const std::string& InActionName, const UIActionContext& InContext) const {
    if (!Has(InActionName))
    {
        VLOG_WARN(EditorUI,"[EditorUI] Try to dispatch an non-existing action. ");
        return;
    }

    auto it = Handlers.find(InActionName);
    it->second(InContext);
}


