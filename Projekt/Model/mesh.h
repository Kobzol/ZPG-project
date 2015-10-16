//#pragma once
//
//#define GLEW_STATIC
//#include <GL/glew.h>
//
//#include <string>
//#include <vector>
//
//#include "../Buffer/ebo.h"
//#include "../Render/program.h"
//#include "../Render/renderer.h"
//#include "../Buffer/vao.h"
//#include "../Buffer/vbo.h"
//#include "texture.h"
//#include "vertex.h"
//
//class Mesh
//{
//public:
//	std::vector<Vertex> vertices;
//	std::vector<GLuint> indices;
//	std::vector<Texture> textures;
//
//	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
//
//	void setup();
//
//	void draw(Program& program, Renderer& renderer);
//	void dispose();
//
//private:
//	VAO vao;
//	VBO vbo;
//	EBO ebo;
//};