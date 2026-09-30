#include <CoreAPI/VRenderer.h>
#include <CoreAPI/VTexture.h>
#include <SDL2/SDL.h>
#include <stdexcept>

#include <fmt/core.h>
#include <fmt/color.h>

#include "LogSystem.h"
#include "CoreAPI/VCore.h"

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

int VRenderer::Clear() const {
	return SDL_RenderClear(_Renderer);
}

int VRenderer::RenderCopy(const VTexture& Texture) {
	return	SDL_RenderCopy(_Renderer, Texture.GetTexture(), nullptr, nullptr);
}

int VRenderer::RenderCopy(const VTexture& Texture, const SDL_Rect& DestRect) {
	return SDL_RenderCopy(_Renderer, Texture.GetTexture(), nullptr, &DestRect);
}

int VRenderer::RenderCopyF(const VTexture& Texture, const SDL_FRect& DestRect) const{
	return SDL_RenderCopyF(_Renderer, Texture.GetTexture(), nullptr, &DestRect);
}

int VRenderer::RenderCopy(const VTexture& Texture, const SDL_Rect& SrcRect, const SDL_Rect& DestRect) {
	return SDL_RenderCopy(_Renderer, Texture.GetTexture(), &SrcRect, &DestRect);
}

int VRenderer::RenderFillRectF(SDL_FRect Rect) const {
	return SDL_RenderFillRectF(_Renderer,&Rect);
}

void VRenderer::Present() {
	SDL_RenderPresent(_Renderer);
}

void VRenderer::SetDrawColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) const {
	SDL_SetRenderDrawColor(_Renderer, r, g, b, a);
}

void VRenderer::Catch(int ErrorCode) const {
	if (ErrorCode < 0) {
		fmt::print(stderr, "Error {}\n", SDL_GetError()); 
	}
}

