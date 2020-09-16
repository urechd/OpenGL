#include "TestColor3D.h"

#include "ErrorHandle.h"

namespace test
{
    TestColor3D::TestColor3D()
    {
        float positions[] =
        {
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // 0
            -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, // 1
            -1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // 2
            -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // 3
             1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // 4
             1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 1.0f, // 5
             1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 0.0f, // 6
             1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f  // 7
        };

        unsigned int indeces[] =
        {
            0, 2, 1, // -x
            1, 2, 3,

            4, 5, 6, // +x
            5, 7, 6,

            0, 1, 5, // -y
            0, 5, 4,

            2, 6, 7, // +y
            2, 7, 3,

            0, 4, 6, // -z
            0, 6, 2,

            1, 3, 7, // +z
            1, 7, 5
        };

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        m_VAO = std::make_unique<VertexArray>();

        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 6 * 8 * sizeof(float));
        VertexBufferLayout layout;

        layout.Push<float>(3);
        layout.Push<float>(3);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indeces, 6 * 6);

        m_Shader = std::make_unique<Shader>("res/shaders/3Dshader.glsl.vert", "res/shaders/3Dshader.glsl.frag");
        m_Shader->Bind();

        m_Proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        m_View = glm::lookAt(
            glm::vec3(4, 3, 3),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0)
        );
        m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        m_MVP = m_Proj * m_View * m_Model;
    }

    TestColor3D::~TestColor3D()
    {
        glDisable(GL_DEPTH_TEST);
    }

    void TestColor3D::OnUpdate(float deltaTime)
    {

    }

    void TestColor3D::OnRender()
    {
        GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        Renderer renderer;

        m_Model = glm::rotate(m_Model, glm::radians(0.5f), glm::vec3(0.0f, 1.0f, 0.0f));
        m_MVP = m_Proj * m_View * m_Model;

        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", m_MVP);
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void TestColor3D::OnImGuiRender()
    {

    }
}