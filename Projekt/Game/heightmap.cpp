#include "heightmap.h"

HeightMap::HeightMap(size_t size, float granularity, float textureScale)
{
	GLfloat heightVertices[6][2] = {
		{ 0.0f, 0.0f },
		{ 0.0f, -1.0f },
		{ 1.0f, -1.0f },
		{ 1.0f, -1.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 0.0f }
	};

	std::vector<VertexHeightMap> vertices;
	vertices.reserve(6 * size * size);

	std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
	std::default_random_engine engine((unsigned int)time(nullptr));

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			for (size_t v = 0; v < 6; v++)
			{
				float offsetX = i + heightVertices[v][0];
				float offsetZ = j + heightVertices[v][1];

				VertexHeightMap vertex;
				vertex.texCoords = glm::vec2(offsetZ / (float)(size / textureScale), offsetX / (float)(size / textureScale));
				vertex.position = glm::vec3((i * granularity + heightVertices[v][0] * granularity), 0, (j * granularity + heightVertices[v][1] * granularity));

				vertex.position.y = glm::simplex(glm::vec2(vertex.position.x, vertex.position.z));

				vertices.push_back(vertex);
			}
		}
	}

	this->geometryObject = std::make_unique<GeometryObject>(&vertices[0], sizeof(VertexHeightMap), 6 * size * size);
	this->geometryObject.get()->setAttributePositionTexture3D();
}

GameObject* HeightMap::createObject()
{
	return new GameObject(nullptr, new RenderComponent(glm::vec3(1.0f), ProgramManager::PROGRAM_HEIGHTMAP, new GeometryDrawModule(*this->geometryObject.get())));
}