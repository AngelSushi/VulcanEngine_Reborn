#include <Components/RenderComponent.h>
#include <imgui.h>
#include <fmt/core.h>
#include <CoreAPI/VCore.h>

namespace VulcanEngine {
	/*RenderComponent::RenderComponent(std::unique_ptr<Sprite>&& RenderSprite)
		: _Sprite(std::move(RenderSprite)),_SpriteButton("Open Sprite Editor") {
		
		_Color[0] = 1.F;
		_Color[1] = 1.F;
		_Color[2] = 1.F;
		_Color[3] = 1.F;

		_SpriteButton.OnPressedButton = std::bind(&RenderComponent::OpenSpriteEditor, this);
	}
	

	RenderComponent::RenderComponent(RenderComponent&& MoveRender) noexcept 
		 : _Sprite(std::move(MoveRender._Sprite)),_SpriteButton(std::move(MoveRender._SpriteButton)) {

		_Color[0] = MoveRender._Color[0];
		_Color[1] = MoveRender._Color[1];
		_Color[2] = MoveRender._Color[2];
		_Color[3] = MoveRender._Color[3];
	}

	RenderComponent& RenderComponent::operator=(RenderComponent&& MoveRender) noexcept {
		_Sprite = std::move(MoveRender._Sprite);
		_SpriteButton = std::move(MoveRender._SpriteButton);

		_Color[0] = MoveRender._Color[0];
		_Color[1] = MoveRender._Color[1];
		_Color[2] = MoveRender._Color[2];
		_Color[3] = MoveRender._Color[3];

		return *this;
	}

	void RenderComponent::OpenSpriteEditor() {
		ImGui::PopStyleColor(1);
		/*VCore& Core = VCore::Instance();

		std::unique_ptr<SpriteWindow> SpriteCreatorWindow = std::make_unique<SpriteWindow>(_Sprite, "Sprite Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Core.GetScreenSize().X / 1.15F, Core.GetScreenSize().Y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		Core.AddNewWindow(std::move(SpriteCreatorWindow));

	}

	void RenderComponent::LoadComponent(const nlohmann::json& Descr) {
	}

	void RenderComponent::SaveComponent(std::vector<std::uint8_t>& ByteArray) {
	}

	RenderComponent::~RenderComponent() {
	}
*/

}