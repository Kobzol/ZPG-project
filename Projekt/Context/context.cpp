#include "context.h"

GLfloat Context::deltaTime = 0.0;

GLfloat Context::getDeltaTime()
{
	return Context::deltaTime;
}

Context::Context()
{
	this->window = nullptr;
}

void Context::destroyWindow()
{
	glfwDestroyWindow(this->window);
	this->window = nullptr;
}
void Context::setProperty(GLenum prop, bool enabled)
{
	if (enabled)
	{
		glEnable(prop);
	}
	else glDisable(prop);

	GL_CHECK_ERRORS();
}

GLboolean Context::getGLBoolean(bool value)
{
	return value ? GL_TRUE : GL_FALSE;
}

void Context::initialize()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	OpenGLHelper::glClearError();
}
void Context::terminate()
{
	this->destroyWindow();
	glfwTerminate();
}

GLFWwindow* Context::getWindow()
{
	return this->window;
}
void Context::closeWindow()
{
	glfwSetWindowShouldClose(this->window, 1);
}
int Context::getWindowWidth()
{
	return this->width;
}
int Context::getWindowHeight()
{
	return this->height;
}

void Context::createWindow(int width, int height, int samples, std::string title, bool resizable, bool fullscreen)
{
	if (this->window != nullptr)
	{
		this->destroyWindow();
	}

	glfwWindowHint(GLFW_RESIZABLE, (GLboolean) resizable);
	glfwWindowHint(GLFW_SAMPLES, samples);

	GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;
	this->window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
	this->width = width;
	this->height = height;

	glfwMakeContextCurrent(this->window);
	this->setViewport(0, 0, width, height);

	glewExperimental = true;
	glewInit();

	OpenGLHelper::glClearError();
}

void Context::setViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport(x, y, width, height);
	GL_CHECK_ERRORS();
}
void Context::setKeyCallback(void (*callback)(GLFWwindow* window, int key, int scancode, int action, int mode))
{
	glfwSetKeyCallback(this->window, callback);
}
void Context::setMousePositionCallback(void (*callback)(GLFWwindow* window, double xpos, double ypos))
{
	glfwSetCursorPosCallback(this->window, callback);
}
void Context::setMouseScrollCallback(void (*callback)(GLFWwindow* window, double xoffset, double yoffset))
{
	glfwSetScrollCallback(this->window, callback);
}
void Context::setMouseButtonCallback(void(*callback)(GLFWwindow* window, int button, int action, int modifier))
{
	glfwSetMouseButtonCallback(this->window, callback);
}
void Context::setWindowSizeCallback(void(*callback)(GLFWwindow* window, int width, int height))
{
	glfwSetWindowSizeCallback(this->window, callback);
}
void Context::setCursor(bool enabled)
{
	glfwSetInputMode(this->window, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void Context::loop(std::function<void(Context&)> loopCallback)
{
	GLfloat lastFrame = (GLfloat) glfwGetTime();
	while (!glfwWindowShouldClose(this->window))
	{
		GLfloat currentFrame = (GLfloat) glfwGetTime();
		Context::deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();

		loopCallback(*this);

		glfwSwapBuffers(this->window);
	}
}

void Context::setDepthTest(bool enabled)
{
	this->setProperty(GL_DEPTH_TEST, enabled);
}
void Context::setStencilTest(bool enabled)
{
	this->setProperty(GL_STENCIL_TEST, enabled);
}

void Context::setDepthFunc(GLenum func)
{
	glDepthFunc(func);
	GL_CHECK_ERRORS();
}

void Context::setStencilFunc(GLenum func, GLint value, GLuint mask)
{
	glStencilFunc(func, value, mask);
	GL_CHECK_ERRORS();
}
void Context::setStencilOp(GLenum stencilFail, GLenum depthFail, GLenum success)
{
	glStencilOp(stencilFail, depthFail, success);
	GL_CHECK_ERRORS();
}
void Context::setStencilMask(GLuint mask)
{
	glStencilMask(mask);
	GL_CHECK_ERRORS();
}

void Context::setColorMask(bool r, bool g, bool b, bool a)
{
	glColorMask(this->getGLBoolean(r), this->getGLBoolean(g), this->getGLBoolean(b), this->getGLBoolean(a));
	GL_CHECK_ERRORS();
}
void Context::setDepthMask(bool value)
{
	glDepthMask(this->getGLBoolean(value));
	GL_CHECK_ERRORS();
}

void Context::setPolygonMode(GLenum face, GLenum mode)
{
	glPolygonMode(face, mode);
	GL_CHECK_ERRORS();
}
void Context::setLineWidth(GLfloat width)
{
	glLineWidth(width);
	GL_CHECK_ERRORS();
}

void Context::setBlending(bool enabled)
{
	this->setProperty(GL_BLEND, enabled);
}
void Context::setBlendingFunc(GLenum sourceFactor, GLenum destinationFactor)
{
	glBlendFunc(sourceFactor, destinationFactor);
	GL_CHECK_ERRORS();
}

void Context::setCulling(bool enabled)
{
	this->setProperty(GL_CULL_FACE, enabled);
}
void Context::setCullingMode(GLenum mode)
{
	glCullFace(mode);
	GL_CHECK_ERRORS();
}
void Context::setCullingFrontFace(GLenum mode)
{
	glFrontFace(mode);
	GL_CHECK_ERRORS();
}

void Context::setMultisampling(bool enabled)
{
	this->setProperty(GL_MULTISAMPLE, enabled);
}

void Context::setGammaCorrection(bool enabled)
{
	this->setProperty(GL_FRAMEBUFFER_SRGB, enabled);
}

void Context::setShowMouseCursor(bool enabled)
{
	glfwSetInputMode(window, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}