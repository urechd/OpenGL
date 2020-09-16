#include "Shader.h"

#include "ErrorHandle.h"
#include "GL/glew.h"

#include <iostream>
#include <vector>
#include <fstream>

Shader::Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
    std::string vertexSource = ParseShader(vertexShaderFilePath);
    std::string fragmentSource = ParseShader(fragmentShaderFilePath);

    m_RendererID = CreateShader(vertexSource, fragmentSource);
}

Shader::~Shader()
{
    GLCALL(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCALL(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCALL(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCALL(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCALL(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform4fv(const std::string& name, const float vector[4])
{
    GLCALL(glUniform4fv(GetUniformLocation(name), 1, vector));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

std::string Shader::ParseShader(const std::string& filePath)
{
    std::string result;
    std::ifstream in(filePath, std::ios::in | std::ios::binary);
    if (in)
    {
        in.seekg(0, std::ios::end);
        result.resize((size_t)in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&result[0], result.size());
        in.close();
    }
    else
    {
        std::cout << "Could not open file " << filePath << std::endl;
    }

    return result;
}

unsigned int Shader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
{
    GLCALL(unsigned int program = glCreateProgram());
    int glShaderIDIndex = 0;

    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    GLCALL(glAttachShader(program, vertexShader));

    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
    GLCALL(glAttachShader(program, fragmentShader));
    
    GLCALL(glLinkProgram(program));
    
    int isLinked = 0;
    GLCALL(glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked));
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        GLCALL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength));

        std::vector<GLchar> infoLog(maxLength);
        GLCALL(glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]));

        GLCALL(glDeleteProgram(program));

        GLCALL(glDeleteShader(vertexShader));
        GLCALL(glDeleteShader(fragmentShader));

        std::cout << infoLog.data() << std::endl;
    }

    GLCALL(glDetachShader(program, vertexShader));
    GLCALL(glDetachShader(program, fragmentShader));
    GLCALL(glDeleteShader(vertexShader));
    GLCALL(glDeleteShader(fragmentShader));

    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);

    const char* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, 0);

    glCompileShader(shader);

    int isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        int maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(shader);

        std::cout << infoLog.data() << std::endl;
    }

    return shader;
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return m_UniformLocationCache[name];
    }

    GLCALL(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    
    if (location == -1)
    {
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    }

    m_UniformLocationCache[name] = location;
    return location;
}