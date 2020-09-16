#pragma once

#include "Test.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexBufferLayout.h"

#include <memory>

namespace test
{
    class TestLighting : public Test
    {
    public:
        TestLighting();
        ~TestLighting();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<Shader> m_Shader;

        glm::mat4 m_Proj, m_View, m_Model, m_MVP;
        float m_AmbientLightColor[4];
        float m_DiffuseLightColor[4];
        float m_DiffuseLightPosition[4];
    };
}