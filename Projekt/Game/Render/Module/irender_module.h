#pragma once

class RenderComponent;

class IRenderModule
{
public:
	virtual void startDraw(RenderComponent* component) = 0;
	virtual void endDraw(RenderComponent* component) { };
	virtual void draw(RenderComponent* component)
	{
		this->startDraw(component);
		this->endDraw(component);
	}
	virtual void dispose() { };
};