#define _USE_MATH_DEFINES
#include <memory>

#include "Window.h"
#include "Line.h"
#include "MorphObject.h"

int main()
{
    const std::string vertexShaderCircle = R"(
#version 450 core

layout (location=0) in vec3 position;
layout (location=16) uniform mat4 u_matrix;
layout (location=0) uniform float u_phase;

void main()
{
    float startZ = position.x * position.x + position.y * position.y;
    vec4 startPosition = vec4(position.xy, startZ, 1.0);
    float finishZ = position.x * position.x - position.y * position.y;
    vec4 endPosition = vec4(position.xy, finishZ, 1.0);

    vec4 vertex = mix(startPosition, endPosition, u_phase);
    gl_Position = u_matrix * vertex;
}
    )";

    if (!glfwInit())
    {
        throw std::runtime_error("glfw is not initialized");
    }

    GLFWwindow* glfwWindow = glfwCreateWindow(1200, 900, "3 task", NULL, NULL);
    if (!glfwWindow)
    {
        glfwTerminate();
        throw std::runtime_error("could not create window");
    }

    glfwMakeContextCurrent(glfwWindow);

    glewInit();
    if (!GLEW_ARB_shader_objects)
    {
        throw std::runtime_error("glew is not initialized");
    }

    Window window(glfwWindow);
    window.AddDrawable(std::make_shared<MorphObject>(80, window.GetVBO(), window.GetVAO()));
    window.AddShader(std::make_shared<Shader>(GL_VERTEX_SHADER, vertexShaderCircle.c_str()));
    window.Run();

    return 0;
}