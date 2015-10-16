#pragma once

#include <set>
#include <unordered_map>
#include <vector>

#include "game_object.h"

class ObjectManager
{
public:
	ObjectManager(int maxSize = 100);

	GameObject* get(int id);
	void add(GameObject* object);
	void markForRemoval(GameObject* object);
	void removeMarkedObjects();

	void dispose();

private:
	static int objectId;

	ObjectManager(const ObjectManager& other);
	ObjectManager& operator=(const ObjectManager& other);

	void remove(int index);

	std::vector<GameObject*> objects;
	std::unordered_map<int, int> indexMap;
	std::set<int> removalList;

	int maxSize;
	int nextIndex;
};