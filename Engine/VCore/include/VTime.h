#pragma once
#include <chrono>
#include <cstdint>

namespace VulcanEngine {
	class VTime {

		public:
		
			VTime();
		
			static std::tm GetActualTime();
		
			static std::string ToString(const std::tm& InTimeInfo);

			float GetElapsedTime() const;
			float Restart();

		private:
			static float GetElapsedTime(std::uint64_t Now, std::uint64_t LastTime);

			std::uint64_t _LastTime;
	};


}
