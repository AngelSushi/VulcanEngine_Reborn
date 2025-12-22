#include <VDrawHelper.h>
#include <stdexcept>
#include <fmt/core.h>

namespace VulcanEngine {

	VDrawHelper* VDrawHelper::_Instance = nullptr;

	VDrawHelper::VDrawHelper() {
		if (_Instance) {
			throw new std::runtime_error("Only one VDrawRenderer can be initialize");
		}

		_Instance = this;
	}

	VDrawHelper::~VDrawHelper() {
	}

	void VDrawHelper::DrawTitleBar(const char* Title) {	
		VMath::Vector2f WindowPos = VMath::Vector2f{ ImGui::GetWindowPos().x , ImGui::GetWindowPos().y };
		ImVec2 CurrentWindowSize = ImGui::GetWindowSize();
		float TitleHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f + 5.F;

		ImDrawList* DrawList = ImGui::GetWindowDrawList();

		DrawList->AddRectFilled(ImVec2{ WindowPos.x, WindowPos.y }, ImVec2(WindowPos.x + CurrentWindowSize.x, WindowPos.y + TitleHeight), IM_COL32(48, 48, 48, 255));

		ImGui::BeginGroup();

		VMath::Vector2f TextPosition = VMath::Vector2f{ ImGui::GetCursorPos().x, ImGui::GetCursorPos().y };
		VMath::Vector2f TextSize = VMath::Vector2f{ ImGui::CalcTextSize(Title).x, ImGui::CalcTextSize(Title).y };

		ImVec2 StartPosition = ImVec2{ WindowPos.x + TextPosition.x - 10,WindowPos.y };
		ImVec2 EndPosition = ImVec2{ WindowPos.x + TextPosition.x + 10 + TextSize.x,WindowPos.y + TitleHeight };

		DrawList->AddRectFilled(StartPosition, EndPosition, IM_COL32(84, 84, 84, 255));

		ImGui::Text(Title);

		ImGui::EndGroup();
	}

	void VDrawHelper::Spacing(float Count /* = 1*/) {
		for (int i = 0; i < Count; i++) {
			ImGui::Spacing();
		}
	}

	void VDrawHelper::FillRectText(const char* Text, ImVec2 StartOffset, ImVec2 EndOffset, ImU32 Color, float Rounding /*= 0.0f*/) {
		ImDrawList* DrawList = ImGui::GetWindowDrawList();
		ImVec2 WindowPosition = ImGui::GetWindowPos();
		
		ImVec2 TextPosition = ImGui::GetCursorPos();
		ImVec2 TextSize = ImGui::CalcTextSize(Text);

		ImVec2 Start = ImVec2{ WindowPosition.x + TextPosition.x - StartOffset.x, WindowPosition.y + TextPosition.y - StartOffset.y };
		ImVec2 End = ImVec2{ WindowPosition.x + TextPosition.x + TextSize.x + EndOffset.x,WindowPosition.y + TextPosition.y + TextSize.y + EndOffset.x};

		DrawList->AddRectFilled(Start, End, Color,Rounding);
	}

	void VDrawHelper::DrawRect(VMath::Vector2i Start, VMath::Vector2i End,ImU32 Color,float Size) {
		DrawRect(ImVec2{ (float)Start.x,(float)Start.y }, ImVec2{ (float)End.x,(float)End.y }, Color,Size);
	}

	void VDrawHelper::DrawRect(ImVec2 Start, ImVec2 End, ImU32 Color,float Size) {
		ImDrawList* DrawList = ImGui::GetWindowDrawList();

		DrawList->AddRect(Start, End, Color, 1,0,Size);
	}

	void VDrawHelper::DrawCircle(VMath::Vector2i Center, ImU32 Color, float Radius) {
		DrawCircle(ImVec2{ (float)Center.x,(float)Center.y }, Color, Radius);
	}

	void VDrawHelper::DrawCircle(ImVec2 Center, ImU32 Color, float Radius) {
		ImDrawList* DrawList = ImGui::GetWindowDrawList();

		DrawList->AddCircleFilled(Center, Radius, Color, 32);
	}

	float VDrawHelper::DrawFloat(std::string Label, float& Value) {
		Spacing();

		ImGui::Text(Label.c_str());
		ImGui::SameLine();

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 1.5f);

		float TextSize = ImGui::CalcTextSize(Label.c_str()).x;

		std::string IdName = "##" + Label;

		ImGui::SetNextItemWidth(325 - TextSize);
		if (ImGui::InputFloat(IdName.c_str(), &Value)) {
			Value = Value;
		}

		return 40;
	}

	float VDrawHelper::DrawString(std::string Label, std::string& Value) {
		Spacing();

		ImGui::Text(Label.c_str());
		ImGui::SameLine();

		Value.resize(Value.size() + 1);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 1.5f);

		float TextSize = ImGui::CalcTextSize(Label.c_str()).x;

		ImGui::SetNextItemWidth(325 - TextSize);

		std::string IdName = "##" + Label;

		if (ImGui::InputText(IdName.c_str(), &Value[0], Value.size() + 1)) {
			Value = Value.data();
			Value.resize(strlen(Value.c_str()));
		}

		return 40;
	}

	VDrawHelper& VDrawHelper::Instance() {
		if (!_Instance) {
			throw std::runtime_error("VDrawHelper hasn't been initialized");
		}

		return *_Instance;
	}
}