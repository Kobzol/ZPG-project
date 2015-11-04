#pragma once

#include <algorithm>
#include <set>
#include <unordered_map>
#include <vector>

#include "game_object.h"

class ObjectManager
{
public:
	ObjectManager(size_t maxSize = 100);

	GameObject* get(int id);
	void add(GameObject* object);
	void markForRemoval(GameObject* object);
	void removeMarkedObjects();

	size_t getObjectCount();
	std::vector<GameObject*>& getObjects();

	GameObject* findByName(const std::string& name);
	std::vector<GameObject*> findByTag(Tag tag);

	void dispose();

private:
	static int objectId;

	ObjectManager(const ObjectManager& other);
	ObjectManager& operator=(const ObjectManager& other);

	void remove(size_t index);

	std::vector<GameObject*> objects;
	std::unordered_map<int, size_t> indexMap;
	std::set<int> removalList;

	size_t maxSize;
	size_t nextIndex;
};