#pragma once
#include <Export.h>
#include <string>
#include <vector>


namespace VulcanEngine {

	class VULCAN_ENGINE_API VFont {

	public:
		// Constructors
		VFont()  = default; 
		VFont(std::string_view InFont);
		
		static std::vector<std::string> GetAvailableExtensions() {
			return { ".ttf", ".otf", ".woff", ".woff2" };
		}
	};

}

