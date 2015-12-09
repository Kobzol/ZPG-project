#include "geometry_draw_module.h"

GeometryDrawModule::GeometryDrawModule(GeometryObject geometry) : geometry(geometry)
{

}

void GeometryDrawModule::startDraw(RenderComponent* component)
{
	this->geometry.getVAO().bind();
	RenderUtils::drawTriangles(0, this->geometry.getVertexCount());
	this->geometry.getVAO().unbind();
}
void GeometryDrawModule::dispose()
{
	this->geometry.dispose();
}
