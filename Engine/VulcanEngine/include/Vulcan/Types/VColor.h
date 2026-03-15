#pragma once
#include <Export.h>
#include <cstdint>
#include <ostream>
#include <string>


namespace VulcanEngine {

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

		// Getters
		float R() const { return _R; }
		float G() const { return _G; }
		float B() const { return _B; }
		float A() const { return _A; }

		std::string ToString() { return "[R: " + std::to_string(_R) + " G: " + std::to_string(_G) + " B: " + std::to_string(_B) + " A: " + std::to_string(_A); }
	
	private:

	
		float _OpenColorPicker;
		float _R, _G, _B, _A;

		float _ColorPickerArray[4];
	};

	VULCAN_ENGINE_API std::ostream& operator<<(std::ostream& Stream, const VColor& Color);

}

