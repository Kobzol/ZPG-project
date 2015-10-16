#include "Framebuffer.h"

void Framebuffer::bindDefault()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	GL_CHECK_ERRORS();
}

Framebuffer::Framebuffer()
{
	glGenFramebuffers(1, &this->framebuffer);
	GL_CHECK_ERRORS();
}
Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &this->framebuffer);
	GL_CHECK_ERRORS();

	if (this->primaryAttachment.get() != nullptr)
	{
		this->primaryAttachment.get()->dispose();
	}
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

	this->primaryAttachment = std::unique_ptr<Texture>(new Texture(TextureType::Diffuse));
	this->primaryAttachment.get()->allocate();
	this->primaryAttachment.get()->bind();
	this->primaryAttachment.get()->set2DImage(Image(width, height, ImageType::Alpha));
	this->primaryAttachment.get()->setTextureFiltering(true, GL_LINEAR);
	this->primaryAttachment.get()->setTextureFiltering(false, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->primaryAttachment.get()->getId(), 0);
	GL_CHECK_ERRORS();

	this->secondaryAttachment = std::unique_ptr<Renderbuffer>(new Renderbuffer());
	this->secondaryAttachment.get()->bind();
	this->secondaryAttachment.get()->setStorage(GL_DEPTH24_STENCIL8, width, height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->secondaryAttachment.get()->getId());
	GL_CHECK_ERRORS();
}
void Framebuffer::createShadowMap(int width, int height)
{
	this->bind();

	this->primaryAttachment = std::unique_ptr<Texture>(new Texture(TextureType::Diffuse));
	this->primaryAttachment.get()->allocate();
	this->primaryAttachment.get()->bind();
	this->primaryAttachment.get()->setDepthComponent(width, height);
	this->primaryAttachment.get()->setTextureFiltering(true, GL_NEAREST);
	this->primaryAttachment.get()->setTextureFiltering(false, GL_NEAREST);
	this->primaryAttachment.get()->setTextureClamping(GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	this->primaryAttachment.get()->setTextureBorderColor(borderColor);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->primaryAttachment.get()->getId(), 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	GL_CHECK_ERRORS();
}
void Framebuffer::createOmniShadowMap(int width, int height)
{
	this->bind();

	this->cubemapAttachment = std::unique_ptr<Cubemap>(new Cubemap());
	this->cubemapAttachment.get()->allocate();
	this->cubemapAttachment.get()->bind();
	this->cubemapAttachment.get()->generateDepthMap(width, height);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->cubemapAttachment.get()->getId(), 0);
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