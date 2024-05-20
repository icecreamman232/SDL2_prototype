#pragma once
#include "SDL.h"
#include <functional>
class Timer
{
public:
	Timer(float duration,std::function<void()> callback);
	SDL_TimerID TimerID;

private:
	float m_duration;
	std::function<void()> m_callback;

	//Best about c++ and SDL here. We cant have different signature for this function.
	//  So it has to be like this and be static
	static Uint32 TimerCallbackStatic(Uint32 interval, void* param);
};

