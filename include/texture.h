#pragma once
#include "renderer.h"
#define STB_IMAGE_IMPLEMENTATION
   #include "vendor/stb/stb_image.h"

class Texture
{
private:
    unsigned int m_ModuleID;
    std::string m_filepath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const std::string& path);
    ~Texture();

    void Blend() const;
    void Bind(unsigned int slot) const;
    void Unbind() const;

    int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
};


