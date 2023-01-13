#pragma once
#include "system.h"
#include <vendor/glad/glad.h>

#define CREATE_RENDER_BUFFER_OBJECT 2

class FrameBuffer : public System
{
public:
	unsigned int m_fbo;
	unsigned int m_rbo;
	unsigned int m_frameBufferTexture;
	unsigned int m_textureWidth;
	unsigned int m_textureHeight;

	FrameBuffer(std::string componentName, unsigned int TextureWidth, unsigned int TextureHeight);
	FrameBuffer(std::string componentName, std::string subClass, unsigned int TextureWidth, unsigned int TextureHeight);
	FrameBuffer(std::string componentName, unsigned int TextureWidth, unsigned int TextureHeight, unsigned int parseValue);
	FrameBuffer(std::string componentName, std::string subClass, unsigned int TextureWidth, unsigned int TextureHeight, unsigned int parseValue);
	void CreateFrameBuffer(unsigned int parseValue);
	virtual void TextureFilters();
	virtual void FrameBufferSettings();
	virtual void CreateRenderBufferObjects();
	void Read(unsigned int TextureUnit);
	virtual void Write();
};