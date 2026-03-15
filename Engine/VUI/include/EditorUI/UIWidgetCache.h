#pragma once
#include <CoreAPI/precomp.h>
#include <EditorUI/UIWidget.h>

class UIWidgetCache {

public:
    void Clear();

    void Put(std::unique_ptr<UIWidget> InWidget);

    // Maybe need to return a ref ? 
    std::unique_ptr<UIWidget> Take(const std::string& InKey);

    bool Has(const std::string& InKey) const;
    size_t Size() const;

private:
    std::unordered_map<std::string,std::unique_ptr<UIWidget>> Cache;
    
};
