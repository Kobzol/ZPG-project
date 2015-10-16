//#pragma once
//
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//
//#include <string>
//#include <vector>
//#include <unordered_map>
//
//#include "../Render/program.h"
//#include "../Render/renderer.h"
//#include "mesh.h"
//
//class Model
//{
//public:
//	Model(std::string path);
//
//	void draw(Program& program, Renderer& renderer);
//	void dispose();
//
//private:
//	std::vector<Mesh> meshes;
//	std::string directory;
//	std::unordered_map<std::string, Texture> loadedTextures;
//
//	void loadModel(std::string path);
//	void processNode(aiNode* node, const aiScene* scene);
//	void addMesh(aiMesh* mesh, const aiScene* scene);
//	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType assimpType, TextureType textureType);
//};