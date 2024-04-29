#pragma once
#include "stdafx.h"

class SnubDodecahedron
{
public:
	explicit SnubDodecahedron(float size = 1);
	void Draw() const;

	unsigned GetSideColorsCount()const;
	void SetSideColor(unsigned index, const glm::vec4& color);
	void SetPentagonsColor(glm::vec4 color);
	void SetSpecularColor(glm::vec4 color);
	void SetShininess(float shininess);

private:
	float m_size;
	
	glm::vec4 m_pentagonsColor = { 0.5,0.5,0.5,0 };
	const static unsigned m_colorsCount = 242;
	glm::vec4 m_sideColors[m_colorsCount];
	glm::vec4 m_specularColor = { 0, 0, 0, 1 };
	float m_shininess = 1;

	void AddVertices(const GLfloat* color, const std::vector<unsigned char> facePoints, const float vertices[60][3]) const;
};
