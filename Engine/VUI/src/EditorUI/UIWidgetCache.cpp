#include <EditorUI/UIWidgetCache.h>

void UIWidgetCache::Put(std::unique_ptr<UIWidget> InWidget) {
}

std::unique_ptr<UIWidget> UIWidgetCache::Take(const std::string& InKey) {
}

bool UIWidgetCache::Has(const std::string& InKey) const {
    return Cache.find(InKey) != Cache.end();
}

size_t UIWidgetCache::Size() const {
    return Cache.size();
}
