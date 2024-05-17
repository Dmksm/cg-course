#define _USE_MATH_DEFINES
#include <memory>
#include <vector>
#include <stdexcept>

#include "Square.h"
#include "Window.h"

int main()
{
    // сделать чтобы сохранял пропорции и доп кружочек сверху
//    const std::string vertexShader = R"(
//#version 450 core
//
//layout (location=0) in vec4 position;
//layout (location=16) uniform mat4 u_matrix;
//varying vec4 pos;
//
//void main()
//{
//    pos = u_matrix * vec4(position.x, position.y, 0, 1);
//}
//    )";

    const std::string fragmentShader = R"(
#version 450 core

layout(location = 0) uniform vec2 u_resolution;

void main()
{
    vec2 pixelCoord = gl_FragCoord.xy / u_resolution.xy;

    vec2 pos = vec2(0.5, 0.4);
    float dis = distance(pixelCoord, pos);
    vec2 pos2 = vec2(0.5, 0.75);
    float dis2 = distance(pixelCoord, pos2);
    float bigRadius = 0.15;
    float smallRadius = 0.13;

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