#pragma once


#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>
#include <CoreAPI/VRenderer.h>

#include "LogSystem.h"

DECLARE_LOG_CATEGORY(CoreAPI);

namespace VulcanCore {

	class VWindow;
	class VCursor;

	class VCore {
		public:
			VCore(std::uint32_t Flags = 0);
			VCore(const VCore&) = delete;
			~VCore();
		
			VCore& operator=(const VCore&) = delete;

			static VCore& GetInstance();

			const VMath::Vector2i GetScreenSize() const;
			static const std::string GetVersion();
			static bool PollEvent(SDL_Event& Event);

			VulcanEngine::VWindow& CreateWindow(const VulcanEngine::WindowConfig& config);
			VulcanEngine::Graphics::VRenderer& CreateRenderer(const VulcanEngine::Graphics::RendererConfig& config);

			VulcanEngine::VWindow& GetWindow(const std::string_view& InWindowName);
			VulcanEngine::Graphics::VRenderer& GetRenderer(const std::string_view& InWindowName);

			const std::unordered_map<std::string, std::shared_ptr<VulcanEngine::Graphics::VRenderer>>& GetAllRenderers() const {
				return Renderers;
			}

	private:
		int ScreenWidth;
		int ScreenHeight;

		std::unordered_map<std::string,std::shared_ptr<VulcanEngine::VWindow>> Windows;
		std::unordered_map<std::string,std::shared_ptr<VulcanEngine::Graphics::VRenderer>> Renderers;
		
		inline static VCore* Instance;
	};
}

