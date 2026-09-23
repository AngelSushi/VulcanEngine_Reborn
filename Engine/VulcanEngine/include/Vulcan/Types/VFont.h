#pragma once
#include <Export.h>
#include <string>
#include <vector>

class VULCAN_ENGINE_API VFont {

public:
	// Constructors
	VFont()  = default; 
	VFont(std::string_view InFont);
	
	static std::vector<std::string> GetAvailableExtensions() {
		return { ".ttf", ".TTF", ".otf", ".woff", ".woff2" };
	}
};



