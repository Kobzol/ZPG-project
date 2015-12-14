#pragma once

#include "content_manager.h"
#include "../Render/framebuffer.h"

class FramebufferManager : public ContentManager<Framebuffer>
{
public:
	static const std::string FRAMEBUFFER_POSTPROCESS;
	static const std::string FRAMEBUFFER_DEPTH;

	static FramebufferManager& getInstance();

	void preloadFramebuffers(int width, int height);

	void bindDefault();

	void dispose();

private:
	static FramebufferManager instance;

	FramebufferManager();
};