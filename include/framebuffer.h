#pragma once
#include "system.h"
#include "shadermanager.h"
#include "scene.h"

class FrameBuffer : public System
{
public:
	unsigned int m_fbo;
	unsigned int m_frameBufferTexture;
	unsigned int m_textureWidth;
	unsigned int m_textureHeight;

	FrameBuffer(std::string componentName, unsigned int TextureWidth, unsigned int TextureHeight);
	FrameBuffer(std::string componentName, std::string subClass, unsigned int TextureWidth, unsigned int TextureHeight);
	void CreateFrameBuffer();
	virtual void TextureFilters();
	virtual void FrameBufferSettings();
	void Read(unsigned int TextureUnit);
	virtual void Write(Scene* scene, Shader* shader);
};