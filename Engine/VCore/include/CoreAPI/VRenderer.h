#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <memory>
#include <optional>

#include "VWindow.h"


struct SDL_Renderer;
class VWindow;

class VTexture;

struct RendererConfig {
	VWindow& Window;
	int Renderer = -1;
	std::optional<std::uint32_t> Flags;
};

class VCORE_API VRenderer {
	friend class VTexture;

	public:

		static std::shared_ptr<VRenderer> Create(const RendererConfig& config) {
			return std::make_shared<VRenderer>(config);
		}
	
		VRenderer(const RendererConfig& Config);
		VRenderer(const VRenderer&) = delete;
		VRenderer(VRenderer&&) noexcept;

		VRenderer& operator=(VRenderer&&) noexcept;

		~VRenderer();

		SDL_Renderer* GetRenderer() { return _Renderer; }

		int Clear() const;

		int RenderCopy(const VTexture& Texture);
		int RenderCopy(const VTexture& Texture, const SDL_Rect& DestRect);
		int RenderCopyF(const VTexture& Texture, const SDL_FRect& DestRect) const;
		int RenderCopy(const VTexture& Texture, const SDL_Rect& SrcRect, const SDL_Rect& DestRect);

		int RenderFillRectF(SDL_FRect Rect) const;
	
		void Present();

		void SetDrawColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255) const;

		void Catch(int ErrorCode) const;

		VRenderer& operator=(const VRenderer&) = delete;

		SDL_Renderer* GetRenderer() const { return _Renderer; }
private:
		SDL_Renderer* _Renderer;
};


