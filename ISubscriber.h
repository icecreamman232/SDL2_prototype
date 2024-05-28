#pragma once

template <typename EventType>
class ISubscriber
{
public:
	virtual void OnTriggerEvent(const EventType& eventType) = 0;
};

