  #include "shader.h"

Shader::Shader(const std::string& fragmentShader,const std::string& vertexShader)
    : m_FragmentFilePath(fragmentShader), m_VertexFilePath(vertexShader), m_ModuleID(0)
{
    std::string fragmentSource = GetShaderSource(fragmentShader);
    std::string vertexSource = GetShaderSource(vertexShader);
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

void Shader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
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
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "[ERROR] SHADER COMPILATION FAILED\n" << infoLog << std::endl;
    }
}
void Shader::Bind() const
{
    glUseProgram(m_ModuleID);
}
void Shader::Unbind() const
{
    glUseProgram(0);
}
