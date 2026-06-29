#include <Systems/FontSystem.h>

#include "IO/FileManager.h"
#include "Types/VFont.h"

FontSystem& FontSystem::Instance() {
    static FontSystem Instance;
    return Instance;
}

void FontSystem::InitSystem() {
    TTF_Init();

    Fonts.reserve(10); // Reserve space for 10 fonts to avoid frequent reallocations. Don't use it, it just for test to avoid pointer dangling
    
    for (const std::string& AvailableExtension : VulcanEngine::VFont::GetAvailableExtensions()) {
        for (const std::string& FontPath : VulcanCore::FileManager::Get().LoadExtension("assets/",AvailableExtension)) {
            LoadFont(FontPath,16);
        } 
    }
}

TTF_Font* FontSystem::GetFont(std::string_view FontName, int FontSize) {
    auto it = std::find_if(Fonts.begin(), Fonts.end(), [&](const FontEntry& Entry) {
        return Entry.FontName == FontName && Entry.FontSize == FontSize;
    });

    return (it != Fonts.end()) ? it->Font : nullptr;
}

TTF_Font* FontSystem::GetFont(int FontId) {
    auto it = std::find_if(Fonts.begin(), Fonts.end(), [&](const FontEntry& Entry) {
        return Entry.FontId == FontId;
    });

    return (it != Fonts.end()) ? it->Font : nullptr;
}

TTF_Font* FontSystem::GetFont(int FontId, int FontSize) {
    auto it = std::find_if(Fonts.begin(), Fonts.end(), [&](const FontEntry& Entry) {
        return Entry.FontId == FontId && Entry.FontSize == FontSize;
    });

    return (it != Fonts.end()) ? it->Font : nullptr;
}

int FontSystem::GetFontId(std::string_view FontName, int FontSize) {
    auto it = std::find_if(Fonts.begin(), Fonts.end(), [&](const FontEntry& Entry) {
        return Entry.FontName == FontName && Entry.FontSize == FontSize;
    });

    return (it != Fonts.end()) ? it->FontId : -1;
}

TTF_Font* FontSystem::LoadFont(std::filesystem::path FontPath, int FontSize) {
    TTF_Font* Font = TTF_OpenFont(FontPath.string().data(), FontSize);
    
    if (!Font) {
        // VLOG_ERROR(FontSystem, "Failed to load font: {} with size {}. Error: {}", FontPath, FontSize, TTF_GetError());
        return nullptr;
    }

    Fonts.push_back({ FontPath.filename().string(),static_cast<int>(Fonts.size()), FontSize, Font });
    return Font;
}

bool FontSystem::IsFontLoaded(std::string_view FontName, int FontSize) {
    return GetFont(FontName, FontSize) != nullptr;
}

void FontSystem::Shutdown() {
    for (const auto& Entry : Fonts) {
        TTF_CloseFont(Entry.Font);
    }
    
    TTF_Quit();
}
