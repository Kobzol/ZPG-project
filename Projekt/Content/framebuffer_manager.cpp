#include "framebuffer_manager.h"

FramebufferManager FramebufferManager::instance = FramebufferManager();

FramebufferManager& FramebufferManager::getInstance()
{
	return FramebufferManager::instance;
}

FramebufferManager::FramebufferManager()
{

}

void FramebufferManager::bindDefault()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	GL_CHECK_ERRORS();
}

void FramebufferManager::dispose()
{
	for (auto& framebuffer : this->items)
	{
		framebuffer.second.dispose();
	}
}