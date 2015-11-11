#include "font_manager.h"

const std::string FontManager::FONT_PATH = "Resources/Font/";

FontManager FontManager::instance = FontManager();

FontManager& FontManager::getInstance()
{
	return FontManager::instance;
}

FontManager::FontManager()
{

}

void FontManager::initialize(int width, int height)
{
	this->setPerspective(width, height);

	FT_Library ft;
	assert(!FT_Init_FreeType(&ft));

	FT_Face face;
	assert(!FT_New_Face(ft, (FontManager::FONT_PATH + "arial.ttf").c_str(), 0, &face));

	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cerr << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

		Character character;
		character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
		character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
		character.advance = face->glyph->advance.x;

		character.texture.allocate();
		character.texture.bind();

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		
		character.texture.setTextureClamping(GL_CLAMP_TO_EDGE);
		character.texture.setTextureFiltering(true, GL_LINEAR);
		character.texture.setTextureFiltering(false, GL_LINEAR);

		this->characters.insert(std::pair<GLchar, Character>(c, character));
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	this->vao = new VAO();
	this->vbo = new VBO();

	this->vao->bind();
	this->vbo->bind();
	
	this->vbo->setData(nullptr, sizeof(GLfloat) * 6 * 4, GL_DYNAMIC_DRAW);
	Program::setAttribute(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*) 0);
	
	this->vao->unbind();
	this->vbo->unbind();
}
void FontManager::dispose()
{
	this->vao->dispose();
	this->vbo->dispose();

	delete this->vao;
	delete this->vbo;
}

void FontManager::renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	ProgramManager::getInstance().save();
	ProgramManager::getInstance().use(ProgramManager::PROGRAM_FONT);
	Program& program = ProgramManager::getInstance().getCurrentProgram();

	program.setProjectionMatrix(this->projection);
	program.setUniform3f("color", color);

	this->vao->bind();

	for (auto c = text.begin(); c != text.end(); c++)
	{
		Character ch = this->characters[*c];

		GLfloat xpos = x + ch.bearing.x * scale;
		GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;

		GLfloat vertices[6][4] = {
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos, ypos, 0.0, 1.0 },
			{ xpos + w, ypos, 1.0, 1.0 },

			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 0.0 }
		};

		ch.texture.bind(0);

		this->vbo->bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		this->vbo->unbind();

		RenderUtils::drawTriangles(0, 6);

		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * scale;
	}

	this->vao->unbind();

	ProgramManager::getInstance().restore();
}

void FontManager::setPerspective(int width, int height)
{
	this->projection = glm::ortho(0.0f, (float) width, 0.0f, (float) height);
}