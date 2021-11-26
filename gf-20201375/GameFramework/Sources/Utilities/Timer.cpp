#include "Timer.h"

Timer::Timer()
{
    m_interval = 0;
    m_startTicks = 0;
    m_pauseTicks = 0;
}

void Timer::setInterval(int interval)
{
    m_interval = interval;
}

void Timer::start()
{
    m_startTicks = SDL_GetTicks();
}

void Timer::pause()
{
    if (m_pauseTicks == 0)
        m_pauseTicks = SDL_GetTicks();
}

void Timer::resume()
{
    if (m_pauseTicks == 0)
        return;

    m_startTicks += SDL_GetTicks() - m_pauseTicks;
    m_pauseTicks = 0;
}

bool Timer::done()
{
    if (m_pauseTicks == 0 && SDL_GetTicks() - m_startTicks >= m_interval)
    {
        start();
        return true;
    }

    return false;
}