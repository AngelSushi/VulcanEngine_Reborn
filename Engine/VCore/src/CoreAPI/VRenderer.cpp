#include <CoreAPI/VRenderer.h>
#include <CoreAPI/VTexture.h>
#include <SDL2/SDL.h>
#include <stdexcept>

#include <fmt/core.h>
#include <fmt/color.h>

#include "LogSystem.h"
#include "CoreAPI/VCore.h"


namespace VulcanEngine::Graphics {

	VRenderer::VRenderer(const RendererConfig& Config) {
		VLOG_INFO(CoreAPI,"Creation of Renderer for {}\n", Config.Window.GetTitle());

		_Renderer = SDL_CreateRenderer(Config.Window.GetWindow(), Config.Renderer,Config.Flags.has_value() ? Config.Flags.value() : 0);
		
		if (!_Renderer)
			throw std::runtime_error("failed to create renderer");
	}

	VRenderer::VRenderer(VRenderer&& MoveRenderer) noexcept {
		_Renderer = std::move(MoveRenderer._Renderer);
	}

	VRenderer& VRenderer::operator=(VRenderer&& MoveRenderer) noexcept {
		_Renderer = std::move(MoveRenderer._Renderer);
		return *this;
	}

	VRenderer::~VRenderer()	{
		VLOG_INFO(CoreAPI,"Destroying renderer\n");
		SDL_DestroyRenderer(_Renderer);
	}

	void VRenderer::Clear() const {
		SDL_RenderClear(_Renderer);
	}

	void VRenderer::RenderCopy(const VTexture& Texture) {
		SDL_RenderCopy(_Renderer, Texture.GetTexture(), nullptr, nullptr);
	}

	void VRenderer::RenderCopy(const VTexture& Texture, const SDL_Rect& DestRect) {
		SDL_RenderCopy(_Renderer, Texture.GetTexture(), nullptr, &DestRect);
	}

	void VRenderer::RenderCopy(const VTexture& Texture, const SDL_Rect& SrcRect, const SDL_Rect& DestRect) {
		SDL_RenderCopy(_Renderer, Texture.GetTexture(), &SrcRect, &DestRect);
	}

	void VRenderer::Present() {
		SDL_RenderPresent(_Renderer);
	}

	void VRenderer::SetDrawColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
		SDL_SetRenderDrawColor(_Renderer, r, g, b, a);
	}
}
