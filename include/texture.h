#pragma once
#include <vendor/glad/glad.h>
#include <vendor/glm/gtc/type_ptr.hpp>
#include "vendor/stb/stb_image.h"
#include "system.h"
#include "directory.h"


class Texture : public System
{
private:
    unsigned int m_textureID;
    std::string m_filepath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const std::string& path);
    ~Texture();

    void Blend() const;
    void Bind() const;
    void Unbind() const;
    bool LoadTexture();

    int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
};