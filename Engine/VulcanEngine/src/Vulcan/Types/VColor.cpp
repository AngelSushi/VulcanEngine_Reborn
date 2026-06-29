#include <Types/VColor.h>
#include <fmt/core.h>

namespace VulcanEngine {

	VColor::VColor() : VColor(1.0f,1.0f,1.0f,1.0f) {}

	VColor::VColor(float Red, float Green, float Blue, float Alpha /* = 1.0f */) : RValue(Red),GValue(Green),BValue(Blue),AValue(Alpha) {
	}

	VColor::VColor(std::string_view InHex) {
		if (InHex.empty()) {
			RValue = 1.f;
			GValue = 1.f;
			BValue = 1.f;
			AValue = 1.f;
		}
		else {
			if (InHex.front()=='#') {
				InHex.remove_prefix(1);
			}

			unsigned v = std::stoul(std::string(InHex), nullptr, 16);
		
			if (InHex.size() == 6) { // RRGGBB
				RValue = float((v >> 16) & 0xFF) / 255.f;
				GValue = float((v >> 8) & 0xFF) / 255.f;
				BValue = float(v & 0xFF) / 255.f;
				AValue = 1.f;
			}
			else if (InHex.size() == 8) {// RRGGBBAA
				RValue = float((v >> 24) & 0xFF) / 255.f;
				GValue = float((v >> 16) & 0xFF) / 255.f;
				BValue = float((v >> 8) & 0xFF) / 255.f;
				AValue = float(v & 0xFF) / 255.f;
			}
			else {
				RValue = 1.f;
				GValue = 1.f;
				BValue = 1.f;
				AValue = 1.f;
			}
		}
	}

	VColor VColor::Lighten(float Amount) const {
		return VColor(std::min(RValue + Amount, 1.f),std::min(GValue + Amount, 1.f),std::min(BValue + Amount, 1.f),AValue);
	}

	VColor VColor::Darken(float Amount) const {
		return VColor(std::max(RValue - Amount, 0.f),std::max(GValue - Amount, 0.f),std::max(BValue - Amount, 0.f),AValue);
	}
	
	void VColor::ToRGBA8(std::uint8_t& R, std::uint8_t& G, std::uint8_t& B, std::uint8_t A /* = 1.0f */) const {
		R = static_cast<std::uint8_t>(RValue * 255.f);
		G = static_cast<std::uint8_t>(G * 255.f);
		B = static_cast<std::uint8_t>(B * 255.f);
		A = static_cast<std::uint8_t>(A * 255.f);
	}

	VColor VColor::FromRGBA8(std::uint8_t R, std::uint8_t G, std::uint8_t B, std::uint8_t A /* = 1.0f */) {
		float invColor = 1.f / 255.f;
		return { R * invColor, G * invColor, B * invColor, A * invColor };
	}
	
	VULCAN_ENGINE_API std::ostream& operator<<(std::ostream& Stream, const VColor& Color) {
		return Stream << "Color (" << Color.R() << ", " << Color.G() << ", " << Color.B() << ", " << Color.A() << ")";
	}

}

