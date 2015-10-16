#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <functional>

#include "../Helper/opengl_helper.h"

class Context
{
private:
	static GLfloat deltaTime;

	GLFWwindow* window;
	int width;
	int height;

	Context(Context& other);
	Context& operator=(Context& other);

	void destroyWindow();
	void setProperty(GLenum prop, bool enabled);

	GLboolean getGLBoolean(bool value);

public:
	static GLfloat getDeltaTime();

	Context();

	void initialize(int majorVersion, int minorVersion);
	void terminate();

	GLFWwindow* getWindow();
	void closeWindow();
	int getWindowWidth();
	int getWindowHeight();

	void loop(std::function<void(Context&)> loopCallback);

	void createWindow(int width, int height, int samples, std::string title, bool resizable, bool fullscreen);

	void setViewport(GLint x, GLint y, GLsizei width, GLsizei height);
	void setKeyCallback(void (*callback)(GLFWwindow* window, int key, int scancode, int action, int mode));
	void setMousePositionCallback(void (*callback)(GLFWwindow* window, double xpos, double ypos));
	void setMouseScrollCallback(void (*callback)(GLFWwindow* window, double xoffset, double yoffset));
	void setMouseButtonCallback(void(*callback)(GLFWwindow* window, int button, int action, int modifier));
	void setWindowSizeCallback(void(*callback)(GLFWwindow* window, int width, int height));
	void setCursor(bool enabled);

	void setDepthTest(bool enabled);
	void setStencilTest(bool enabled);

	void setDepthFunc(GLenum func);

	void setStencilFunc(GLenum func, GLint value, GLuint mask);
	void setStencilOp(GLenum stencilFail, GLenum depthFail, GLenum success);
	void setStencilMask(GLuint mask);

	void setColorMask(bool r, bool g, bool b, bool a);
	void setDepthMask(bool enabled);

	void setPolygonMode(GLenum face, GLenum mode);
	void setLineWidth(GLfloat width);

	void setBlending(bool enabled);
	void setBlendingFunc(GLenum sourceFactor, GLenum destinationFactor);

	void setCulling(bool enabled);
	void setCullingMode(GLenum mode);
	void setCullingFrontFace(GLenum mode);

	void setMultisampling(bool enabled);
	
	void setGammaCorrection(bool enabled);

	void setShowMouseCursor(bool enabled);
};