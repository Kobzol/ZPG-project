#pragma once

#include <functional>

#include "icomponent.h"

template <typename T>
class FunctionComponent : public IComponent
{
public:
	FunctionComponent(const std::function<T>& fn) : fn(fn)
	{

	}

	void update() override
	{
		this->fn();
	}
private:
	std::function<T> fn;
};