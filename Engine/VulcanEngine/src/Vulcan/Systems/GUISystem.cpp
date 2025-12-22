#include <Systems/GUISystem.h>
#include <fmt/core.h>

#include <ImGuiRenderer.h>

namespace VulcanEngine {

	GuiSystem::GuiSystem(const GuiSystemConfig& Config) {

		GuiRenderer = ImGuiRenderer::Create({
			.Window = Config.Window,
			.Renderer = Config.Renderer
		});
		
	}

	void GuiSystem::InitSystem() {
		VSystem::InitSystem();
	}

	void GuiSystem::StartSystem() {
		VSystem::StartSystem();
	}

	void GuiSystem::Iterate(float DeltaTime) {
		
	}

	GuiSystem::~GuiSystem() {}
}
