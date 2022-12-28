#include "framebuffer.h"

FrameBuffer::FrameBuffer(std::string componentName, unsigned int TextureWidth, unsigned int TextureHeight)
	:System(componentName, "FrameBuffer"), m_textureWidth(TextureWidth), m_textureHeight(TextureHeight)
{
	CreateFrameBuffer();
}

FrameBuffer::FrameBuffer(std::string componentName, std::string subClass, unsigned int TextureWidth, unsigned int TextureHeight)
	:System(componentName, subClass), m_textureWidth(TextureWidth), m_textureHeight(TextureHeight)
{
	CreateFrameBuffer();
}

void FrameBuffer::CreateFrameBuffer()
{
	glGenFramebuffers(1, &m_fbo);
	glGenTextures(1, &m_frameBufferTexture);
	glBindTexture(GL_TEXTURE_2D, m_frameBufferTexture);
	TextureFilters();
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	FrameBufferSettings();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::TextureFilters()
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureWidth, m_textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void FrameBuffer::FrameBufferSettings()
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_frameBufferTexture, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void FrameBuffer::Read(unsigned int TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, m_frameBufferTexture);
}

void FrameBuffer::Write(Scene* scene, Shader* shader)
{
	shader->Bind();
	scene->ProcessScene(shader);
	glViewport(0, 0, m_textureWidth, m_textureHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->Unbind();
}

