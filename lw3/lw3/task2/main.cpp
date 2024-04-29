#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <numbers>

struct Point 
{
    float x;
    float y;
};

struct Color
{
    float red;
    float green;
    float blue;
};

class Krosh 
{
public:
    // структуру именованных полей для каждого цвета частей чтобы не перепутать и ширину и высоту тоже в структуру
    Krosh(Point position, unsigned width, unsigned height, Color bodyColor, Color legColor, Color handColor, Color earColor)
        : m_position(position)
        , m_width(width)
        , m_height(height)
        , m_bodyColor(bodyColor)
        , m_legColor(legColor)
        , m_handColor(handColor)
        , m_earColor(earColor)
    {
    };

    void Draw()
    {
        glPushMatrix();
        glTranslatef(m_position.x, m_position.y, 0);

        DrawLegs();
        DrawEars();
        DrawBody(); 
        DrawEyelids();
        DrawTeeth(); 
        DrawMouth();
        DrawEyes();
        DrawNose();
        DrawHands();

        glPopMatrix();
    }

private:
    Point m_position;
    unsigned m_width;
    unsigned m_height;
    Color m_bodyColor;
    Color m_legColor;
    Color m_handColor;
    Color m_earColor;

    void DrawEyes()
    {
        glColor3f(1, 1, 1);
        FillEllipse(790, 470, 70, 100, 360);
        glColor3f(0, 0, 0);
        FillEllipse(820, 470, 14, 20, 360);

        glColor3f(1, 1, 1);
        FillEllipse(930, 470, 90, 140, 360);
        glColor3f(0, 0, 0);
        FillEllipse(880, 470, 18, 28, 360);
    }

    void DrawEyelids()
    {
        glColor3f(0, 0, 0);
        FillEllipse(790, 350, 70, 100, 360);
        glColor3f(m_bodyColor.red, m_bodyColor.green, m_bodyColor.blue);
        FillEllipse(790, 356, 75, 100, 360);

        glColor3f(0, 0, 0);
        FillEllipse(930, 450, 90, 140, 360);
        glColor3f(m_bodyColor.red, m_bodyColor.green, m_bodyColor.blue);
        FillEllipse(930, 456, 95, 140, 360);
    }

    void DrawMouth()
    {
        glColor3f(0, 0, 0);
        FillEllipse(870, 630, 200, 41, 360);
        glColor3f(m_bodyColor.red, m_bodyColor.green, m_bodyColor.blue);
        FillEllipse(870, 627, 200, 40, 360);
    }

    void DrawTeeth()
    {
        glColor3f(1, 1, 1);
        FillEllipse(900, 680, 40, 50, 360);
        glColor3f(1, 1, 1);
        FillEllipse(840, 700, 40, 60, 360);
    }

    void DrawNose()
    {
        glColor3f(1, 0, 0);
        FillEllipse(850, 550, 20, 20, 360);
    }

    void DrawBody()
    {
        glColor3f(m_bodyColor.red, m_bodyColor.green, m_bodyColor.blue);
        FillEllipse(850, 600, 370, 370, 360);
    }

    void DrawLegs()
    {
        glColor3f(m_legColor.red, m_legColor.green, m_legColor.blue);
        FillEllipse(600, 900, 150, 100, 360);
        FillEllipse(1100, 900, 150, 100, 360);
    }

    void DrawHands()
    {
        glColor3f(m_handColor.red, m_handColor.green, m_handColor.blue);

        glPushMatrix();
        glRotatef(-10, 0, 0, 1);
        FillEllipse(1100, 750, 100, 200, 360);
        glPopMatrix();

        glPushMatrix();
        glRotatef(10, 0, 0, 1);
        FillEllipse(600, 450, 100, 200, 360);
        glPopMatrix();
    }

    void DrawEars()
    {
        glColor3f(m_earColor.red, m_earColor.green, m_earColor.blue);
        FillEllipse(700, 160, 100, 200, 360);
        FillEllipse(1000, 160, 100, 200, 360);
    }

    void FillEllipse(
        float xCenter, float yCenter, float rx, float ry, int points)
    {
        const float step = 2 * std::numbers::pi / points;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2d(xCenter, yCenter);
        for (float angle = 0; angle <= 2 * std::numbers::pi; angle += step)
        {
            float a = (fabsf(angle - 2 * std::numbers::pi) < 1e-5) ? 0 : angle;
            const float dx = rx * cosf(a);
            const float dy = ry * sinf(a);
            glVertex2f(dx + xCenter, dy + yCenter);
        }
        glEnd();
    }
};

int main() {
    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

    //класс окна добавить как из лекции
    window = glfwCreateWindow(1920, 1080, "Draw Krosh", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    Krosh krosh({ 100, 40 }, 150, 150, { 0, 0.9, 0.9 }, { 0, 1, 1 }, { 0, 1, 1 }, { 0, 1, 1 });

    while (!glfwWindowShouldClose(window)) 
    {
        glClear(GL_COLOR_BUFFER_BIT);

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1);

        krosh.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
