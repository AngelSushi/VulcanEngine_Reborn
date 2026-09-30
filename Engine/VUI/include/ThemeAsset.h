#pragma once
#include <string>
#include <variant>

#include <Types/VFont.h>
#include <Types/Assets/VAsset.h>

#include <ThemeAsset.vht.h>



VCLASS()
class VUI_API ThemeAsset : public VAsset {

    VCLASS_BODY()

public:
    // Maybe need move semantics 
    ThemeAsset() = default;
    ThemeAsset(const ThemeAsset&) = default; 
    ThemeAsset& operator=(const ThemeAsset&) = default;

    
    void ConstructJson(const std::string_view& InAssetName) override;

    static ThemeAsset* FromJson(const std::string& InJson);
    std::string ToJson() const override;

    void Init();
    void Render();
    void PostRender();

    
private:

    VFont TitleFont{};
    VFont BodyFont{};

    nlohmann::json DefaultFlags;
};

