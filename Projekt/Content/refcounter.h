#pragma once

#include <unordered_map>

template <typename T>
class RefCounter
{
public:
	RefCounter(T* object) : object(object)
	{
		this->incrementAddress(object);
	}
	RefCounter(const RefCounter& other)
	{
		this->object = other.object;
		this->incrementAddress(other.object);
	}
	RefCounter& operator=(RefCounter other)
	{
		this->object = other.object;
		this->incrementAddress(other.object);
		return *this;
	}
	~RefCounter()
	{
		this->free();
	}

	T* get()
	{
		return this->object;
	}
	void free()
	{
		RefCounter<T>::references[this->object]--;

		if (RefCounter<T>::references[this->object] == 0)
		{
			delete this->object;
		}
	}

private:
	static std::unordered_map<void*, int> references;

	void incrementAddress(T* address)
	{
		if (address != nullptr)
		{
			if (RefCounter<T>::references.count(object))
			{
				RefCounter<T>::references[object]++;
			}
			else RefCounter<T>::references.emplace(object, 1);
		}
	}

	T* object;
};

template <typename T>
std::unordered_map<void*, int> RefCounter<T>::references = std::unordered_map<void*, int>();