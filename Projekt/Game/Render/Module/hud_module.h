#pragma once

#include "irender_module.h"
#include "../../game.h"

class HUDModule : public IRenderModule
{
public:
	virtual void startDraw(RenderComponent* component);
	virtual void endDraw(RenderComponent* component);
};