#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <cassert>
#include <iostream>
#include <map>
#include <string>

#include "character.h"
#include "../program.h"
#include "../render_utils.h"
#include "../../Buffer/vao.h"
#include "../../Buffer/vbo.h"
#include "../../Content/program_manager.h"

class FontManager
{
public:
	static FontManager& getInstance();

	void initialize(int width, int height);
	void dispose();

	void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

	void setPerspective(int width, int height);

private:
	static const std::string FONT_PATH;

	static FontManager instance;

	FontManager();

	VAO* vao;
	VBO* vbo;

	glm::mat4 projection;
	std::map<GLchar, Character> characters;
};