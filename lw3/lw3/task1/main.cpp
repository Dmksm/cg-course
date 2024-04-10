#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

struct Point 
{
    float x, y;
};

std::vector<Point> ControlPoints = { {100, 100}, {200, 300}, {400, 200}, {500, 400} };
int SelectedPointIndex = -1;
bool IsDragging = false;
Point MousePos;

Point CalculateBezierPoint(float t) 
{
    float oneMinusT = 1.0f - t;
    Point p;
    p.x = oneMinusT * oneMinusT * oneMinusT * ControlPoints[0].x +
        3 * oneMinusT * oneMinusT * t * ControlPoints[1].x +
        3 * oneMinusT * t * t * ControlPoints[2].x +
        t * t * t * ControlPoints[3].x;

    p.y = oneMinusT * oneMinusT * oneMinusT * ControlPoints[0].y +
        3 * oneMinusT * oneMinusT * t * ControlPoints[1].y +
        3 * oneMinusT * t * t * ControlPoints[2].y +
        t * t * t * ControlPoints[3].y;

    return p;
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) 
{
    if (button == GLFW_MOUSE_BUTTON_LEFT) 
    {
        if (action == GLFW_PRESS) 
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            MousePos.x = static_cast<float>(xpos);
            MousePos.y = static_cast<float>(ypos);

            for (size_t i = 0; i < ControlPoints.size(); ++i) 
            {
                float dx = MousePos.x - ControlPoints[i].x;
                float dy = MousePos.y - ControlPoints[i].y;
                float distanceSquared = dx * dx + dy * dy;
                if (distanceSquared < 25) 
                {
                    SelectedPointIndex = static_cast<int>(i);
                    IsDragging = true;
                    break;
                }
            }
        }
        else if (action == GLFW_RELEASE) 
        {
            IsDragging = false;
            SelectedPointIndex = -1;
        }
    }
}

void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) 
{
    if (IsDragging && SelectedPointIndex != -1) 
    {
        ControlPoints[SelectedPointIndex].x = static_cast<float>(xpos);
        ControlPoints[SelectedPointIndex].y = static_cast<float>(ypos);
    }
}

void DrawBezierCurve() 
{
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; ++i) 
    {
        float t = i / 100.0f;
        Point p = CalculateBezierPoint(t);
        glVertex2f(p.x, p.y);
    }
    glEnd();
}

void DrawControlPoints() 
{
    glPointSize(10);
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    for (const auto& point : ControlPoints) 
    {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

int main() {
    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(1920, 1080, "Draw Smeshariki", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPositionCallback);

    while (!glfwWindowShouldClose(window)) 
    {
        glClear(GL_COLOR_BUFFER_BIT);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);

        glColor3f(1, 1, 1);
        DrawBezierCurve();
        DrawControlPoints();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
