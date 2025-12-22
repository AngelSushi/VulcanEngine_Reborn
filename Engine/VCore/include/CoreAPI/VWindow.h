#pragma once

#include <cstdint>
#include <optional>
#include <CoreAPI/VRenderer.h>
#include <Vector2.h>

struct SDL_Window;

namespace VulcanEngine {
	
	class ImGuiRenderer;
	class VRenderer;


	struct WindowConfig {
		std::string Title;
		std::optional<VMath::Vector2i> Position{};
		VMath::Vector2i Size{};
		std::uint32_t Flags = 0;
	};
	
	class VWindow {
		friend class VRenderer;

	public:
		static std::shared_ptr<VWindow> Create(const WindowConfig& Config) {
			return std::make_shared<VWindow>(Config);
		}
		
		VWindow(const WindowConfig& Config);
		VWindow(const VWindow&) = delete;
		virtual ~VWindow();

		virtual void Start();
		virtual void Update(float DeltaTime);
		void PollEvents(ImGuiRenderer* GUIRenderer = nullptr);
		
		std::string GetTitle() const;

		SDL_Window* GetWindow() { return Window; }

		VWindow& operator=(const VWindow&) = delete;

		bool IsClosed() const { return Close; }
		void CloseWindow() { Close = true; }
		
	protected:
		VRenderer* _Renderer;
		ImGuiRenderer* _ImRenderer;

		bool _FirstFrame = true;

	private:
		SDL_Window* Window;
		
		bool Close{};
	};


}
