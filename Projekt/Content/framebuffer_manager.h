#pragma once

#include "content_manager.h"
#include "../Render/framebuffer.h"

class FramebufferManager : public ContentManager<Framebuffer>
{
public:
	static FramebufferManager& getInstance();

	void bindDefault();

	void dispose();

private:
	static FramebufferManager instance;

	FramebufferManager();
};