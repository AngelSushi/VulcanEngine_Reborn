#pragma once
#include <memory>

#include <Export.h>
#include <Systems/VSystem.h>

#include <CoreAPI/VCore.h>

namespace VulcanEngine {

	class VRenderer;

	struct RenderSystemConfig {
		std::string Title;
		std::optional<VMath::Vector2i> Position{};
		VMath::Vector2i Size{};
		std::uint32_t Flags = 0;
	};
	
	class VULCAN_ENGINE_API RenderSystem  : public VSystem {

	public:
		static RenderSystem& Instance() {
			static RenderSystem instance;
			return instance;
		}
		
		// Constructors
		RenderSystem();
		RenderSystem(bool isActive, bool isEditorSystem) : VSystem(isActive, isEditorSystem) {}
		// Destructors
		~RenderSystem() override = default;

		
		// VSystem's Functions
		void InitSystem() override;
		void StartSystem() override;
		void Iterate(float DeltaTime) override;
		void OnPreFrame() override;
		void OnPostFrame() override;
		
		void Shutdown() override;
		
		static void SetConfig(const RenderSystemConfig& config) { Config = config; }
	
		
	private:
		static inline RenderSystemConfig Config{};
	};
}

