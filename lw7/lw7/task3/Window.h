#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
#include <string>
#include <cstdlib>
#include <memory>
#include <vector>
#include <stdexcept>
#include <optional>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/orthonormalize.hpp>

#include "IDrawable.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include <glm/fwd.hpp>

class Window
{
public:
    Window(GLFWwindow* window)
        : m_window(window)
        , m_program(std::make_unique<ShaderProgram>())
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
    }

    void Run()
    {
        Init();
        while (!glfwWindowShouldClose(m_window))
        {
            RunFrame();
        }
        CleanUp();
    }

    void AddDrawable(std::shared_ptr<IDrawable> drawable)
    {
        m_drawables.push_back(drawable);
    }

    void AddShader(std::shared_ptr<Shader> shader)
    {
        m_shaders.push_back(shader);
    }

    const unsigned int& GetVAO()const
    {
        return m_VAO;
    }

    const unsigned int& GetVBO()const
    {
        return m_VBO;
    }

    ~Window()
    {
        glfwTerminate();
    }

private:
    void CleanUp()
    {
        glDeleteBuffers(1, &m_VBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    void RunFrame()
    {
        int screenWidth, screenHeight;
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glfwGetWindowSize(m_window, &screenWidth, &screenHeight);
        glEnable(GL_DEPTH_TEST);

        SetupMatrixes(screenWidth, screenHeight);
        OnMotion();
        Draw();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void Init()
    {
        InitShaders();

        for (auto& drawableObject : m_drawables)
        {
            drawableObject->Init();
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glClearColor(1, 1, 1, 0);
        glUseProgram(*m_program);
    }

    void Draw()
    {
        glBindVertexArray(m_VAO);
        DrawObjects();
        glBindVertexArray(0);
    }

    void SetupMatrixes(int screenWidth, int screenHeight)
    {
        SetupProjectionMatrix(screenWidth, screenHeight);
        SetupModelViewMatrix();
        SetupShaderMatrix();
    }

    void SetupShaderMatrix()
    {
        auto mvpMatrix = m_projectionMatrix * m_modelViewMatrix;

        for (int i = 0; i < mvpMatrix.length(); ++i)
        {
            for (int j = 0; j < mvpMatrix[i].length(); ++j)
            {
                m_shaderMatrix[i * mvpMatrix.length() + j] = float(mvpMatrix[i][j]);
            }
        }

        glUniformMatrix4fv(16, 1, GL_FALSE, m_shaderMatrix);
    }

    void InitShaders()
    {
        if (m_shaders.size() == 0)
        {
            return;
        }

        for (auto& shader : m_shaders)
        {
            shader->Compile();
            if (!shader->IsCompiled())
            {
                auto m = shader->GetInfoLog();
                throw std::runtime_error("Failed to compile shader: " + shader->GetInfoLog());
            }

            m_program->AttachShader(*shader);
        }

        m_program->Link();
        if (!m_program->IsLinked())
        {
            auto m = m_program->GetInfoLog();
            throw std::runtime_error("Failed to link program: " + m_program->GetInfoLog());
        }
    }

    void OnMotion()
    {
        double currMousePosX, currMousePosY;
        glfwGetCursorPos(m_window, &currMousePosX, &currMousePosY);

        if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS
            && m_mousePosX.has_value() && m_mousePosY.has_value())
        {
            if (m_mousePosX == currMousePosX && m_mousePosY == currMousePosY)
            {
                return;
            }

            double dx = currMousePosX - m_mousePosX.value();
            double dy = currMousePosY - m_mousePosY.value();

            int height, width;
            glfwGetWindowSize(m_window, &width, &height);

            GLdouble rotateX = dy * M_PI / width;
            GLdouble rotateY = dx * M_PI / height;
            RotateCamera(rotateX, rotateY);
        }

        m_mousePosX = currMousePosX;
        m_mousePosY = currMousePosY;
    }

    void RotateCamera(double xAngleRadians, double yAngleRadians)
    {
        const glm::dvec3 xAxis{
            m_modelViewMatrix[0][0], m_modelViewMatrix[1][0], m_modelViewMatrix[2][0]
        };
        const glm::dvec3 yAxis{
            m_modelViewMatrix[0][1], m_modelViewMatrix[1][1], m_modelViewMatrix[2][1]
        };

        m_modelViewMatrix = glm::rotate(m_modelViewMatrix, xAngleRadians, xAxis);
        m_modelViewMatrix = glm::rotate(m_modelViewMatrix, yAngleRadians, yAxis);

        m_modelViewMatrix = Orthonormalize(m_modelViewMatrix);
    }

    void SetupProjectionMatrix(int width, int height)
    {
        glViewport(0, 0, width, height);

        double aspect = double(width) / double(height);

        glMatrixMode(GL_PROJECTION);
        m_projectionMatrix = glm::perspective(60.0 * M_PI / 180.0, aspect, 0.1, 10.0);
        glLoadMatrixd(&m_projectionMatrix[0][0]);
    }

    void SetupModelViewMatrix()
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixd(&m_modelViewMatrix[0][0]);
    }

    void DrawObjects()
    {
        for (auto& drawableObject : m_drawables)
        {
            drawableObject->Draw();
        }
    }

    glm::dmat4x4 Orthonormalize(const glm::dmat4x4& m)
    {
        const auto normalizedMatrix = glm::orthonormalize(glm::dmat3x3{ m });
        return {
            glm::dvec4{ normalizedMatrix[0], 0.0 },
            glm::dvec4{ normalizedMatrix[1], 0.0 },
            glm::dvec4{ normalizedMatrix[2], 0.0 },
            m[3]
        };
    }

    inline const static int m_FRUSTUM_SIZE = 2;

    std::optional<double> m_mousePosX;
    std::optional<double> m_mousePosY;

    GLFWwindow* m_window;
    std::unique_ptr<ShaderProgram> m_program = nullptr;
    std::vector<std::shared_ptr<IDrawable>> m_drawables = {};
    std::vector<std::shared_ptr<Shader>> m_shaders = {};
    unsigned int m_VAO, m_VBO;

    glm::dmat4x4 m_modelViewMatrix = glm::lookAt(
        glm::dvec3{ 0.0, 0.0, 5 },
        glm::dvec3{ 0.0, 0.0, 0.0 },
        glm::dvec3{ 0.0, 1.0, 0.0 }
    );
    glm::dmat4x4 m_projectionMatrix = glm::lookAt(
        glm::dvec3{ 0.0, 0.0, 0.0 },
        glm::dvec3{ 0.0, 0.0, 0.0 },
        glm::dvec3{ 0.0, 0.0, 0.0 }
    );
    float m_shaderMatrix[16] = {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
    };
};