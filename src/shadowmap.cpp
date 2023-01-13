#include "shadowmap.h"

ShadowMap::ShadowMap(std::string relativeTo, unsigned int ShadowWidth, unsigned int ShadowHeight, glm::vec3 direction)
	:FrameBuffer("Default", "ShadowMap", ShadowWidth, ShadowHeight), m_direction(direction),
	m_relativeTo(relativeTo), m_PerspectiveSize(30.0f), m_zNear(-50.0f), m_zFar(50.0f), m_biasMin(0.00001f), m_biasMax(0.0001f)
{
	CreateFrameBuffer(CREATE_RENDER_BUFFER_OBJECT);
}

void ShadowMap::TextureFilters()
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_textureWidth, m_textureHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
}

void ShadowMap::FrameBufferSettings()
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_frameBufferTexture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glDisable(GL_CULL_FACE);
}

void ShadowMap::Write()
{
	glViewport(0, 0, m_textureWidth, m_textureHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMap::Process(Shader* shader)
{
	glm::mat4 lightProjection, lightView;
	lightProjection = glm::ortho(-m_PerspectiveSize, m_PerspectiveSize, -m_PerspectiveSize, m_PerspectiveSize, m_zNear, m_zFar);
	lightView = glm::lookAt(-m_direction, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	m_lightSpaceMatrix = lightProjection * lightView;
	shader->SetUniformMatrix4fv("lightSpaceMatrix", m_lightSpaceMatrix);
}

glm::mat4 ShadowMap::GetLightSpaceMatrix()
{
	return m_lightSpaceMatrix;
}

ShadowMap::~ShadowMap()
{

}
