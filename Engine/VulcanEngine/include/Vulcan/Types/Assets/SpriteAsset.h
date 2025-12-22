#pragma once

#include <Export.h>
#include <SDL2/SDL.h>
#include <Renderable.h>
#include <memory>
#include <Types/Assets/VAsset.h>

#include <Vector2.h>
#include "CoreAPI/VTexture.h"

#include "BinarySerializer.h"
#include "AssetsManager.h"

#include <SpriteAsset.vht.h>



namespace VulcanEngine {
	class Graphics::VRenderer;
	class Graphics::VTexture;
	class Transform;
	class VMath::MatrixFloat;

	VCLASS()
	class VULCAN_ENGINE_API SpriteAsset : public VAsset {

		friend class SpriteAssetHandler; // Add It to VCLASS_BODY macro?
		
		VCLASS_BODY()
		
		public:
			static SpriteAsset* Create(const std::string& InFilePath) {
				return VulcanCore::NewObject<SpriteAsset>(InFilePath);
			}
		
			SpriteAsset(Graphics::VTexture* InTexture,std::string FilePath);
			SpriteAsset(Graphics::VTexture* InTexture, const SDL_Rect& Rect,std::string FilePath);

			SpriteAsset(const SpriteAsset&);
			SpriteAsset(SpriteAsset&&) noexcept;

			SpriteAsset& operator=(const SpriteAsset&);
			SpriteAsset& operator=(SpriteAsset&&) noexcept;

			
			const SDL_Rect& GetRect() { return Rect; }
			const VMath::Vector2f& GetOrigin() const { return Origin; }
			const VMath::Vector2i& GetSize() const { return Size; }
			const Graphics::VTexture* GetTexture() const { return Texture; }

			void ConstructBinary(const std::vector<uint8_t>& Buffer) override;

		private:
			SpriteAsset(const std::string& InFilePath) : VAsset(InFilePath) {}
		
		// Pivot / Anchor
			Graphics::VTexture* Texture{};
			SDL_Rect Rect{};
			VMath::Vector2f Origin{};
			VMath::Vector2i Size{};
			
	};
	
	inline std::ostream& operator<<(std::ostream& os, const SpriteAsset& asset) { // Does it work with inheritance?
		std::vector<uint8_t> buffer;

		VulcanCore::BinarySerializer::Serialize<std::string>(buffer,asset.GetGUID());
		VulcanCore::BinarySerializer::Serialize<std::string>(buffer,asset.GetFilePath());
		VulcanCore::BinarySerializer::Serialize<std::string>(buffer,asset.GetName());

		if (asset.GetTexture()) {
			VulcanCore::BinarySerializer::Serialize<std::string>(buffer,asset.GetTexture()->GetName());			
		}
		else {
			std::string texName = fs::path(asset.GetFilePath()).filename().string();
			VulcanCore::BinarySerializer::Serialize<std::string>(buffer,texName);
		}

		VulcanCore::BinarySerializer::Serialize<float>(buffer,asset.GetOrigin().x);
		VulcanCore::BinarySerializer::Serialize<float>(buffer,asset.GetOrigin().y);
		VulcanCore::BinarySerializer::Serialize<int8_t>(buffer,static_cast<int8_t>(asset.GetSize().x));
		VulcanCore::BinarySerializer::Serialize<int8_t>(buffer,static_cast<int8_t>(asset.GetSize().y));
		
		os.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
		return os;
	}
}
