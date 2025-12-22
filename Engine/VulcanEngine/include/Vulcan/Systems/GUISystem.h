#pragma once
#include <memory>
#include <Export.h>
#include <Systems/VSystem.h>

#include <CoreAPI/VRenderer.h>
#include <CoreAPI/VWindow.h>

namespace VulcanEngine {

	class VRenderer;

	class GuiSystemConfig {
	public:
		VWindow& Window;
		Graphics::VRenderer& Renderer;
	};
	
	class VULCAN_ENGINE_API GuiSystem  : public VSystem {

	public:
		// Constructors
		GuiSystem(const GuiSystemConfig& Config);
		GuiSystem(bool isActive, bool isEditorSystem) : VSystem(isActive, isEditorSystem) {}

		// VSystem's Functions
		void InitSystem() override;
		void StartSystem() override;
		void Iterate(float DeltaTime) override;

		// Destructors
		~GuiSystem() override;

	private:
		std::unique_ptr<ImGuiRenderer> GuiRenderer;
	};
}

