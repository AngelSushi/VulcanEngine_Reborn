#pragma once
#include <Export.h>
#include <string>

namespace VulcanEngine {
	class VULCAN_ENGINE_API VType {
	public:
		VType() = default;
		~VType() = default;

		virtual int DrawInspector(std::string Label, VType& Value) = 0;
	};
}

