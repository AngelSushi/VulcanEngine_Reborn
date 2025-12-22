#include <CoreAPI/VWindow.h>
#include <SDL2/SDL.h>
#include <stdexcept>
#include <CoreAPI/VCore.h>
#include <fmt/core.h>

#include "Game.h"
#include "ImGuiRenderer.h"


namespace VulcanEngine {
	
	VWindow::VWindow(const WindowConfig& Config) {
		VLOG_INFO(CoreAPI,"Creation of window {}",Config.Title);

		int X = Config.Position ? Config.Position->x : SDL_WINDOWPOS_CENTERED;
		int Y = Config.Position ? Config.Position->y : SDL_WINDOWPOS_CENTERED;
		
		Window = SDL_CreateWindow(Config.Title.data(),X,Y,Config.Size.x,Config.Size.y,Config.Flags);

		if (!Window)
			throw std::runtime_error("failed to create window");
	}

	VWindow::~VWindow() {
		VLOG_INFO(CoreAPI,"Destroying window {}",GetTitle());
		SDL_DestroyWindow(Window);
	}

	void VWindow::Start() {
		//_Renderer = VCore::Instance().GetAttachedRenderer(this);
	//	_ImRenderer = VCore::Instance().GetAttachedImRenderer(this);
	}

	void VWindow::Update(float DeltaTime) {
		if (_FirstFrame) {
			Start();
			_FirstFrame = false;
			return;
		}
	}

	void VWindow::PollEvents(ImGuiRenderer* GUIRenderer) {
		SDL_Event event;
		while (VulcanCore::VCore::PollEvent(event)) {
			GUIRenderer->ProcessEvent(event);
			
			switch (event.type) {
				case SDL_QUIT:
					Game::GetQuitEngineEvent().Trigger();
					CloseWindow();
					break;
				}
		}
	}

	std::string VWindow::GetTitle() const {
		return SDL_GetWindowTitle(Window);
	}

}
