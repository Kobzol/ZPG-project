#pragma once

class Camera;

class CameraChangedListener
{
public:
	void notifyCameraChangedStatic(Camera& camera)
	{
		this->notifyCameraChanged(camera);
	}
	virtual void notifyCameraChanged(Camera& camera) = 0;
};