#include "path_follower.h"
#include "../Object/game_object.h"

PathFollower::PathFollower(std::initializer_list<IPathHandler*> pathHandlers) : pathHandlers(pathHandlers), currentHandler(0)
{

}

void PathFollower::update()
{
	IPathHandler* handler = this->pathHandlers[this->currentHandler];
	handler->move(this->getGameObject()->getTransform());

	if (handler->isFinished())
	{
		handler->reset();
		this->currentHandler = (this->currentHandler + 1) % this->pathHandlers.size();
	}
}