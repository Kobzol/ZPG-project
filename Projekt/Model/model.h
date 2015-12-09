#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
#include <unordered_map>
#include <time.h>

#include "mesh.h"
#include "../Content/texture_manager.h"
#include "../Render/render_utils.h"

class Model
{
public:
	Model(std::string path);

	std::vector<Mesh>& getMeshes();
	void dispose();

private:
	Model(const Model& other);
	Model& operator=(const Model& other);

	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	void addMesh(aiMesh* mesh, const aiScene* scene);
	void loadMaterialTextures(aiMaterial* material, aiTextureType assimpType, TextureType textureType, std::vector<Texture>& textures);
};