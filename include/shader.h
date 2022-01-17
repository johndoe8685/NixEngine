#pragma once
#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>

class Shader
{
private:
    unsigned int m_ModuleID;
    std::string m_FragmentFilePath;
	std::string m_VertexFilePath;
public:
    Shader(const std::string& fragmentShader, const std::string& vertexShader);
    ~Shader();

    std::string GetShaderSource(const std::string& filepath);
    unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource);
    unsigned int CompileShader(unsigned int type, const std::string& source);

    void Bind() const;
	void Unbind() const;
};
