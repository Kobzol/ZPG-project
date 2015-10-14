#include "effect_manager.h"

EffectManager EffectManager::instance = EffectManager();

EffectManager& EffectManager::getInstance()
{
	return EffectManager::instance;
}

void EffectManager::beforeRender(Context& context)
{
	context.setStencilFunc(GL_ALWAYS, 1, 0xFF);	// passes stencil test always
	context.setStencilMask(0xFF);	// enable writing to stencil buffer
}
void EffectManager::beforeOutline(Context& context)
{
	context.setStencilFunc(GL_NOTEQUAL, 1, 0xFF);	// passes stencil test if value is not equal to 1
	context.setStencilMask(0x00);	// disable writing to stencil buffer
	context.setDepthTest(false);
}
void EffectManager::afterOutline(Context& context)
{
	context.setDepthTest(true);
	context.setStencilMask(0xFF);
}