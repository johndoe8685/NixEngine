#pragma once
#include "vendor/stb/stb_image.h"
#include "system.h"
#include "shader.h"
#include "mesh.h"
#include "shadermanager.h"

class Skybox : public System
{
private:
	
	Shader* m_skyShader;
	Mesh* m_skyMesh;
	ShaderManager shadermanager;

	unsigned int m_textureID;
public:
	Skybox(std::string componentName, std::string fileName);
	void DrawSkybox();
};