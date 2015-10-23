#pragma once

#include <algorithm>
#include <vector>

template <typename T, typename... Args>
class EventBroadcaster
{
private:
	std::vector<T*> listeners;
	void (T::*callback)(Args... args);

public:
	EventBroadcaster(void (T::*callback)(Args... args)) : callback(callback)
	{
		
	}

	void attachListener(T* listener)
	{
		if (std::find(this->listeners.begin(), this->listeners.end(), listener) == this->listeners.end())
		{
			this->listeners.push_back(listener);
		}
	}
	void detachListener(T* listener)
	{
		auto found = std::find(this->listeners.begin(), this->listeners.end(), listener);
		if (found != this->listeners.end())
		{
			this->listeners.erase(found);
		}
	}
	void notify(Args... args)
	{
		for (T* t : this->listeners)
		{
			(t->*callback)(args...);
		}
	}
};