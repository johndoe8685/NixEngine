  #include "shader.h"
#include <iostream>

Shader::Shader(const std::string& fragmentShader,const std::string& vertexShader)
    : m_FragmentFilePath(fragmentShader), m_VertexFilePath(vertexShader), m_ModuleID(0)
{
    std::string cwd = get_current_dir_name();
    std::string fragmentShaderDir = cwd + fragmentShader;
    std::string vertexShaderDir = cwd + vertexShader;
    std::string fragmentSource = GetShaderSource(fragmentShaderDir);
    std::string vertexSource = GetShaderSource(vertexShaderDir);
    std::cout << "[FRAGMENT SOURCE]:\n" << fragmentSource << std::endl;
    std::cout << "[VERTEX SOURCE]\n" << vertexSource << std::endl;
    m_ModuleID = CreateShader(vertexSource, fragmentSource);
}

std::string Shader::GetShaderSource(const std::string& filepath)
{
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[1];
    while (getline(stream, line)) {
        ss[0] << line << '\n';
    }
    return ss[0].str();
}

unsigned int Shader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
{
    unsigned int shaderProgram = glCreateProgram();
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "[ERROR] PROGRAM COMPILATION FAILED\n" << infoLog << std::endl;
    }
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    int  success;
    char infoLog[512];
    glValidateProgram(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "[ERROR] SHADER COMPILATION FAILED\n" << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

int Shader::GetUniformLocation(const std::string& name)
{
    int location = glGetUniformLocation(m_ModuleID, name.c_str());
    if (location == -1)
        std::cout << "[WARNING] Uniform " << name << " doesnt exist!" << std::endl;
    return location;
}

void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4 model, glm::mat4 value)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}
void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}
void Shader::SetUniform1f(const std::string& name, float v0)
{
    glUniform1f(GetUniformLocation(name), v0);
}