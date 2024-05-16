#pragma once
#define _USE_MATH_DEFINES

#include <vector>
#include <chrono>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "./IDrawable.h"

class MorphObject : public IDrawable
{
public:
	MorphObject(int density, const unsigned int& VBO, const unsigned int& VAO)
		: m_VBO(VBO)
		, m_VAO(VAO)
		, m_density(density)
	{
	}

private:
	void Draw()override
	{
		UpdatePhase();

		glUniform1f(0, (sinf(m_phase) + 1) / 2);
		glBindVertexArray(m_VAO);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_QUADS);
		float size = 2.0 / m_density;

		for (float y = -1; y < 1; y += size)
		{
			for (float x = -1; x < 1; x += size)
			{
				glVertex3f(x, y, 0);
				glVertex3f(x + size, y, 0);
				glVertex3f(x + size, y + size, 0);
				glVertex3f(x, y + size, 0);
			}
		}
		glEnd();
		
		glBindVertexArray(0);
	}

	void Init()override
	{
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void UpdatePhase()
	{
		auto elapsed = m_previousTime - m_currentTime;

		float delta = elapsed.count() * m_ANIMATION_SPEED;

		m_phase = fmodf(
			float(m_phase + delta * 2 * M_PI / 0.001f),
			float(2 * M_PI)
		);
	}

	inline static const float m_ANIMATION_SPEED = 0.005;

	std::chrono::steady_clock::time_point m_currentTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point m_previousTime = std::chrono::steady_clock::now();

	std::vector<float> m_vertices;
	float m_phase;
	int m_density;
	const unsigned int& m_VBO, m_VAO;
};