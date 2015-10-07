#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <memory>

#include "shader.h"
#include "../Buffer/vao.h"
#include "../Helper/helper.h"
#include "../Event/camera_changed_listener.h"
#include "camera.h"

class Program : public CameraChangedListener
{
private:
	GLuint program;

	Program(const Program& other);
	Program& operator=(Program& other);

public:
	static void setAttribute(GLint position, GLint count, GLenum type, GLboolean normalize, GLsizei stride, const void* offset);

	Program(std::string outputName);
	~Program();

	void attachShader(Shader& shader);
	void link();
	void use();

	GLint getAttributeLocation(std::string name);
	void setAttribute(std::string name, GLint count, GLenum type, GLboolean normalize, GLsizei stride, const void* offset);

	GLint getUniformLocation(std::string name);
	void setUniform3f(std::string name, GLfloat x, GLfloat y, GLfloat z);
	void setUniform3f(std::string name, glm::vec3 value);
	void setUniform2f(std::string name, glm::vec2 value);
	void setUniform1f(std::string name, GLfloat value);
	void setUniform1i(std::string name, GLint value);
	void setUniformMatrix4fv(std::string name, const glm::mat4& matrix);

	VAO* getVAO();

	void notifyCameraChanged(Camera& camera);
	void setCameraMatrices(Camera& camera);
};