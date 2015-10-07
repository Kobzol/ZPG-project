#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "event_listener.h"
#include "camera_changed_listener.h"

class EventBroadcaster
{
private:
	std::vector<EventListener*> listeners;
	std::function<void(EventListener*)> notifyCallback;

public:
	void setCallback(std::function<void(EventListener*)> notifyCallback);
	void attachListener(EventListener* listener);
	void detachListener(EventListener* listener);
	void notify();
};