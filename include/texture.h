#pragma once
#include "renderer.h"
#include "vendor/stb/stb_image.h"
#ifdef __linux__
#include "unistd.h"
#endif
#ifdef _WIN64
#include <direct.h>
#define GetCurrentDir _getcwd
#endif

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
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
};