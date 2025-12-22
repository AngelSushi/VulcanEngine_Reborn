#include <CoreAPI/VTexture.h>
#include <SDL2/SDL.h>
#include <stdexcept>
#include <memory>
#include <fmt/core.h>
#include <fmt/color.h>

#include "CoreAPI/VRenderer.h"
#include "CoreAPI/VSurface.h"


namespace VulcanEngine::Graphics {
	
	VTexture::VTexture(SDL_Texture* Texture, const std::string& FilePath) :
		Texture(Texture), FilePath(FilePath) {

		if (!FilePath.empty()) {
			Name = FilePath.substr(FilePath.find_last_of("/") + 1, FilePath.length());

			if (Name == FilePath) {
				Name = FilePath.substr(FilePath.find_last_of("\\") + 1, FilePath.length());
			}	
		}
	}


	VTexture::VTexture(VTexture&& Texture) noexcept :
		Texture(Texture.Texture),FilePath(Texture.FilePath),Name(Texture.Name) {
		Texture.Texture = nullptr;

	}

	VTexture::~VTexture() {
		if (Texture) {
			SDL_DestroyTexture(Texture);
		}
	}

	SDL_Rect VTexture::GetRect() const {
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		SDL_QueryTexture(Texture, nullptr, nullptr, &rect.w, &rect.h);

		return rect;
	}

	VTexture& VTexture::operator=(VTexture&& Tex) noexcept {
		std::swap(Texture, Tex.Texture);
		std::swap(FilePath, Tex.FilePath);
		std::swap(Name, Tex.Name);
		return *this;
	}

	std::shared_ptr<VTexture> VTexture::CreateFromSurface(const VRenderer& Renderer, const VSurface& Surface, const std::string& FilePath) 	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer.GetRenderer(), Surface.GetSurface());
		
		if (!texture) {
			throw std::runtime_error("failed to create texture " + std::string(SDL_GetError()));
		}

		return std::make_shared<VTexture>(VTexture(texture,FilePath));
	}

	void VTexture::SetPixel(int x, int y, Uint32 Color) {
		int Width = 0;
		int Height = 0;
		void* Pixels;
		int Pitch = 0;

		if (SDL_LockTexture(Texture, nullptr, &Pixels, &Pitch) != 0) {
			return;
		}

		Uint32* PixelData = static_cast<Uint32*>(Pixels);

		int Index = y * (Pitch / sizeof(Uint32)) + x;
		PixelData[Index] = Color;

		SDL_UnlockTexture(Texture);
	}

}
