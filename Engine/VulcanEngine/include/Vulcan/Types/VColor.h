#pragma once
#include <Export.h>
#include <cstdint>
#include <imgui.h>
#include <ostream>
#include <Types/VType.h>
#include <CoreAPI/precomp.h>


struct Clay_Color;

class VULCAN_ENGINE_API VColor {
	friend class JsonSerializer;

public:
	// Constructors
	VColor();
	VColor(float Red, float Green, float Blue, float Alpha = 1.0f);
	VColor(std::string_view InHex);

	VColor Lighten(float Amount) const;
	VColor Darken(float Amount) const;
	

	void ToRGBA8(std::uint8_t& R, std::uint8_t& G, std::uint8_t& B, std::uint8_t A = 1.0f) const;
	VColor FromRGBA8(std::uint8_t R, std::uint8_t G, std::uint8_t B, std::uint8_t A = 1.0f);

	Clay_Color ToClay() const;

	// Getters
	float R() const { return RValue; }
	float G() const { return GValue; }
	float B() const { return BValue; }
	float A() const { return AValue; }

	std::string ToString() { return "[R: " + std::to_string(R()) + " G: " + std::to_string(G()) + " B: " + std::to_string(B()) + " A: " + std::to_string(A()); }

private:
	
	float RValue;
	float GValue;
	float BValue;
	float AValue;
};

VULCAN_ENGINE_API std::ostream& operator<<(std::ostream& Stream, const VColor& Color);

namespace VulcanEngine {

	class VULCAN_ENGINE_API VColor : public VType {
		friend class JsonSerializer;

	public:
		// Constructors
		VColor();
		VColor(float Red, float Green, float Blue, float Alpha = 1.0f);
		VColor(std::string_view InHex);

		operator ImVec4() const { 
			return ImVec4{_R, _G, _B, _A };
		}

		VColor Lighten(float Amount) const;
		VColor Darken(float Amount) const;
		

		void ToRGBA8(std::uint8_t& R, std::uint8_t& G, std::uint8_t& B, std::uint8_t A = 1.0f) const;
		VColor FromRGBA8(std::uint8_t R, std::uint8_t G, std::uint8_t B, std::uint8_t A = 1.0f);

		// Getters
		float R() const { return _R; }
		float G() const { return _G; }
		float B() const { return _B; }
		float A() const { return _A; }

		std::string ToString() { return "[R: " + std::to_string(_R) + " G: " + std::to_string(_G) + " B: " + std::to_string(_B) + " A: " + std::to_string(_A); }
		
		// VType Functions
		int DrawInspector(std::string Label, VType& Value) override;

	private:

		void ShowColorPicker(std::string Label, VType& Value); // Possible to do with new window

		float _OpenColorPicker;
		float _R, _G, _B, _A;

		float _ColorPickerArray[4];
	};

	VULCAN_ENGINE_API std::ostream& operator<<(std::ostream& Stream, const VColor& Color);

}

