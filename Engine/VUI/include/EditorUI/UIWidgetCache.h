#pragma once
#include <CoreAPI/precomp.h>

#include <EditorUI/UIWidget.h>

class UIWidgetCache {

public:
    void Clear();

    void Put(UIWidget* InWidget);

    UIWidget* Take(const std::string& InKey);

    bool Has(const std::string& InKey) const;
    size_t Size() const;

private:
    // Maybe can cause so errors that we store direct pointers ? 
    std::unordered_map<std::string,UIWidget*> Cache;
    
};
