#pragma once
#include <CoreAPI/precomp.h>

#include <Systems/VSystem.h>
#include <SDL_ttf.h>

class VUI_API FontSystem : public VulcanEngine::VSystem {

public:
    
    static FontSystem& Instance();
    
    // Convert to VFont after
    void InitSystem() override;
    void Shutdown() override;

    // Global Reflection about Fonts : 
    // Are we oblige to load a font with a specific size, can we not just load a font and adjust the size or something like that after ?

    TTF_Font* LoadFont(std::filesystem::path FontPath, int FontSize);

    // Maybe replace all GetFont functions in VFont or in something better than the system ? 
    TTF_Font* GetFont(std::string_view FontName, int FontSize);
    TTF_Font* GetFont(int FontId);
    TTF_Font* GetFont(int FontId, int FontSize);
    int GetFontId(std::string_view FontName, int FontSize);

    bool IsFontLoaded(std::string_view FontName, int FontSize);

private:
    struct FontEntry {
        std::string FontName;
        int FontId;
        int FontSize;
        // Problem with movement when we increase the capacity of vector ? 
        TTF_Font* Font;
    };

    std::vector<FontEntry> Fonts;
};