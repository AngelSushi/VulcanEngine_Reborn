#pragma once
#include <iostream>
#include <nlohmann/json.hpp>

#include "Vector2.h"
#include "Types/VColor.h"

namespace VulcanEngine {

	class JsonSerializer {
	public:
		// Care of std::tuple maybe not work on all compilers (e.g console,linux,etc)
		template<typename T>
		static std::tuple<T,bool> Load(const std::string_view& Content) {
			try {
				nlohmann::json JsonObject = nlohmann::json::parse(Content);
				T Data = JsonObject.get<T>();
				return { Data, true };
			} catch (nlohmann::json::exception& e) {
				std::cerr << e.what() << '\n';
				return { T{}, false };
			}
		}

		template<typename T>
		static void LoadAll(const std::vector<std::string>& In,std::vector<T>& Out) {
			for (const std::string& Content : In) {
				auto [Data,Succeed] = Load<T>(Content);

				if (Succeed) {
					Out.push_back(Data);	
				}
			}
		}
	};

	
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

