#include "object_manager.h"

int ObjectManager::objectId = 0;

ObjectManager::ObjectManager(int maxSize) : maxSize(maxSize)
{
	this->objects.resize(maxSize);
	std::fill(this->objects.begin(), this->objects.end(), nullptr);

	for (int i = maxSize - 1; i >= 0; i--)
	{
		this->freeSpots.push(i);
	}
}

GameObject* ObjectManager::get(int id)
{
	if (this->indexMap.count(id))
	{
		return this->objects[this->indexMap[id]];
	}
	else throw std::runtime_error("No object with id " + std::to_string(id) + " exists.");
}
void ObjectManager::add(GameObject* object)
{
	if (!this->freeSpots.empty())
	{
		int nextSpot = this->freeSpots.top();
		this->freeSpots.pop();

		int id = ObjectManager::objectId++;

		object->setId(id);

		this->indexMap.emplace(id, nextSpot);
		this->objects[nextSpot] = object;
	}
	else throw std::overflow_error("Cannot add another object to this manager.");
}
void ObjectManager::markForRemoval(GameObject* object)
{
	int objectId = object->getId();

	if (this->indexMap.count(objectId))
	{
		this->removalList.insert(objectId);
	}
	else throw std::runtime_error("No object with id " + std::to_string(objectId) + " exists.");
}
void ObjectManager::removeMarkedObjects()
{
	for (int objectId : this->removalList)
	{
		this->remove(this->indexMap[objectId]);
	}

	this->removalList.clear();
}

void ObjectManager::dispose()
{
	for (std::pair<int, int> objectRecord : this->indexMap)
	{
		GameObject* object = this->objects[objectRecord.second];
		if (object != nullptr)
		{
			this->objects[objectRecord.second] = nullptr;

			object->dispose();
			delete object;
		}
	}
}

void ObjectManager::remove(int index)
{
	GameObject* object = this->objects[index];
	int objectId = object->getId();

	this->indexMap.erase(objectId);
	this->objects[index] = nullptr;
	this->freeSpots.push(index);

	object->dispose();
	delete object;
}