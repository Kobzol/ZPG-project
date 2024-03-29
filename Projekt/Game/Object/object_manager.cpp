#include "object_manager.h"

int ObjectManager::objectId = 0;

ObjectManager::ObjectManager(size_t maxSize) : maxSize(maxSize), nextIndex(0)
{
	this->objects.resize(maxSize);
	std::fill(this->objects.begin(), this->objects.end(), nullptr);
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
	if (this->nextIndex < this->maxSize)
	{
		size_t nextSpot = this->nextIndex++;

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

size_t ObjectManager::getObjectCount()
{
	return this->nextIndex;
}
std::vector<GameObject*>& ObjectManager::getObjects()
{
	return this->objects;
}

GameObject* ObjectManager::findByName(const std::string& name)
{
	auto found = std::find_if(this->objects.begin(), this->objects.begin() + this->getObjectCount(), [name](GameObject* obj) -> bool { return obj->getName() == name; });

	if (found != this->objects.end())
	{
		return *found;
	}
	else return nullptr;
}
std::vector<GameObject*> ObjectManager::findByTag(Tag tag)
{
	std::vector<GameObject*> found;
	size_t count = this->getObjectCount();

	for (size_t i = 0; i < count; i++)
	{
		if (this->objects[i]->getTags().isSet(tag))
		{
			found.push_back(this->objects[i]);
		}
	}

	return found;
}

void ObjectManager::dispose()
{
	for (std::pair<int, size_t> objectRecord : this->indexMap)
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

void ObjectManager::remove(size_t index)
{
	GameObject* object = this->objects[index];
	int objectId = object->getId();

	size_t maxIndex = this->nextIndex - 1;
	GameObject* movedObject = this->objects[maxIndex];

	this->indexMap.erase(objectId);

	if (object != movedObject)
	{
		this->objects[index] = movedObject;
		this->indexMap[movedObject->getId()] = index;
		this->objects[maxIndex] = nullptr;
	}
	else this->objects[index] = nullptr;	// the removed object is the last one
	
	this->nextIndex--;

	object->dispose();
	delete object;
}