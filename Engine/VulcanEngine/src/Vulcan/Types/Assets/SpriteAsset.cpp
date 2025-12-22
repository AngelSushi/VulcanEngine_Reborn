#include <Types/Assets/SpriteAsset.h>
#include <CoreAPI/VRenderer.h>
#include <CoreAPI/VTexture.h>
#include <Components/Transform.h>

#include <fmt/core.h>

#include <imgui.h>

#include <VDrawHelper.h>
#include <CoreAPI/VCore.h>
#include <ResourceManager.h>


namespace VulcanEngine {
	SpriteAsset::SpriteAsset(Graphics::VTexture* InTexture,std::string InFilePath) :  VAsset(InFilePath),Texture(InTexture),Rect(Texture->GetRect()) {}

	SpriteAsset::SpriteAsset(Graphics::VTexture* InTexture, const SDL_Rect& InRect, std::string InFilePath) : VAsset(InFilePath),
	Texture(std::move(InTexture)),Rect(InRect),Origin(0.5f, 0.5f),Size(Rect.w, Rect.h) {
		
	}

	SpriteAsset::SpriteAsset(const SpriteAsset& CopySprite) : VAsset(std::move(CopySprite.FilePath)),Texture(std::move(CopySprite.Texture)), 
		Rect(CopySprite.Rect),Origin(CopySprite.Origin),Size(CopySprite.Size) {
		
		fmt::println("Constructeur par copie de Sprite");
	}


	SpriteAsset::SpriteAsset(SpriteAsset&& MoveSprite) noexcept :VAsset(std::move(MoveSprite.FilePath)),Texture(std::move(MoveSprite.Texture)),
		Rect(MoveSprite.Rect),Origin(MoveSprite.Origin),Size(MoveSprite.Size) {
		fmt::println("Constructeur par mouvement de Sprite");
	}


	SpriteAsset& SpriteAsset::operator=(const SpriteAsset& CopySprite) {
		FilePath = CopySprite.FilePath;
		Texture = CopySprite.Texture;
		Rect = CopySprite.Rect;
		Origin = CopySprite.Origin;
		Size = CopySprite.Size;

		fmt::println("Affectation par copie de Sprite");

		return *this;
	}

	SpriteAsset& SpriteAsset::operator=(SpriteAsset&& MoveSprite) noexcept {
		FilePath = std::move(MoveSprite.FilePath);
		Texture = std::move(MoveSprite.Texture);
		Rect = MoveSprite.Rect;
		Origin = MoveSprite.Origin;
		Size = MoveSprite.Size;

		fmt::println("Affectation par mouvement de Sprite");

		return *this;
	}

	void SpriteAsset::ConstructBinary(const std::vector<uint8_t>& Buffer) {
		size_t offset = 0;

		GUID = VulcanCore::BinarySerializer::Unserialize<std::string>(Buffer, offset);
		FilePath = VulcanCore::BinarySerializer::Unserialize<std::string>(Buffer, offset);
		AssetName = VulcanCore::BinarySerializer::Unserialize<std::string>(Buffer, offset);	

		std::string texName = VulcanCore::BinarySerializer::Unserialize<std::string>(Buffer, offset);
		Origin.x = VulcanCore::BinarySerializer::Unserialize<float>(Buffer, offset);
		Origin.y = VulcanCore::BinarySerializer::Unserialize<float>(Buffer, offset);
		Size.x   = VulcanCore::BinarySerializer::Unserialize<int8_t>(Buffer, offset);
		Size.y   = VulcanCore::BinarySerializer::Unserialize<int8_t>(Buffer, offset);

		Texture = Resources::ResourceManager::Instance().GetTexture(FilePath).get();
	}
	
}
