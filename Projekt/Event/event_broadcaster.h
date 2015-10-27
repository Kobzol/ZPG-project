#pragma once

#include <algorithm>
#include <vector>

template <typename Listener, typename... Args>
class EventBroadcaster
{
private:
	std::vector<Listener*> listeners;
	void (Listener::*callback)(Args... args);

public:
	EventBroadcaster() : callback(nullptr)
	{

	}

	void setCallback(void (Listener::*callback)(Args... args))
	{
		this->callback = callback;
	}

	void attachListener(Listener* listener)
	{
		if (std::find(this->listeners.begin(), this->listeners.end(), listener) == this->listeners.end())
		{
			this->listeners.push_back(listener);
		}
	}
	void detachListener(Listener* listener)
	{
		auto found = std::find(this->listeners.begin(), this->listeners.end(), listener);
		if (found != this->listeners.end())
		{
			this->listeners.erase(found);
		}
	}
	void notify(Args... args)
	{
		for (Listener* t : this->listeners)
		{
			(t->*callback)(args...);
		}
	}
};