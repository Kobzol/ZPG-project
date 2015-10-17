#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
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

	this->vao.unbind();
}

void Mesh::draw()
{
	GLuint diffuseNo = 1;
	GLuint specularNo = 1;

	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		bool diffuse = this->textures[i].type == TextureType::Diffuse;
		std::string name = "texture_";
		name += (diffuse ? "diffuse" : "specular");

		GLuint index = specularNo;
		if (diffuse)
		{
			index = diffuseNo;
			diffuseNo++;
		}
		else specularNo++;

		name += std::to_string(index);

		ProgramManager::getInstance().getCurrentProgram().setUniform1i(name, i);
		this->textures[i].bind(i);
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