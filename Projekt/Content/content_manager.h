#pragma once

#include <unordered_map>

template <typename T>
class ContentManager
{
public:
	void load(std::string identifier, const T &item)
	{
		this->items.emplace(identifier, item);
	}

	bool hasKey(std::string identifier)
	{
		return this->items.count(identifier) > 0;
	}

	T& get(std::string identifier)
	{
		if (this->items.count(identifier))
		{
			return this->items[identifier];
		}
		else throw std::runtime_error("No item with identifier " + identifier + " has been found.");
	}

protected:
	std::unordered_map<std::string, T> items;
};