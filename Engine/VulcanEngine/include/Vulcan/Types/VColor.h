#pragma once
#include <CoreAPI/precomp.h>


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

}

