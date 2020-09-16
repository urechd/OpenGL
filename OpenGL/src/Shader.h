#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

class Shader
{
private:
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniform4fv(const std::string& name, const float vector[4]);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
    std::string ParseShader(const std::string& filePath);
    unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    int GetUniformLocation(const std::string& name);
};