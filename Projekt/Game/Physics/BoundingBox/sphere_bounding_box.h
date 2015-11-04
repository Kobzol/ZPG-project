#pragma once

#include "../transform.h"

class SphereBoundingBox
{
public:
	SphereBoundingBox(float radius = 0.0f);

	bool collidesWith(Transform& hostTransform, Transform& remoteTransform, SphereBoundingBox* remoteBoundingBox);

private:
	float radius;
};