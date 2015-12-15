#include "path_follower.h"
#include "../Object/game_object.h"

PathFollower::PathFollower(IPathHandler* pathHandler) : pathHandler(pathHandler)
{

}

void PathFollower::update()
{
	this->pathHandler->move(this->getGameObject()->getTransform());
}