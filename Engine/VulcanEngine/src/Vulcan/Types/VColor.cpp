#include <Types/VColor.h>
#include <fmt/core.h>

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
	
	VULCAN_ENGINE_API std::ostream& operator<<(std::ostream& Stream, const VColor& Color) {
		return Stream << "Color (" << Color.R() << ", " << Color.G() << ", " << Color.B() << ", " << Color.A() << ")";
	}

}

