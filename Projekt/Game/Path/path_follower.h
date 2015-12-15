#pragma once

#include "ipath_handler.h"
#include "../Component/icomponent.h"

class PathFollower : public IComponent
{
public:
	PathFollower(IPathHandler* pathHandler);

	virtual void update() override;

private:
	IPathHandler* pathHandler;
};