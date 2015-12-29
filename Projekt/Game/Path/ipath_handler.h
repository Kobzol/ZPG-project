#pragma once

#include "../Physics/transform.h"

class IPathHandler
{
public:
	virtual void move(Transform& transform) = 0;
	virtual bool isFinished() = 0;
	virtual void reset() = 0;
};