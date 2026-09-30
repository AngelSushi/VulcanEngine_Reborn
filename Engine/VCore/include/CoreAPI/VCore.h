#pragma once


#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>
#include <CoreAPI/VRenderer.h>

#include "LogSystem.h"


DECLARE_LOG_CATEGORY(CoreAPI);

class VWindow;
class VCursor;

class VCORE_API VCore {
	public:
		VCore(std::uint32_t Flags = 0);
		VCore(const VCore&) = delete;
		~VCore();
	
		VCore& operator=(const VCore&) = delete;

		static VCore& GetInstance();

		const VMath::Vector2i GetScreenSize() const;
		static const std::string GetVersion();
		static bool PollEvent(SDL_Event& Event);

		VWindow& CreateWindow(const WindowConfig& config);
		VRenderer& CreateRenderer(const RendererConfig& config);

	// Dangerous to access without const ? 
		VWindow& GetWindow(const std::string_view& InWindowName);
		VWindow& GetWindowByIndex(int InIndex);
		VRenderer& GetRenderer(const std::string_view& InWindowName);

		const std::unordered_map<std::string, std::shared_ptr<VRenderer>>& GetAllRenderers() const {
			return Renderers;
		}

private:
	int ScreenWidth;
	int ScreenHeight;

	std::unordered_map<std::string,std::shared_ptr<VWindow>> Windows;
	std::unordered_map<std::string,std::shared_ptr<VRenderer>> Renderers;
	
	inline static VCore* Instance;
};


