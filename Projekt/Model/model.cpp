//#include "model.h"
//
//Model::Model(std::string path)
//{
//	this->loadModel(path);
//}
//
//void Model::draw(Program& program, Renderer& renderer)
//{
//	for (GLuint i = 0; i < this->meshes.size(); i++)
//	{
//		this->meshes[i].draw(program, renderer);
//	}
//}
//void Model::dispose()
//{
//	for (GLuint i = 0; i < this->meshes.size(); i++)
//	{
//		this->meshes[i].dispose();
//	}
//}
//
//void Model::loadModel(std::string path)
//{
//	Assimp::Importer importer;
//	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
//
//	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//	{
//		GL_PRINT_ERROR("failed loading scene from model " + path + ": " + std::string(importer.GetErrorString()));
//	}
//	this->directory = path.substr(0, path.find_last_of("/"));
//
//	this->processNode(scene->mRootNode, scene);
//}
//void Model::processNode(aiNode* node, const aiScene* scene)
//{
//	for (GLuint i = 0; i < node->mNumMeshes; i++)
//	{
//		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//		this->addMesh(mesh, scene);
//	}
//
//	for (GLuint i = 0; i < node->mNumChildren; i++)
//	{
//		this->processNode(node->mChildren[i], scene);
//	}
//}
//
//void Model::addMesh(aiMesh* mesh, const aiScene* scene)
//{
//	std::vector<Vertex> vertices;
//	std::vector<GLuint> indices;
//	std::vector<Texture> textures;
//
//	for (GLuint i = 0; i < mesh->mNumVertices; i++)
//	{
//		Vertex vertex;
//		vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
//		vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
//		
//		if (mesh->mTextureCoords[0])
//		{
//			vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
//		}
//		else vertex.texCoords = glm::vec2(0.0f);
//
//		vertices.push_back(vertex);
//	}
//
//	for (GLuint i = 0; i < mesh->mNumFaces; i++)
//	{
//		aiFace face = mesh->mFaces[i];
//
//		for (GLuint j = 0; j < face.mNumIndices; j++)
//		{
//			indices.push_back(face.mIndices[j]);
//		}
//	}
//
//	if (mesh->mMaterialIndex >= 0)
//	{
//		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//		
//		std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
//		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//		
//		std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular);
//		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//	}
//
//	this->meshes.push_back(Mesh(vertices, indices, textures));
//	this->meshes[this->meshes.size() - 1].setup();
//}
//
//std::vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType assimpType, TextureType textureType)
//{
//	std::vector<Texture> textures;
//
//	for (GLuint i = 0; i < material->GetTextureCount(assimpType); i++)
//	{
//		aiString str;
//		material->GetTexture(assimpType, i, &str);
//		
//		std::string convStr = std::string(str.C_Str());
//
//		if (!this->loadedTextures.count(convStr))
//		{
//			std::string path = this->directory + "/" + convStr;
//
//			Texture texture(textureType);
//			texture.allocate();
//			texture.bind();
//			texture.path = str;
//			texture.set2DImage(Image(path, ImageType::Alpha));
//			texture.generateMipmap();
//
//			loadedTextures[convStr] = texture;
//		}
//		
//		textures.push_back(this->loadedTextures[convStr]);
//	}
//
//	return textures;
//}