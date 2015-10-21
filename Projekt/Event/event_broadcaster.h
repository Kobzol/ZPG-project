#pragma once

#include <algorithm>
#include <vector>

template <typename T, typename R>
class EventBroadcaster
{
private:
	std::vector<T*> listeners;
	void (T::*callback)(R param);

public:
	EventBroadcaster(void (T::*callback)(R param)) : callback(callback)
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
	void notify(R param)
	{
		for (T* t : this->listeners)
		{
			(t->*callback)(param);
		}
	}
};