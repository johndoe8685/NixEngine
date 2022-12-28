#pragma once
#include "framebuffer.h"
#include "scene.h"

class ShadowMap : public FrameBuffer
{
private:
	ShaderManager shaderManager;
public:
	ShadowMap(unsigned int ShadowWidth, unsigned int ShadowHeight);
	~ShadowMap();

	void TextureFilters() override;
	void FrameBufferSettings() override;

	void Write(Scene* scene, Shader* shader) override;
};