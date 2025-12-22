#pragma once
#include <nlohmann/json.hpp>

#include "Vector2.h"
#include "Types/VColor.h"

namespace VulcanEngine {
	using namespace VMath;
	template<typename T>
	void from_json(const nlohmann::json& Json, Vector2<T>& Vec) {
		Vec.X = Json.at("x");
		Vec.Y = Json.at("y");
	}

	template<typename T>
	void to_json(nlohmann::json& Json, const Vector2<T>& Vec) {
		Json["x"] = Vec.X;
		Json["y"] = Vec.Y;
	}

	void from_json(const nlohmann::json& Json, VColor Color) {
	
	}
}

