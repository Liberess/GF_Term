#pragma once

#include <SDL.h>

class Timer
{
public:
	Timer();
	~Timer() {};
	void setInterval(int interval);
	void start();
	void pause();
	void resume();
	bool done();

private:
	int m_interval;
	int m_startTicks;
	int m_pauseTicks;
};