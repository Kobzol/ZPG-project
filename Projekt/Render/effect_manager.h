#pragma once

#include "../Context/context.h"

class EffectManager
{
public:
	static EffectManager& getInstance();

	void beforeRender(Context& context);
	void beforeOutline(Context& context);
	void afterOutline(Context& context);

private:
	static EffectManager instance;
};