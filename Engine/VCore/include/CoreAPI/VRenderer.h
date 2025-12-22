#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <memory>
#include <optional>

#include "VWindow.h"


struct SDL_Renderer;
class VWindow;

namespace VulcanEngine::Graphics {
	class VTexture;
	
	struct RendererConfig {
		VWindow& Window;
		int Renderer = -1;
		std::optional<std::uint32_t> Flags;
	};
	
	class VRenderer {
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

			void Clear() const;

			void RenderCopy(const VTexture& Texture);
			void RenderCopy(const VTexture& Texture, const SDL_Rect& DestRect);
			void RenderCopy(const VTexture& Texture, const SDL_Rect& SrcRect, const SDL_Rect& DestRect);

			void Present();

			void SetDrawColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255);

			VRenderer& operator=(const VRenderer&) = delete;

		private:
			SDL_Renderer* GetRenderer() const { return _Renderer; }

			SDL_Renderer* _Renderer;
	};
}

