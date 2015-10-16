#pragma once

#include <bitset>

template <class T>
class Flags
{
public:
	std::bitset<sizeof(int)> value;

	Flags()
	{
		
	}
	Flags(T enumValue)
	{
		this->set(enumValue);
	}

	void set(T enumValue)
	{
		this->value.set((int) enumValue);
	}
	void set(std::initializer_list<T> enumValues)
	{
		for (T t : enumValues)
		{
			this->set(t);
		}
	}
	void unset(T enumValue)
	{
		this->value.reset((int) enumValue);
	}
	void unset(std::initializer_list<T> enumValues)
	{
		for (T t : enumValues)
		{
			this->unset(t);
		}
	}
	bool isSet(T enumValue)
	{
		return this->value.test((int) enumValue);
	}
	bool isSet(std::initializer_list<T> enumValues)
	{
		for (T t : enumValues)
		{
			if (!this->isSet(t))
			{
				return false;
			}
		}

		return true;
	}
	void reset()
	{
		this->value.reset();
	}
};