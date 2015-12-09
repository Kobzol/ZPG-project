#pragma once

#include "irender_module.h"

class DecoratorModule : public IRenderModule
{
public:
	DecoratorModule(IRenderModule* decorator, IRenderModule* inner);

	virtual void startDraw(RenderComponent* renderComponent) override;
	virtual void endDraw(RenderComponent* renderComponent) override;
	virtual void dispose() override;

private:
	IRenderModule* decorator;
	IRenderModule* inner;
};