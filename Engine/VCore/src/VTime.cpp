#include <SDL.h>
#include <VTime.h>

namespace VulcanEngine {
	std::tm VTime::GetActualTime() {
		using namespace std::chrono;

		auto now = system_clock::now();
		std::time_t now_c = system_clock::to_time_t(now);

		std::tm local_time;
		localtime_s(&local_time, &now_c);

		return local_time;
	}


	std::string VTime::ToString(const std::tm& InTimeInfo) {
		std::ostringstream oss;
		oss << std::put_time(&InTimeInfo, "%H:%M:%S");
		return oss.str();
	}

	VTime::VTime() : _LastTime(SDL_GetPerformanceCounter()) {}

	float VTime::GetElapsedTime() const {
		float ElapsedTime = (float)(SDL_GetPerformanceCounter() - _LastTime) / SDL_GetPerformanceFrequency();
		return ElapsedTime;
	}

	float VTime::GetElapsedTime(std::uint64_t Now, std::uint64_t LastTime) {
		return (float)(Now - LastTime) / SDL_GetPerformanceFrequency();
	}

	float VTime::Restart() {
		float Now = SDL_GetPerformanceCounter();
		float ElapsedTime = GetElapsedTime(Now, _LastTime);
		_LastTime = Now;

		return ElapsedTime;
	}

}


