#include "scene.h"

void Scene::update()
{
	const std::vector<GameObject*>& objects = this->objectManager.getObjects();
	size_t objectCount = this->objectManager.getObjectCount();

	for (size_t i = 0; i < objectCount; i++)
	{
		objects[i]->update();
	}
}
void Scene::draw()
{
	const std::vector<GameObject*>& objects = this->objectManager.getObjects();
	size_t objectCount = this->objectManager.getObjectCount();

	for (size_t i = 0; i < objectCount; i++)
	{
		objects[i]->draw();
	}
}

void Scene::updateFrameEnd()
{
	this->objectManager.removeMarkedObjects();
}

void Scene::dispose()
{
	this->objectManager.dispose();
}

void Scene::add(GameObject* object)
{
	this->objectManager.add(object);
}