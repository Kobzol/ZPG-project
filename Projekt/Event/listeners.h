#pragma once

class Camera;

class CameraViewChangedListener
{
public:
	virtual void onCameraViewChanged(Camera& camera) = 0;
};

class CameraProjectionChangedListener
{
public:
	virtual void onCameraProjectionChanged(Camera& camera) = 0;
};

class CameraPositionChangedListener
{
public:
	virtual void onCameraPositionChanged(Camera& camera) = 0;
};