#pragma once

class SemaphoreClock
{
#ifdef _MSC_VER
	void* m_handle = nullptr;
#else
	sem_t  m_handle = 0;
#endif _MSC_VER
public:
	SemaphoreClock();
	~SemaphoreClock();

	void raiseEvent() const;
	bool waitEvent(int nTimeOut = 50) const;
};
