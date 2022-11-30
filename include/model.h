#pragma once
#include <vector>
#include <iostream>
#include <vendor/glm/glm.hpp>
#include <vendor/glm/gtc/matrix_transform.hpp>
#include <vendor/glm/gtc/type_ptr.hpp>
#include <vendor/assimp/Importer.hpp>
#include <vendor/assimp/scene.h>
#include <vendor/assimp/postprocess.h>
#include "system.h"
#include "mesh.h"
#include "texture.h"

class Model : public System
{
private:
	std::vector<Mesh*> m_meshList;
	std::vector<Texture*> m_textureList;
	std::vector<unsigned int> m_textureID;

	//Position, Scale, Rotate variables
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::vec3 m_rotation;
public:
	Model(std::string componentName, const std::string& path);
	~Model();

	void RenderModel();

	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotation(float x, float y, float z);
private:
	void LoadModel();
	void processNode(aiNode *node, const aiScene *scene);
	Mesh* processMesh(aiMesh *mesh, const aiScene *scene);
	void processTexture(const aiScene* scene);
};

