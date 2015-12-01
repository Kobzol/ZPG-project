#include "model.h"

Model::Model(std::string path)
{
	this->loadModel(path);
}

void Model::draw()
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i].draw();
	}
}
void Model::dispose()
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
	{
		this->meshes[i].dispose();
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path,
		aiProcess_Triangulate |
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace |
		aiProcess_OptimizeMeshes |
		aiProcess_OptimizeGraph
		);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		throw std::runtime_error("Failed loading scene from model " + path + ": " + std::string(importer.GetErrorString()));
	}
	this->directory = path.substr(0, path.find_last_of("/"));

	this->processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->addMesh(mesh, scene);
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

void Model::addMesh(aiMesh* mesh, const aiScene* scene)
{
	this->meshes.emplace_back(std::vector<Vertex>(), std::vector<GLuint>(), std::vector<Texture>());
	Mesh& createdMesh = this->meshes[this->meshes.size() - 1];

	createdMesh.vertices.reserve(mesh->mNumVertices);

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

		if (mesh->HasNormals())
		{
			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		}
		else vertex.normal = glm::vec3(0.0f);

		if (mesh->HasTextureCoords(0))
		{
			vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else vertex.texCoords = glm::vec2(0.0f);

		if (mesh->HasTangentsAndBitangents())
		{
			vertex.tangent = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
		}
		else vertex.tangent = glm::vec3(0.0f);

		createdMesh.vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			createdMesh.indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		
		this->loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse, createdMesh.textures);
		this->loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular, createdMesh.textures);
	}

	this->meshes[this->meshes.size() - 1].setup();
}

void Model::loadMaterialTextures(aiMaterial* material, aiTextureType assimpType, TextureType textureType, std::vector<Texture>& textures)
{
	size_t textureCount = material->GetTextureCount(assimpType);

	for (GLuint i = 0; i < textureCount; i++)
	{
		aiString str;
		material->GetTexture(assimpType, i, &str);
		
		std::string convStr = std::string(str.C_Str());

		if (!TextureManager::getInstance().hasKey(convStr))
		{
			std::string path = this->directory + "/" + convStr;

			Texture texture(textureType);
			texture.allocate();
			texture.bind();
			texture.set2DImage(Image(path, ImageType::Alpha));
			texture.generateMipmap();

			TextureManager::getInstance().load(convStr, texture);
		}
		
		textures.push_back(TextureManager::getInstance().get(convStr));
	}
}