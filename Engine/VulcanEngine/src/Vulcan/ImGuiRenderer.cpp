#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <imgui_internal.h>
#include <fmt/color.h>
#include <CoreAPI/VRenderer.h>
#include <ImGuiRenderer.h>

#include "LogSystem.h"
#include "CoreAPI/VCore.h"

#define SDL_HAS_CAPTURE_AND_GLOBAL_MOUSE 0  // D�sactiver cette section
namespace VulcanEngine {
	
	ImGuiRenderer::ImGuiRenderer(const GuiRendererConfig& Config) : _Window(&Config.Window),_Renderer(&Config.Renderer) {

		VLOG_INFO(CoreAPI,"Creation of imgui context for {} window ",Config.Window.GetTitle());

		IMGUI_CHECKVERSION();
		
		_Context = ImGui::CreateContext();
		ImGui::SetCurrentContext(_Context);

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	//	io.ConfigFlags |= ImGuiConfigFlags_
		//io.BackendPlatformUserData

		ImGui::StyleColorsDark();


		ImGui_ImplSDL2_InitForSDLRenderer(_Window->GetWindow(), _Renderer->GetRenderer());
		ImGui_ImplSDLRenderer2_Init(_Renderer->GetRenderer());
	}
	
	void ImGuiRenderer::Render() {
		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(),_Renderer->GetRenderer());
	}

	void ImGuiRenderer::NewFrame() {
		ImGui::SetCurrentContext(GetContext());

		ImGui_ImplSDLRenderer2_NewFrame();
 		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	bool ImGuiRenderer::ProcessEvent(SDL_Event& event) {
		if (event.window.windowID == SDL_GetWindowID(_Window->GetWindow())) {
			ImGui::SetCurrentContext(GetContext());
			ImGui_ImplSDL2_ProcessEvent(&event);

			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) {
				return false;
			}
		}

		return true;
	}

	ImGuiRenderer::~ImGuiRenderer() {
		print(fg(fmt::color::red), "[Core] Destruction du contexte ImGui \n");

		ImGui_ImplSDLRenderer2_Shutdown();
		ImGui_ImplSDL2_Shutdown();

		ImGui::DestroyContext(_Context);
	}

	
	
}
