#pragma once
#include <vector>
#include <iostream>
#include <vendor/assimp/Importer.hpp>
#include <vendor/assimp/scene.h>
#include <vendor/assimp/postprocess.h>
#include "directory.h"
#include "mesh.h"
#include "texture.h"

class Model
{
private:
	std::vector<Mesh*> m_meshList;
	std::vector<Texture*> m_textureList;
	std::vector<unsigned int> m_textureID;
	Directory dir;
public:
	Model(const std::string& path);
	~Model();
	void RenderModel();
private:
	void LoadModel();
	void processNode(aiNode *node, const aiScene *scene);
	Mesh* processMesh(aiMesh *mesh, const aiScene *scene);
	void processTexture(const aiScene* scene);
};

