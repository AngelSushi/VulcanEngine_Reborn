#pragma once

#include <memory>

#include <string>
#include <vector>

struct SDL_Surface;

namespace VulcanEngine::Graphics {
	class VSurface{
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


}
