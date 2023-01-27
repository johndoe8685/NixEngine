#include "skybox.h"

Skybox::Skybox(std::string componentName, std::string fileName)
	:System(componentName, "Skybox")
{
	shadermanager = ShaderManager::Get();
	stbi_set_flip_vertically_on_load(0);

	//Burada eklenecek olan skyboxlar /res/texture/skybox/ klas�r�nde, verilen fileName'e sahip olup 6 resmin de ismini right left up gibi devam etmesini standartla�t�r�yor
	std::string faceLocations[] = { "right", "left", "top", "bottom", "front" ,"back" };
	for (size_t i = 0; i < 6; i++)
	{
		faceLocations[i] = std::string("/res/texture/skybox/") + fileName + "/" + faceLocations[i];
		debugger.giveMessage(Debugger::Info, "Loading", faceLocations[i]);
	}
	
	m_skyShader = new Shader("Skybox", "/res/shader/skybox.frag", "/res/shader/skybox.vert");

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

	int width, height, bitDepth;

	for (size_t i = 0; i < 6; i++)
	{
		std::string temp = faceLocations[i] + ".png";
		directory.changePath(temp);
		unsigned char* texData = stbi_load(directory.getPath().c_str(), &width, &height, &bitDepth, 0);
		if (!texData)
		{
			temp = faceLocations[i] + ".jpg";
			directory.changePath(temp);
			texData = stbi_load(directory.getPath().c_str(), &width, &height, &bitDepth, 0);
			if (!texData)
			{
				debugger.giveMessage(Debugger::DebugLevel::Error, "Failed to Find", faceLocations[i]);
				m_skyMesh = nullptr;
				return;
			}
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		stbi_image_free(texData);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	// Mesh Setup
	std::vector<unsigned int> skyboxIndices;
	// front
	skyboxIndices.push_back(0);
	skyboxIndices.push_back(1);
	skyboxIndices.push_back(2);
	skyboxIndices.push_back(2);
	skyboxIndices.push_back(1);
	skyboxIndices.push_back(3);
	// right
	skyboxIndices.push_back(2);
	skyboxIndices.push_back(3);
	skyboxIndices.push_back(5);
	skyboxIndices.push_back(5);
	skyboxIndices.push_back(3);
	skyboxIndices.push_back(7);
	// back
	skyboxIndices.push_back(5);
	skyboxIndices.push_back(7);
	skyboxIndices.push_back(4);
	skyboxIndices.push_back(4);
	skyboxIndices.push_back(7);
	skyboxIndices.push_back(6);
	// left
	skyboxIndices.push_back(4);
	skyboxIndices.push_back(6);
	skyboxIndices.push_back(0);
	skyboxIndices.push_back(0);
	skyboxIndices.push_back(6);
	skyboxIndices.push_back(1);
	// top
	skyboxIndices.push_back(4);
	skyboxIndices.push_back(0);
	skyboxIndices.push_back(5);
	skyboxIndices.push_back(5);
	skyboxIndices.push_back(0);
	skyboxIndices.push_back(2);
	// bottom
	skyboxIndices.push_back(1);
	skyboxIndices.push_back(6);
	skyboxIndices.push_back(3);
	skyboxIndices.push_back(3);
	skyboxIndices.push_back(6);
	skyboxIndices.push_back(7);

	std::vector<Vertex> skyboxVertices;
	skyboxVertices.push_back({ glm::vec3(-1.0f, 1.0f, -1.0f),  glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) });
	skyboxVertices.push_back({ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) });
	skyboxVertices.push_back({ glm::vec3(1.0f, 1.0f, -1.0f),   glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) });
	skyboxVertices.push_back({ glm::vec3(1.0f, -1.0f, -1.0f),  glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) });

	skyboxVertices.push_back({ glm::vec3(-1.0f, 1.0f, 1.0f),   glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) });
	skyboxVertices.push_back({ glm::vec3(1.0f, 1.0f, 1.0f),    glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) });
	skyboxVertices.push_back({ glm::vec3(-1.0f, -1.0f, 1.0f),  glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) });
	skyboxVertices.push_back({ glm::vec3(1.0f, -1.0f, 1.0f),   glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) });

	m_skyMesh = new Mesh(skyboxVertices, skyboxIndices);
}
//void Skybox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
void Skybox::DrawSkybox(glm::mat4 view, glm::mat4 projection)
{
	if (m_skyMesh != nullptr && m_skyShader != nullptr)
	{
		//viewMatrix'i matris 4x4'ten matris 3x3'e d�n��t�r.
		//Bu d�n���m viewMatrix'in scale ve position'ununu de�i�tirmiyor ama rotation'nunu kald�r�yor
		glm::mat4 viewMatrix = view;
		viewMatrix = glm::mat4(glm::mat3(viewMatrix));

		//Burada depth testi kapat ��nk� skybox'u en son framebuffer'a yazaca��z
		glDepthMask(GL_FALSE);
		
		m_skyShader->SetUniformMatrix4fv("projection", projection);
		m_skyShader->SetUniformMatrix4fv("view", viewMatrix);

		m_skyShader->Bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

		m_skyMesh->RenderMesh();
		m_skyShader->Unbind();

		//Geri depth testi a�
		glDepthMask(GL_TRUE);
	}
}
