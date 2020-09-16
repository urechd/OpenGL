#include "TestTexture2D.h"

#include "imgui/imgui.h"
#include "ErrorHandle.h"
#include "GL/glew.h"

namespace test
{
    TestTexture2D::TestTexture2D()
        : m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0), m_IndexBuffer(),
        m_Proj(glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
    {
        float positions[] =
        {
            -50.0f, -50.0f, 0.0f, 0.0f, // 0
             50.0f, -50.0f, 1.0f, 0.0f, // 1
             50.0f,  50.0f, 1.0f, 1.0f, // 2
            -50.0f,  50.0f, 0.0f, 1.0f  // 3
        };

        unsigned int indeces[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();

        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;

        layout.Push<float>(2);
        layout.Push<float>(2);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indeces, 6);

        m_Shader = std::make_unique<Shader>("res/shaders/2Dshader.glsl.vert", "res/shaders/2Dshader.glsl.frag");
        m_Shader->Bind();

        m_Texture = std::make_unique<Texture>("res/textures/Hmmm.png");
        m_Shader->SetUniform1i("u_Texture", 0);
    }

    TestTexture2D::~TestTexture2D()
    {

    }

    void TestTexture2D::OnUpdate(float deltaTime)
    {

    }

    void TestTexture2D::OnRender()
    {
        GLCALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;

            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;

            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
    }

    void TestTexture2D::OnImGuiRender()
    {
        ImGui::SliderFloat3("Transformation A", &m_TranslationA.x, 0.0f, 800.0f);
        ImGui::SliderFloat3("Transformation B", &m_TranslationB.x, 0.0f, 800.0f);
    }
}