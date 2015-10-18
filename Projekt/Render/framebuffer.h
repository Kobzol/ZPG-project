#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <memory>

#include "../Model/cubemap.h"
#include "../Model/texture.h"
#include "renderbuffer.h"
#include "../Helper/opengl_helper.h"

class Framebuffer
{
private:
	GLuint framebuffer;

public:
	Texture primaryAttachment;
	Renderbuffer secondaryAttachment;
	Cubemap cubemapAttachment;

	Framebuffer();

	GLuint getId();

	void bind();
	void createAttachments(int width, int height);
	void createShadowMap(int width, int height);
	void createOmniShadowMap(int width, int height);

	bool isComplete();

	void dispose();
};