#include "shadowmap.h"

ShadowMap::ShadowMap(unsigned int ShadowWidth, unsigned int ShadowHeight)
	:FrameBuffer("Default", "ShadowMap", ShadowWidth, ShadowHeight)
{
	shaderManager = ShaderManager::Get();
	CreateFrameBuffer();
}

void ShadowMap::TextureFilters()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void ShadowMap::FrameBufferSettings()
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_frameBufferTexture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
}

void ShadowMap::Write(Scene* scene, Shader* shader)
{
	shader->Bind();
	scene->ProcessScene(shader);
	glViewport(0, 0, m_textureWidth, m_textureHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glClear(GL_DEPTH_BUFFER_BIT);
	shader->Unbind();
}

ShadowMap::~ShadowMap()
{

}
