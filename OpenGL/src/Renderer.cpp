#include "Renderer.h"

#include "ErrorHandle.h"

void Renderer::Clear() const
{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const Shader& shader, const unsigned int count) const
{
    shader.Bind();
    va.Bind();

    GLCALL(glDrawArrays(GL_TRIANGLES, 0, count));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}