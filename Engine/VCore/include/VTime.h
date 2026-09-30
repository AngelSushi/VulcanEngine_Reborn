#pragma once
#include <CoreAPI/precomp.h>


// MAybe useless to put in VCore cause we only need for LogSystem in VCore Module, see for changes after. 
class VCORE_API VTime {

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



