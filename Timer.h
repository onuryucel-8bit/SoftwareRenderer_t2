#pragma once

#include <chrono>

//TODO fix this !!

namespace util
{
	class Timer
	{
	public:
		Timer();
		~Timer();

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> startPoint;
		
	};

	inline Timer::Timer()
	{

	}

	inline Timer::~Timer()
	{
	}
}