#include "event_broadcaster.h"

void EventBroadcaster::setCallback(std::function<void(EventListener*)> notifyCallback)
{
	this->notifyCallback = notifyCallback;
}

void EventBroadcaster::attachListener(EventListener* listener)
{
	if (std::find(this->listeners.begin(), this->listeners.end(), listener) == this->listeners.end())
	{
		this->listeners.push_back(listener);
	}
}

void EventBroadcaster::detachListener(EventListener* listener)
{
	auto found = std::find(this->listeners.begin(), this->listeners.end(), listener);
	if (found != this->listeners.end())
	{
		this->listeners.erase(found);
	}
}

void EventBroadcaster::notify()
{
	for (EventListener* listener : this->listeners)
	{
		this->notifyCallback(listener);
	}
}