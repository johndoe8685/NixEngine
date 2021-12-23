#include "shader.h"

Shader::Shader(const std::string& fragmentShader,const std::string& vertexShader)
    : m_FragmentFilePath(fragmentShader), m_VertexFilePath(vertexShader), m_ModuleID(0)
{
    std::string fragmentSource = GetShaderSource(fragmentShader);
    std::string vertexSource = GetShaderSource(vertexShader);
}

std::string Shader::GetShaderSource(const std::string& filepath) {
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[1];
    while (getline(stream, line)) {
        ss[0] << line << '\n';
    }
    return ss[0].str();
}