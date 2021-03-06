#pragma once
#include <chrono>

class ClockTimer
{
	using timer = std::chrono::time_point<std::chrono::high_resolution_clock>;
	using clock = std::chrono::high_resolution_clock;
	using duration = std::chrono::duration<float, std::milli>;

	timer m_timer = clock::now();

public:

	void reset()
	{
		m_timer = clock::now();
	}

	float elapse_ms() const
	{
		return duration(clock::now() - m_timer).count();
	}
};
