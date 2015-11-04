#pragma once

#include "Object/game_object.h"
#include "Object/object_manager.h"

class Scene
{
public:
	void update();
	void draw();

	void updateFrameEnd();

	void dispose();

	void add(GameObject* object);

private:
	ObjectManager objectManager;
};