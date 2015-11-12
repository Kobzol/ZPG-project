#include "framebuffer_manager.h"

const std::string FramebufferManager::FRAMEBUFFER_POSTPROCESS = "postprocess";
const std::string FramebufferManager::FRAMEBUFFER_DEPTH = "depth";

FramebufferManager FramebufferManager::instance = FramebufferManager();

FramebufferManager& FramebufferManager::getInstance()
{
	return FramebufferManager::instance;
}

FramebufferManager::FramebufferManager()
{

}

void FramebufferManager::preloadFramebuffers()
{
	Framebuffer fb;
	fb.bind();
	fb.createAttachments(800, 600);	// TODO pass size
	
	if (!fb.isComplete())
	{
		throw std::runtime_error("Couldn't create postprocess framebuffer");
	}

	this->load(FramebufferManager::FRAMEBUFFER_POSTPROCESS, fb);

	Framebuffer depthFb;
	depthFb.bind();
	depthFb.createShadowMap(1024, 1024);

	if (!depthFb.isComplete())
	{
		throw std::runtime_error("Couldn't create depth framebuffer");
	}

	this->load(FramebufferManager::FRAMEBUFFER_DEPTH, depthFb);

	this->bindDefault();
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