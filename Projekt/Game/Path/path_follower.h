#pragma once

#include <vector>

#include "ipath_handler.h"
#include "../Component/icomponent.h"

class PathFollower : public IComponent
{
public:
	PathFollower(std::initializer_list<IPathHandler*> pathHandlers);

	virtual void update() override;

private:
	std::vector<IPathHandler*> pathHandlers;
	size_t currentHandler;
};