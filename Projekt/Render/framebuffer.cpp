#include "Framebuffer.h"

Framebuffer::Framebuffer()
{
	glGenFramebuffers(1, &this->framebuffer);
	GL_CHECK_ERRORS();
}

GLuint Framebuffer::getId()
{
	return this->framebuffer;
}

void Framebuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
	GL_CHECK_ERRORS();
}

void Framebuffer::createAttachments(int width, int height)
{
	this->bind();

	this->primaryAttachment = Texture(TextureType::Diffuse);
	this->primaryAttachment.allocate();
	this->primaryAttachment.bind();
	this->primaryAttachment.set2DImage(Image(width, height, ImageType::Alpha));
	this->primaryAttachment.setTextureFiltering(true, GL_LINEAR);
	this->primaryAttachment.setTextureFiltering(false, GL_LINEAR);
	this->primaryAttachment.setTextureClamping(GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->primaryAttachment.getId(), 0);
	GL_CHECK_ERRORS();

	this->secondaryAttachment.bind();
	this->secondaryAttachment.setStorage(GL_DEPTH24_STENCIL8, width, height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->secondaryAttachment.getId());
	GL_CHECK_ERRORS();
}
void Framebuffer::createShadowMap(int width, int height)
{
	this->bind();

	this->primaryAttachment = Texture(TextureType::Diffuse);
	this->primaryAttachment.allocate();
	this->primaryAttachment.bind();
	this->primaryAttachment.setDepthComponent(width, height);
	this->primaryAttachment.setTextureFiltering(true, GL_NEAREST);
	this->primaryAttachment.setTextureFiltering(false, GL_NEAREST);
	this->primaryAttachment.setTextureClamping(GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	this->primaryAttachment.setTextureBorderColor(borderColor);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->primaryAttachment.getId(), 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	GL_CHECK_ERRORS();
}
void Framebuffer::createOmniShadowMap(int width, int height)
{
	this->bind();

	this->cubemapAttachment.allocate();
	this->cubemapAttachment.bind();
	this->cubemapAttachment.generateDepthMap(width, height);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->cubemapAttachment.getId(), 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GL_CHECK_ERRORS();
}

bool Framebuffer::isComplete()
{
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	GL_CHECK_ERRORS();

	return status == GL_FRAMEBUFFER_COMPLETE;
}

void Framebuffer::dispose()
{
	glDeleteFramebuffers(1, &this->framebuffer);
	GL_CHECK_ERRORS();

	this->primaryAttachment.dispose();
	this->secondaryAttachment.dispose();
	this->cubemapAttachment.dispose();
}