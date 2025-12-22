#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>

struct SDL_Texture;

namespace VulcanEngine::Graphics {
	class VRenderer;
	class VSurface;

	enum TextureType {
		Texture20 = 0,
		Sprite = 1,
		SpriteSheet = 2,
		UI_Image = 3/*,
		NormalMap = 4,
		CubeMap = 5*/
	};

	class VTexture {
		friend class VRenderer;

		public:
			explicit VTexture(SDL_Texture* Texture, const std::string& FilePath);
			VTexture(const VTexture&) = delete;
			VTexture(VTexture&& Texture) noexcept;
			~VTexture();

			SDL_Texture* GetTexture() { return Texture; }
			SDL_Rect GetRect() const;

			VTexture& operator=(const VTexture&) = delete;
			VTexture& operator=(VTexture&& Texture) noexcept;

			static std::shared_ptr<VTexture> CreateFromSurface(const VRenderer& Renderer, const VSurface& Surface, const std::string& FilePath);

			void SetPixel(int x, int y, Uint32 Color);

			std::string& GetFilePath() { return FilePath; }
			const std::string& GetName() const { return Name; }
	private:

			SDL_Texture* GetTexture() const { return Texture; }

			SDL_Texture* Texture;
			std::string FilePath;
			std::string Name;
	};
}
