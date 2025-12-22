#include <CoreAPI/VSurface.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <fmt/color.h>

namespace VulcanEngine::Graphics {
	VSurface::VSurface(SDL_Surface* InSurface) :Surface(InSurface) {

	}

	VSurface::VSurface(VSurface&& InSurface) noexcept {
		Surface = InSurface.Surface;
		InSurface.Surface = nullptr;
	}

	VSurface::~VSurface() {
		if (Surface) {
			SDL_FreeSurface(Surface);
		}
	}


	VSurface& VSurface::operator=(VSurface&& InSurface) noexcept {
		std::swap(Surface, InSurface.Surface);
		return *this;
	}


	std::shared_ptr<VSurface> VSurface::LoadFromFile(const std::string& InPath) {
		SDL_Surface* surface = IMG_Load(InPath.c_str());

		if (!surface) {
			throw std::runtime_error("failed to load " + InPath + " \n");
		}

		//fmt::print(fg(fmt::color::green), "Loaded image: {}\n", InPath);
		return std::make_shared<VSurface>(surface);
	}

}
