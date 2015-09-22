#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Context/context.h"
#include "Render/shader.h"
#include "Render/program.h"
#include "Buffer/ebo.h"
#include "Buffer/vbo.h"
#include "Buffer/vao.h"
#include "Helper/fileio.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

float pointsA[] = {
	0.0f, 0.0f, 0.0f,	// upper left
	0.5f, 0.5f, 0.0f,	// upper right
	0.5f, -0.5f, 0.0f	// lower right
};

float pointsB[] = {
	-0.5f, 0.5f, 0.0f,	// upper left
	0.5f, 0.5f, 0.0f,	// upper right
	-0.5f, -0.5f, 0.0f,	// lower left
	0.5f, -0.5f, 0.0f,	// lower right
	-0.5f, -0.5f, 0.0f,	// lower left
	0.5f, 0.5f, 0.0f	// upper right
};

int main()
{
	Context context;
	context.initialize();
	context.createWindow(800, 600, 1, "ZPG", false, false);
	context.setKeyCallback(key_callback);

	Shader vertShader(io_load_file("Shaders/Vertex/test.vert"), GL_VERTEX_SHADER);
	Shader fragShader(io_load_file("Shaders/Fragment/test.frag"), GL_FRAGMENT_SHADER);
	
	Program program("outColor");
	program.attachShader(vertShader);
	program.attachShader(fragShader);
	program.link();

	VAO vaoA;
	vaoA.bind();

	VBO vboA;
	vboA.bind();
	vboA.setData(pointsA, sizeof(pointsA), GL_STATIC_DRAW);

	program.setAttribute("position", 3, GL_FLOAT, GL_FALSE, 0, 0);

	VAO vaoB;
	vaoB.bind();

	VBO vboB;
	vboB.bind();
	vboB.setData(pointsB, sizeof(pointsB), GL_STATIC_DRAW);

	program.setAttribute("position", 3, GL_FLOAT, GL_FALSE, 0, 0);

	context.loop([&] (Context& context)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.use();
		
		vaoB.bind();
		program.setUniform3f("color", glm::vec3(0.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		vaoA.bind();
		program.setUniform3f("color", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 3);
	});

	context.terminate();

	return 0;
}