#pragma once

#include <bitset>

template <class T>
class Flags
{
public:
	std::bitset<32> value;

	Flags(T enumValue)
	{
		this->set(enumValue);
	}

	void set(T enumValue)
	{
		this->value.set((int) enumValue);
	}
	void unset(T enumValue)
	{
		this->value.reset((int) enumValue);
	}
	bool isSet(T enumValue)
	{
		return this->value.test((int) enumValue);
	}
	void reset()
	{
		this->value.reset();
	}
};