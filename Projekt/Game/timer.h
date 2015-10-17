#pragma once

class Timer
{
public:
	Timer(float cooldownTime = 0.0f);

	void update(float delta);

	bool isReady();
	bool resetIfReady();
	void reset();

	float getElapsed();

private:
	float elapsedTime;
	float cooldownTime;
};