#pragma once
#include <Export.h>
#include <imgui.h>
#include <string>

// A MODIFIER INCLUDE BIZARRE
#include <Vector2.h>
#include <Vector3.h>


namespace VulcanEngine {

	class VULCAN_ENGINE_API VDrawHelper {

	public:
		VDrawHelper();
		~VDrawHelper();

		void DrawTitleBar(const char* Title);

		void Spacing(float Count = 1);
		void FillRectText(const char* Text, ImVec2 StartOffset, ImVec2 EndOfset,ImU32 Color, float Rounding = 0.0f);
		
		void DrawRect(VMath::Vector2i Start, VMath::Vector2i End, ImU32 Color,float Size);
		void DrawRect(ImVec2 Start, ImVec2 End, ImU32 Color,float Size);

		void DrawCircle(VMath::Vector2i Center, ImU32 Color, float Radius);
		void DrawCircle(ImVec2 Center, ImU32 Color, float Radius);

		float DrawFloat(std::string Label,float& Value);
		float DrawString(std::string Label, std::string& Value);

		template<typename T>
		float DrawVector2(std::string Label, VMath::Vector2<T>& Value);

		template<typename T>
		float DrawVector3(std::string Label, VMath::Vector3<T>& Value);
		
		static VDrawHelper& Instance();

	private:
		static VDrawHelper* _Instance;
	};



	template<typename T>
	inline float VDrawHelper::DrawVector2(std::string Label, VMath::Vector2<T>& Value) {
		Spacing();

		ImGui::Text(Label.c_str());
		ImGui::SameLine();

		float TextSize = ImGui::CalcTextSize(Label.c_str()).x;

		std::string IdName = "##" + Label;

		float Array[2] = { Value.x, Value.y };

		ImGui::SetNextItemWidth(325 - TextSize);
		if (ImGui::InputFloat2(IdName.c_str(), Array)) {
			Value.x = (T) Array[0];
			Value.y = (T) Array[1];
		}

		return 40;
	}
	template<typename T>
	inline float VDrawHelper::DrawVector3(std::string Label, VMath::Vector3<T>& Value) {
		Spacing();

		ImGui::Text(Label.c_str());
		ImGui::SameLine();

		float TextSize = ImGui::CalcTextSize(Label.c_str()).x;

		std::string IdName = "##" + Label;

		float Array[3] = { Value.x, Value.y,Value.z };

		ImGui::SetNextItemWidth(325 - TextSize);
		if (ImGui::InputFloat3(IdName.c_str(), Array)) {
			Value.x = (T) Array[0];
			Value.y = (T) Array[1];
			Value.x = (T) Array[2];
		}

		return 40;
	}
}

