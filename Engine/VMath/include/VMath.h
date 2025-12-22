#pragma once


namespace VMath {

	constexpr float Pi = 3.1415926535897932384626433832795f;

	constexpr float Deg2Rad = Pi / 180.f;
	constexpr float Rad2Deg = 180.f / Pi;

	inline float Clamp(float Value, float Min, float Max) {
		if (Value >= Min && Value <= Max) {
			return Value;
		}
		else if (Value < Min) {
			return Min;
		}
		else {
			return Max;
		}
	}

	inline bool IsNearlyEqual(float Value, float Min,float Max) {
		return Min <= Value && Value <= Max;
	}

	template<typename U,typename T>
	static bool IsBetween(U Value, T Min, T Max) {
		return Min <= Value && Value <= Max;
	}



}