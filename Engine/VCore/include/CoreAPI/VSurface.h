#pragma once

#include <memory>

#include <Export.h>
#include <string>
#include <vector>

#include "../../../../../../../../../../AppData/Local/.xmake/packages/l/libsdl2_ttf/2.24.0/73f35613d7824d09a200046418efc04a/include/SDL2/SDL_ttf.h"

struct SDL_Surface;

class VCORE_API VSurface {
	friend class VTexture;

	public:
		VSurface(const VSurface&) = delete;
		VSurface(VSurface&& Surface) noexcept;
		~VSurface();

		explicit VSurface(SDL_Surface* InSurface);

		SDL_Surface* GetSurface() { return Surface; }

		VSurface& operator=(const VSurface&) = delete;
		VSurface& operator=(VSurface&& InSurface) noexcept;

		static std::vector<std::string> GetAvailableExtensions() {
			static std::vector<std::string> extensions = { ".png", ".jpg", ".jpeg", ".tif", ".tiff", ".webp", ".bmp", ".gif"};
			return extensions;
		}

		static std::shared_ptr<VSurface> LoadFromFile(const std::string& InPath);

	private:
		SDL_Surface* GetSurface() const { return Surface; }

		SDL_Surface* Surface;
};



