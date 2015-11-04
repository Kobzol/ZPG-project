#include "sphere_bounding_box.h"

SphereBoundingBox::SphereBoundingBox(float radius) : radius(radius)
{

}

bool SphereBoundingBox::collidesWith(Transform& hostTransform, Transform& remoteTransform, SphereBoundingBox* remoteBoundingBox)
{
	return glm::length(remoteTransform.getPosition() - hostTransform.getPosition()) < this->radius + remoteBoundingBox->radius;
}