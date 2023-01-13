#include "framebuffer.h"


FrameBuffer::FrameBuffer(std::string componentName, unsigned int TextureWidth, unsigned int TextureHeight)
	:System(componentName, "FrameBuffer"), m_textureWidth(TextureWidth), m_textureHeight(TextureHeight)
{

}

FrameBuffer::FrameBuffer(std::string componentName, std::string subClass, unsigned int TextureWidth, unsigned int TextureHeight)
	:System(componentName, subClass), m_textureWidth(TextureWidth), m_textureHeight(TextureHeight)
{

}

FrameBuffer::FrameBuffer(std::string componentName, unsigned int TextureWidth, unsigned int TextureHeight, unsigned int parseValue)
	:System(componentName, "FrameBuffer"), m_textureWidth(TextureWidth), m_textureHeight(TextureHeight)
{

}

FrameBuffer::FrameBuffer(std::string componentName, std::string subClass, unsigned int TextureWidth, unsigned int TextureHeight, unsigned int parseValue)
	:System(componentName, subClass), m_textureWidth(TextureWidth), m_textureHeight(TextureHeight)
{

}

void FrameBuffer::CreateFrameBuffer(unsigned int parseValue)
{
	if (parseValue == CREATE_RENDER_BUFFER_OBJECT)
	{
		glGenFramebuffers(1, &m_fbo);
		glGenTextures(1, &m_frameBufferTexture);
		glBindTexture(GL_TEXTURE_2D, m_frameBufferTexture);
		TextureFilters();
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		FrameBufferSettings();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	else
	{
		glGenFramebuffers(1, &m_fbo);
		glGenTextures(1, &m_frameBufferTexture);
		glBindTexture(GL_TEXTURE_2D, m_frameBufferTexture);
		TextureFilters();
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		FrameBufferSettings();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
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

void FrameBuffer::CreateRenderBufferObjects()
{
	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_textureHeight, m_textureWidth);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
}

void FrameBuffer::Read(unsigned int TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, m_frameBufferTexture);
}
	
void FrameBuffer::Write()
{
	glViewport(0, 0, m_textureWidth, m_textureHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

