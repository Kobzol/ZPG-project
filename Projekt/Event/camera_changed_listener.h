#pragma once

#include "event_listener.h"

class Camera;

class CameraChangedListener : public EventListener
{
public:
	virtual void notifyCameraChanged(Camera& camera) = 0;
};