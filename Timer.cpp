#include "Timer.h"
#include <SDL_timer.h>

Timer::Timer(float duration, std::function<void()> callback)
{
	m_duration = duration;
	m_callback = callback;

	//Input will be passed as seconds but SDL take time as miliseconds so we multiple 1000 here
	TimerID = SDL_AddTimer(duration * 1000, TimerCallbackStatic, this);
}

Uint32 Timer::TimerCallbackStatic(Uint32 interval, void* param)
{
	Timer* instance = static_cast<Timer*>(param);
	instance->m_callback();

	//Automatically remove timer once it's completed
	SDL_RemoveTimer(instance->TimerID);
	instance->TimerID = 0;
	return 0;
}
