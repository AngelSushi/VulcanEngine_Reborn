#include <Systems/FontSystem.h>

#include "LogSystem.h"
#include "IO/FileManager.h"
#include "Systems/EditorSystem.h"
#include "Types/VFont.h"

FontSystem& FontSystem::Instance() {
    static FontSystem Instance;
    return Instance;
}

void FontSystem::InitSystem() {
    TTF_Init();

    Fonts.reserve(10); // Reserve space for 10 fonts to avoid frequent reallocations. Don't use it, it just for test to avoid pointer dangling

    // Modifier cette double boucle on fait surement trop d'itération  pour rien
    for (const std::string& AvailableExtension : VFont::GetAvailableExtensions()) {
        for (const std::string& FontPath : VulcanCore::FileManager::Get().LoadExtension("assets/",AvailableExtension)) {
            for (int FontSize : { 12, 14, 16, 18, 20, 24, 28, 32 }) {
                LoadFontRW(FontPath, FontSize);
            }
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

TTF_Font* FontSystem::LoadFontRW(std::filesystem::path FontPath, int FontSize) {
    const std::string& Key = FontPath.filename().string();

    auto it = FontsData.find(Key);
    if (it == FontsData.end()) {
        auto Bytes = VulcanCore::FileManager::Get().Read(FontPath.string());
        it = FontsData.emplace(Key,std::move(Bytes)).first;
    }

    const std::vector<Uint8>& Bytes = it->second;
    
    SDL_RWops* RW = SDL_RWFromConstMem(Bytes.data(),static_cast<int>(Bytes.size()));
    TTF_Font* Font = TTF_OpenFontRW(RW,1,FontSize);

    Fonts.push_back({ Key, static_cast<int>(Fonts.size()), FontSize, Font });
    return Font;
}

bool FontSystem::IsFontLoaded(std::string_view FontName, int FontSize) {
    return GetFont(FontName, FontSize) != nullptr;
}

std::shared_ptr<VSurface> FontSystem::CreateUTF8BlendedSurface(TTF_Font* Font, const std::string& Text, SDL_Color Color) {
    SDL_Surface* Surface = TTF_RenderUTF8_Blended(Font, Text.c_str(), Color);

    if (!Surface) {
        fmt::print("Failed to create blended surface for text: {}. Error: {}\n", Text, TTF_GetError());
        return nullptr;
    }

    return std::make_shared<VSurface>(Surface);
}

void FontSystem::Shutdown() {
    for (const auto& Entry : Fonts) {
        TTF_CloseFont(Entry.Font);
    }
    
    TTF_Quit();
}
