#pragma once
#define _USE_MATH_DEFINES

#include "./IDrawable.h"
#include <math.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <glm/ext.hpp>

class Line : public IDrawable
{
private:
	void Draw() override
	{
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
		glBegin(GL_LINE_STRIP);
        const float step = M_PI / 1000.f;
        for (float x = 0; x < 2 * M_PI; x += step)
        {
            glVertex2f(x, 0);
        }
        glEnd();
        glDisableVertexAttribArray(0);
	}
};