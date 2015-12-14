#pragma once

#include "irender_module.h"

class OutlineModule : public IRenderModule
{
public:
	OutlineModule(IRenderModule* module);

	virtual void startDraw(RenderComponent* component) override;

private:
	IRenderModule* module;
};