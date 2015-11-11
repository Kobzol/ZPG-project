#pragma once

class RenderComponent;

class IRenderModule
{
public:
	virtual void update(RenderComponent* component) = 0;
	virtual void dispose() { };
};