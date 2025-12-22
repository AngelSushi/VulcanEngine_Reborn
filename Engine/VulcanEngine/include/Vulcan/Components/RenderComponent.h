#pragma once
#include <Components/VComponent.h>

#include <Export.h>
#include <Types/Assets/SpriteAsset.h>
#include <Types/Button.h>

namespace VulcanEngine {
	class Renderable;

	class VULCAN_ENGINE_API RenderComponent : public VComponent {
	
	public:
/*
		// Constructors
		RenderComponent() = default;
		RenderComponent(std::unique_ptr<Sprite>&&);
		RenderComponent(const RenderComponent&) = delete;
		RenderComponent(RenderComponent&&) noexcept;

		// Operators
		//RenderComponent& operator=(const RenderComponent&);
		RenderComponent& operator=(RenderComponent&&) noexcept;

		void OpenSpriteEditor();

		// VComponent's Functions
		std::string GetComponentName() override {
			return "RenderComponent";
		}


		virtual void LoadComponent(const nlohmann::json& Descr) override;
		virtual void SaveComponent(std::vector<std::uint8_t>& ByteArray) override;
	
		// Getters
		const std::shared_ptr<const Renderable>& GetRenderable() const { return _Sprite; }
		const float* GetColor() const { return _Color; }

		// Destructors 
		~RenderComponent();

	protected:
		std::shared_ptr<Sprite> _Sprite;
		Button _SpriteButton;

		std::string _RenderableName;
		float _Color[4];
		*/
	};

}


