#pragma once
#include "IDispatcher.h"
#include "MyEvent.h"

class PlayerLevelUpEventDispatcher : public IDispatcher<LevelUpEvent>
{

};