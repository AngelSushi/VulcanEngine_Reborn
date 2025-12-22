#pragma once

#include <Export.h>

#include <memory>
#include <imgui.h>

#include <CoreAPI/VRenderer.h>
#include <CoreAPI/VWindow.h>

union SDL_Event;

namespace VulcanEngine {
	class VULCAN_ENGINE_API ImGuiRenderer {


	struct GuiRendererConfig {
		VWindow& Window;
		Graphics::VRenderer& Renderer;
	};
	
	public:

		static std::unique_ptr<ImGuiRenderer> Create(const GuiRendererConfig& config) {
			return std::make_unique<ImGuiRenderer>(config);
		}
		
		ImGuiRenderer(const GuiRendererConfig& Config);
		ImGuiRenderer(const ImGuiRenderer&) = delete;
		ImGuiRenderer(ImGuiRenderer&&) = delete;
		~ImGuiRenderer();

		//ImGuiRenderer& operator=(ImGuiRenderer&&);

		ImGuiContext* GetContext() {
			return _Context;
		}

		void Render();

		void NewFrame();

		bool ProcessEvent(SDL_Event& event);

		ImGuiRenderer& operator=(const ImGuiRenderer&) = delete;
		ImGuiRenderer& operator=(ImGuiRenderer&&) = delete;

	private:
		ImGuiContext* _Context; // On le remplace par un unique_ptr pour le test

		Graphics::VRenderer* _Renderer;
		VWindow* _Window;
	};
}


