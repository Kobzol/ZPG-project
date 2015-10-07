#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <functional>

#include "../Helper/helper.h"

class Context
{
private:
	GLFWwindow* window;
	int width;
	int height;

	Context(Context& other);
	Context& operator=(Context& other);

	void destroyWindow();
	void setProperty(GLenum prop, bool enabled);

	GLboolean getGLBoolean(bool value);

public:
	static GLfloat deltaTime;

	Context();
	~Context();

	void initialize();
	void terminate();

	GLFWwindow* getWindow();
	int getWindowWidth();
	int getWindowHeight();

	void loop(std::function<void(Context&)> loop_callback);

	void createWindow(int width, int height, int samples, std::string title, bool resizable, bool fullscreen);

	void setViewport(GLint x, GLint y, GLsizei width, GLsizei height);
	void setKeyCallback(void (*callback)(GLFWwindow* window, int key, int scancode, int action, int mode));
	void setMousePositionCallback(void (*callback)(GLFWwindow* window, double xpos, double ypos));
	void setMouseScrollCallback(void (*callback)(GLFWwindow* window, double xoffset, double yoffset));
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
};