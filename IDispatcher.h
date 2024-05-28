#pragma once
#include "ISubscriber.h"
#include <vector>

template <typename EventType>
class IDispatcher
{
public:
	static void Attach(ISubscriber<EventType>* observer) 
	{
		m_observers.push_back(observer);
	};
	static void Detach(ISubscriber<EventType>* observer)
	{
		auto it = std::find(m_observers.begin(), m_observers.end(), observer);
		if (it != m_observers.end())
		{
			m_observers.erase(it);
		}
	};
	static void Trigger(const EventType& eventType)
	{
		for (ISubscriber<EventType>* observer : m_observers)
		{
			observer->OnTriggerEvent(eventType);
		}
	};
private:
	static std::vector<ISubscriber<EventType>*> m_observers;
};

template<typename EventType>
std::vector<ISubscriber<EventType>*> IDispatcher<EventType>::m_observers;
