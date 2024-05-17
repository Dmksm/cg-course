#define _USE_MATH_DEFINES
#include <memory>
#include <vector>
#include <stdexcept>

#include "Square.h"
#include "Window.h"

int main()
{
    // сделать чтобы сохранял пропорции и доп кружочек сверху
    const std::string fragmentShader = R"(
#version 450 core

layout(location = 0) uniform vec2 u_resolution;
layout (location=16) uniform mat4 u_matrix;

void main()
{
    vec2 normalizedCoord = gl_FragCoord.xy / u_resolution.xy;
    float aspectRatio = u_resolution.x / u_resolution.y;
    vec2 pos = vec2(0.5, 0.4);
    float dis = distance(normalizedCoord, pos);
    vec2 pos2 = vec2(0.5, 0.75);
    float dis2 = distance(normalizedCoord, pos2);
    float bigRadius = 0.15 * aspectRatio;
    float smallRadius = 0.13 * aspectRatio;

    vec3 color = vec3(0.0, 1.0, 1.0);
    if ((smallRadius < dis && dis < bigRadius) || 
        (smallRadius < dis2 && dis2 < bigRadius))
    {
        color = vec3(0.0, 0.0, 0.0);
    }

    gl_FragColor = vec4(color, 1.0);
}
    )";

    if (!glfwInit())
    {
        throw std::runtime_error("glfw is not initialized");
    }

    GLFWwindow* glfwWindow = glfwCreateWindow(800, 800, "Flag", NULL, NULL);
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
    window.AddDrawable(std::make_shared<Square>());
    window.AddShader(std::make_shared<Shader>(GL_FRAGMENT_SHADER, fragmentShader.c_str()));
    window.Run();

    return 0;
}