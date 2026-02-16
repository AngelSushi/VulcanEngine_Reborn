#include <EditorUI/UIWidgetCache.h>

void UIWidgetCache::Put(UIWidget* InWidget) {
}

std::unique_ptr<UIWidget> UIWidgetCache::Take(const std::string& InKey) {
    auto it = Cache.find(InKey);
    
    if (it == Cache.end()) {
        return nullptr;
    }

    auto out = std::move(it->second);
    Cache.erase(InKey);
    return out;
}

bool UIWidgetCache::Has(const std::string& InKey) const {
    return Cache.find(InKey) != Cache.end();
}

size_t UIWidgetCache::Size() const {
    return Cache.size();
}
