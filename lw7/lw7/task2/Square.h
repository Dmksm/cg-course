#pragma once
#include "./IDrawable.h"

#include <GL/glew.h>

class Square : public IDrawable
{
private:
	void Draw()override
	{
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
        glBegin(GL_QUADS);
        {
            glVertex2f(-1.0, -1.0);
            glVertex2f(1.0, -1.0);
            glVertex2f(1.0, 1.0);
            glVertex2f(-1.0, 1.0);
        }
        glEnd();
        glDisableVertexAttribArray(0);
	}
};
