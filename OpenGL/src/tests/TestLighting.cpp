#include "TestLighting.h"

#include "ErrorHandle.h"
#include "imgui/imgui.h"

namespace test
{
    TestLighting::TestLighting()
        : m_AmbientLightColor { 1.0f, 1.0f, 1.0f, 1.0f }, m_DiffuseLightColor { 1.0f, 1.0f, 1.0f, 1.0f },
          m_DiffuseLightPosition { 1.0f, 1.0f, 1.0f, 1.0f }
    {
        float positions[] =
        {
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f
        };

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        m_VAO = std::make_unique<VertexArray>();

        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 9 * 36 * sizeof(float));
        VertexBufferLayout layout;

        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(3);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_Shader = std::make_unique<Shader>("res/shaders/light_shader.glsl.vert", "res/shaders/light_shader.glsl.frag");
        m_Shader->Bind();

        m_Proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        m_View = glm::lookAt(
            glm::vec3(4, 3, 3),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0)
        );
        m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        m_Model = glm::rotate(m_Model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        m_MVP = m_Proj * m_View * m_Model;

        m_Shader->SetUniformMat4f("u_Model", m_Model);
        m_Shader->SetUniformMat4f("u_MVP", m_MVP);
    }

    TestLighting::~TestLighting()
    {
        glDisable(GL_DEPTH_TEST);
    }

    void TestLighting::OnUpdate(float deltaTime)
    {

    }

    void TestLighting::OnRender()
    {
        GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        Renderer renderer;

        m_Shader->Bind();
        m_Shader->SetUniform4fv("u_AmbientLightColor", m_AmbientLightColor);
        m_Shader->SetUniform4fv("u_DifuseLightColor", m_DiffuseLightColor);
        m_Shader->SetUniform4fv("u_DiffuseLightPosition", m_DiffuseLightPosition);
        renderer.Draw(*m_VAO, *m_Shader, 36);
    }

    void TestLighting::OnImGuiRender()
    {
        ImGui::ColorEdit4("Ambient Light Color", m_AmbientLightColor);
        ImGui::ColorEdit4("Diffuse Light Color", m_DiffuseLightColor);
        ImGui::SliderFloat4("Diffuse Light Position", m_DiffuseLightPosition, -20.0f, 20.0f);
    }
}