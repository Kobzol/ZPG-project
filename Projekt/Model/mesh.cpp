#include "mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
}

void Mesh::setup()
{
	this->vao.bind();

	this->vbo.bind();
	this->vbo.setData(&this->vertices[0], this->vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);
	
	this->ebo.bind();
	this->ebo.setData(&this->indices[0], this->indices.size() * sizeof(GLuint), GL_STATIC_DRAW);

	Program::setAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) 0);	// position
	Program::setAttribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, normal));	// normal
	Program::setAttribute(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, texCoords));	// tex coordinates
	Program::setAttribute(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, tangent));	// tangent

	this->vao.unbind();
}

std::unordered_map<TextureType, std::pair<int, std::string>> textureProperties =
{
	{ TextureType::Diffuse, { 1, "textureDiffuse" } },
	{ TextureType::Specular, { 2, "textureSpecular" } }
};

void Mesh::draw()
{
	GLuint diffuseNo = 1;
	GLuint specularNo = 1;

	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		std::pair<int, std::string> textureProperty = textureProperties[this->textures[i].type];

		ProgramManager::getInstance().getCurrentProgram().setUniform1i(textureProperty.second, textureProperty.first);
		this->textures[i].bind(textureProperty.first);
	}

	this->vao.bind();
	RenderUtils::drawElements(this->indices.size(), GL_UNSIGNED_INT, 0);
	this->vao.unbind();
}
void Mesh::dispose()
{
	this->vao.dispose();
	this->vbo.dispose();
	this->ebo.dispose();
}