#pragma once
#include <CoreAPI/precomp.h>

#include <Systems/VSystem.h>
#include <SDL_ttf.h>

#include "CoreAPI/VSurface.h"

class VUI_API FontSystem : public VSystem {

public:
    
    static FontSystem& Instance();
    
    // Convert to VFont after
    void InitSystem() override;
    void Shutdown() override;

    // Global Reflection about Fonts : 
    // Are we oblige to load a font with a specific size, can we not just load a font and adjust the size or something like that after ?

    TTF_Font* LoadFont(std::filesystem::path FontPath, int FontSize);
    TTF_Font* LoadFontRW(std::filesystem::path FontPath, int FontSize);

    // Maybe replace all GetFont functions in VFont or in something better than the system ? 
    TTF_Font* GetFont(std::string_view FontName, int FontSize);
    TTF_Font* GetFont(int FontId);
    TTF_Font* GetFont(int FontId, int FontSize);
    int GetFontId(std::string_view FontName, int FontSize);

    bool IsFontLoaded(std::string_view FontName, int FontSize);

    std::shared_ptr<VSurface> CreateUTF8BlendedSurface(TTF_Font* Font,const std::string& Text, SDL_Color Color);


private:
    struct FontEntry {
        std::string FontName;
        int FontId;
        int FontSize;
        // Problem with movement when we increase the capacity of vector ? 
        TTF_Font* Font;
    };

    std::vector<FontEntry> Fonts;

    // Is unordered_map the best way to store it ?
    // std::vector represent the data in binary of a font
    std::unordered_map<std::string,std::vector<Uint8>> FontsData;
};
