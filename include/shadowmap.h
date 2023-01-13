#pragma once
#include "framebuffer.h"
#include "shader.h"

class ShadowMap : public FrameBuffer
{
private:
	glm::vec3 m_direction;
	glm::mat4 m_lightSpaceMatrix;
	std::string m_relativeTo;
	float m_PerspectiveSize;
	float m_zNear, m_zFar;
public:
	float m_biasMin, m_biasMax;
	ShadowMap(std::string relativeTo, unsigned int ShadowWidth, unsigned int ShadowHeight, glm::vec3 direction);
	~ShadowMap();

	void TextureFilters() override;
	void FrameBufferSettings() override;

	void Write() override;
	void Process(Shader* shader);

	glm::mat4 GetLightSpaceMatrix();
};