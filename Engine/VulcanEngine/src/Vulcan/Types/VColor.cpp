#include <Types/VColor.h>
#include <fmt/core.h>
#include <imgui.h>
#include <VDrawHelper.h>

namespace VulcanEngine {

	VColor::VColor() : VColor(1.0f,1.0f,1.0f,1.0f) {}

	VColor::VColor(float Red, float Green, float Blue, float Alpha /* = 1.0f */) : _R(Red),_G(Green),_B(Blue),_A(Alpha) {
	}

	VColor::VColor(std::string_view InHex) {
		if (!InHex.empty() && InHex.front()=='#') {
			InHex.remove_prefix(1);
		}

		unsigned v = std::stoul(std::string(InHex), nullptr, 16);
		
		if (InHex.size() == 6) { // RRGGBB
			_R = float((v >> 16) & 0xFF) / 255.f;
			_G = float((v >> 8) & 0xFF) / 255.f;
			_B = float(v & 0xFF) / 255.f;
			_A = 1.f;
		}
		else if (InHex.size() == 8) {// RRGGBBAA
			_R = float((v >> 24) & 0xFF) / 255.f;
			_G = float((v >> 16) & 0xFF) / 255.f;
			_B = float((v >> 8) & 0xFF) / 255.f;
			_A = float(v & 0xFF) / 255.f;
		}
		else {
			_R = 1.f;
			_G = 1.f;
			_B = 1.f;
			_A = 1.f;
		}
	}

	VColor VColor::Lighten(float Amount) const {
		return VColor(std::min(_R + Amount, 1.f),std::min(_G + Amount, 1.f),std::min(_B + Amount, 1.f),_A);
	}

	VColor VColor::Darken(float Amount) const {
		return VColor(std::max(_R - Amount, 0.f),std::max(_G - Amount, 0.f),std::max(_B - Amount, 0.f),_A);
	}
	
	void VColor::ToRGBA8(std::uint8_t& R, std::uint8_t& G, std::uint8_t& B, std::uint8_t A /* = 1.0f */) const {
		R = static_cast<std::uint8_t>(_R * 255.f);
		G = static_cast<std::uint8_t>(G * 255.f);
		B = static_cast<std::uint8_t>(B * 255.f);
		A = static_cast<std::uint8_t>(A * 255.f);
	}

	VColor VColor::FromRGBA8(std::uint8_t R, std::uint8_t G, std::uint8_t B, std::uint8_t A /* = 1.0f */) {
		float invColor = 1.f / 255.f;
		return { R * invColor, G * invColor, B * invColor, A * invColor };
	}

	int VColor::DrawInspector(std::string Label, VType& Value) { 
		VType::DrawInspector(Label,Value);

		VColor& ColorValue = (VColor&)Value;

		VDrawHelper::Instance().Spacing();

		ImGui::Text(Label.c_str());
		ImGui::SameLine();

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 0.5f);

		float TextSize = ImGui::CalcTextSize(Label.c_str()).x;

		ImVec4 Color { ColorValue._R,ColorValue._G,ColorValue._B,ColorValue._A };

		if (ImGui::ColorButton("##Color", Color,ImGuiColorEditFlags_None, ImVec2 {325 - TextSize,25})) {
			_OpenColorPicker = true;
		}

		if (_OpenColorPicker) {
			ShowColorPicker(Label,Value);
		}
		
		return 40;
	}

	void VColor::ShowColorPicker(std::string Label, VType& Value) {
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 85.F / 255.F, 85.F / 255.F, 85.F / 255.F,1.0F });
		VColor& Color = (VColor&)Value;

		ImGui::Begin(Label.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar);

		
		ImGui::SetWindowSize(ImVec2{ 460,510 }, ImGuiCond_FirstUseEver);
		ImGui::SetWindowPos(ImVec2{ 200,200 }, ImGuiCond_FirstUseEver);

		ImDrawList* DrawList = ImGui::GetWindowDrawList();
		ImVec2 WindowPosition = ImGui::GetWindowPos();
		ImVec2 WindowSize = ImGui::GetWindowSize();

		ImVec2 Start = ImVec2{ WindowPosition.x,WindowPosition.y };
		ImVec2 End = ImVec2{ WindowPosition.x + WindowSize.x,WindowPosition.y + 28.F };

		DrawList->AddRectFilled(Start, End, IM_COL32(255, 255, 255, 255), 3);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{ 0.0F,0.0F,0.0F,1.0F });

		ImGui::SetWindowFontScale(1.5F);
		ImGui::Text(Label.c_str());

		ImGui::PopStyleColor();
		
		_ColorPickerArray[0] = Color._R;
		_ColorPickerArray[1] = Color._G;
		_ColorPickerArray[2] = Color._B;
		_ColorPickerArray[3] = Color._A;

		ImGui::SetNextItemWidth(350.F);
		if (ImGui::ColorPicker4("Color", _ColorPickerArray)) {
			Color._R = _ColorPickerArray[0];
			Color._G = _ColorPickerArray[1];
			Color._B = _ColorPickerArray[2];
			Color._A = _ColorPickerArray[3];
		}

		VDrawHelper::Instance().Spacing(4);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 110.F / 255.F,110.F / 255.F,110.F / 255.F,1.0F });
		
		if (ImGui::Button("Apply",ImVec2 { ImGui::GetWindowSize().x - 20.F,30})) {
			_OpenColorPicker = false;
		}
		
		ImGui::PopStyleColor(2);
		ImGui::End();
	}


	VULCAN_ENGINE_API std::ostream& operator<<(std::ostream& Stream, const VColor& Color) {
		return Stream << "Color (" << Color.R() << ", " << Color.G() << ", " << Color.B() << ", " << Color.A() << ")";
	}

}

