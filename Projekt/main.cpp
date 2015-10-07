#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Context/context.h"
#include "Render/shader.h"
#include "Render/program.h"
#include "Render/camera.h"
#include "Buffer/ebo.h"
#include "Buffer/vbo.h"
#include "Buffer/vao.h"
#include "Helper/fileio.h"
#include "Model/model.h"

Camera camera(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 4.0f / 3.0f, 0.1f, 10.0f);

double xpos_old = -1;
double ypos_old = -1;

static GLfloat pitch = 0.0f;
static GLfloat yaw = -90.0f;
static GLfloat mouseSensitivity = 0.05f;

static float angleHorizontal = 270.0f;
static float angleVertical = 0.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GL_TRUE)
	{
		camera.setPosition(camera.getPosition() + -camera.getLeft() * 0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GL_TRUE)
	{
		camera.setPosition(camera.getPosition() + camera.getLeft() * 0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GL_TRUE)
	{
		camera.setPosition(camera.getPosition() + camera.getFront() * 0.1f);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GL_TRUE)
	{
		camera.setPosition(camera.getPosition() + -camera.getFront() * 0.1f);
	}
}
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos)
{
	double diff_x = x_pos - xpos_old;
	double diff_y = ypos_old - y_pos;

	if (xpos_old == -1)
	{
		xpos_old = x_pos;
		ypos_old = y_pos;

		return;
	}

	xpos_old = x_pos;
	ypos_old = y_pos;

	diff_x *= mouseSensitivity;
	diff_y *= mouseSensitivity;

	yaw += (GLfloat) diff_x;
	pitch += (GLfloat) diff_y;

	pitch = glm::clamp(pitch, -89.0f, 89.0f);

	GLfloat cosPitch = cos(glm::radians(pitch));
	GLfloat sinPitch = sin(glm::radians(pitch));
	GLfloat cosYaw = cos(glm::radians(yaw));
	GLfloat sinYaw = sin(glm::radians(yaw));
	glm::vec3 cameraFront = glm::vec3(cosPitch * cosYaw, sinPitch, cosPitch * sinYaw);

	camera.setTarget(cameraFront);
}

float pointsA[] = {
	0.0f, 0.0f, 0.0f,	// upper center
	0.5f, -0.5f, 0.0f,	// lower right
	-0.5f, -0.5f, 0.0f,	// lower left
};

glm::vec4 pointUp = glm::vec4(0.0f, 0.5f, 0.0f, 0.0f);
glm::vec4 pointLeft = glm::vec4(-0.5f, -0.5f, 0.0f, 0.0f);
glm::vec4 pointRight = glm::vec4(0.5f, -0.5f, 0.0f, 0.0f);

int indices[] = { 0, 1, 2, 2, 3, 0 };

namespace glm { 
	glm::mat4 rotate_around(const glm::mat4 &origin, float angle, const glm::vec3 axis, const glm::vec3 &point)
	{
		glm::mat4 move_to_point = glm::translate(origin, point);
		glm::mat4 rotate = glm::rotate(move_to_point, angle, axis);
		glm::mat4 move_back = glm::translate(rotate, -point);

		return move_back;
	}
}

int main()
{
	Context context;
	context.initialize();
	context.createWindow(800, 600, 1, "ZPG", false, false);
	context.setKeyCallback(key_callback);
	context.setMousePositionCallback(mouse_callback);

	Shader vertShader(io_load_file("Shaders/Vertex/test.vert"), GL_VERTEX_SHADER);
	Shader fragShader(io_load_file("Shaders/Fragment/test.frag"), GL_FRAGMENT_SHADER);
	
	Program program("outColor");
	program.attachShader(vertShader);
	program.attachShader(fragShader);
	program.link();
	program.use();

	VAO vaoA;
	vaoA.bind();

	VBO vboA;
	vboA.bind();
	vboA.setData(pointsA, sizeof(pointsA), GL_STATIC_DRAW);

	EBO ebo;
	ebo.bind();
	ebo.setData(indices, sizeof(indices), GL_STATIC_DRAW);

	float angle = 90.0f;
	glm::mat4 model;

	program.setAttribute("position", 3, GL_FLOAT, GL_FALSE, 0, 0);

	camera.addListener(&program);
	program.setCameraMatrices(camera);

	context.loop([&] (Context& context)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.use();
		
		vaoA.bind();
		ebo.bind();
		
		program.setUniformMatrix4fv("Model", model);
		program.setUniform3f("color", glm::vec3(1.0f, 0.0f, 0.0f));

		glDrawArrays(GL_TRIANGLES, 0, 3);
	});

	context.terminate();

	return 0;
}