#include "decorator_module.h"

DecoratorModule::DecoratorModule(IRenderModule* decorator, IRenderModule* inner) : decorator(decorator), inner(inner)
{

}

void DecoratorModule::startDraw(RenderComponent* component)
{
	this->decorator->startDraw(component);
	this->inner->draw(component);
}
void DecoratorModule::endDraw(RenderComponent* component)
{
	this->decorator->endDraw(component);
}
void DecoratorModule::dispose()
{
	this->decorator->dispose();
	delete this->decorator;

	this->inner->dispose();
	delete this->inner;
}