#include <EditorUI/Core/UIWidgetCache.h>

void UIWidgetCache::Clear() {
    Cache.clear();
}

void UIWidgetCache::Put(std::unique_ptr<UIWidget> InWidget) {
    Cache[InWidget->GetID()] = std::move(InWidget);
}

std::unique_ptr<UIWidget> UIWidgetCache::Take(const std::string& InKey) {
    // TO DO LATER : Check For Ownership for this and the real behavior of Take();
    std::unique_ptr<UIWidget>& Widget = Cache[InKey];
    return std::move(Widget);
}

bool UIWidgetCache::Has(const std::string& InKey) const {
    return Cache.find(InKey) != Cache.end();
}

size_t UIWidgetCache::Size() const {
    return Cache.size();
}
