#pragma once

#include <glm/glm.hpp>

#include "../../Model/texture.h"

struct Character
{
public:
	Texture texture;		// ID handle of the glyph texture
	glm::ivec2 size;		// Size of glyph
	glm::ivec2 bearing;		// Offset from baseline to left/top of glyph
	GLuint advance;			// Offset to advance to next glyph
};