#pragma once
#include <vendor/glad/glad.h>
#include <vendor/glm/gtc/type_ptr.hpp>
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
    bool printed;
public:
    Shader(const std::string& fragmentShader, const std::string& vertexShader);
    ~Shader() { glDeleteProgram(m_ModuleID); }

    unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource);
    unsigned int CompileShader(unsigned int type, const std::string& source);

    int GetUniformLocation(const std::string& name);
    std::string GetShaderSource(const std::string& filepath);

    void SetUniformMatrix4fv(const std::string& name, glm::mat4 value);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform1f(const std::string& name, float v0);

    void Bind() const { glUseProgram(m_ModuleID); }
	void Unbind() const { glUseProgram(0); }
};
