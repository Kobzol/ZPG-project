#pragma once

#include "../Physics/transform.h"

class IPathHandler
{
public:
	virtual void move(Transform& transform) = 0;
};