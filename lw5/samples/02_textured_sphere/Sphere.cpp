#include "../libgl/Vector3.h"
#include "../libgl/GdiPlusInitializer.h"
#include "../libgl/TextureLoader.h"

#include "../libgl/stdafx.h"
#include "../libgl/Graphics.h"
#include "../libgl/Utils.h"
#include "../libgl/Texture.h"
#include "Sphere.h"

CSphere::CSphere(
	float radius,
	unsigned slices,
	unsigned stacks)
	: m_radius(radius)
	, m_slices(slices)
	, m_stacks(stacks)
	, m_displayList(0)
{
}

void CSphere::SetTextures(
	GLuint wallTexture,
	GLuint roofTexture,
	GLuint garageTexture,
	GLuint whiteWallWithWindowTextureName,
	GLuint wallWithDoorTextureName,
	GLuint grassTextureName
)
{
	m_wallTexture.Attach(wallTexture);
	m_roofTexture.Attach(roofTexture);
	m_garageTexture.Attach(garageTexture);
	m_whiteWallWithWindowTexture.Attach(whiteWallWithWindowTextureName);
	m_wallWithDoorTexture.Attach(wallWithDoorTextureName);
	m_grassTexture.Attach(grassTextureName);
}

void CSphere::DrawSphere(GLfloat size) const
{
	struct CubeFace
	{
		unsigned char vertex0;
		unsigned char vertex1;
		unsigned char vertex2;
		unsigned char vertex3;
		GLfloat tex0s, tex0t;
		GLfloat tex1s, tex1t;
		GLfloat tex2s, tex2t;
		GLfloat tex3s, tex3t;
		CTexture2D const& texture;
	};

	static const float vertices[100][3] = {
		{ -1.0, -1, -1 }, // 0
		{ +1.0, -1, -1 }, // 1
		{ +1.0, +1, -1 }, // 2
		{ -1.0, +1, -1 }, // 3

		{ -0.9, -0.9, -1 }, // 4
		{ -0.9, 0.25, -1 }, // 5
		{ 0.25, 0.25, -1 }, // 6
		{ 0.25, -0.9, -1 }, // 7

		{ -0.9, -0.9, 0}, // 8
		{ -0.9, 0.25, 0 }, // 9
		{ 0.25, 0.25, 0 }, // 10
		{ 0.25, -0.9, 0 }, // 11

		{ -0.4, -0.9, 0.95}, // 12
		{ -0.4, 0.25, 0.95}, // 13
		{ -0.25, 0.25, 0.95}, // 14
		{ -0.25, -0.9, 0.95}, // 15

		{ -0.4, -0.9, 1}, // 16
		{ -0.4, 0.25, 1}, // 17
		{ -0.25, 0.25, 1}, // 18
		{ -0.25, -0.9, 1}, // 19

		{ 0.25, -0.7, -1}, // 20
		{ 0.25, 0.05, -1}, // 21
		{ 0.9, 0.05, -1}, // 22
		{ 0.9, -0.7, -1}, // 23

		{ 0.25, -0.7, -0.1}, // 24
		{ 0.25, 0.05, -0.1}, // 25
		{ 0.9, 0.05, -0.1}, // 26
		{ 0.9, -0.7, -0.1}, // 27
	};

	static const CubeFace faces[] = {
		// ground
		{ 0, 1, 2, 3, 0, 1, 0, 0, 1, 0, 1, 1, m_grassTexture},

		//wall 
		{ 4, 8, 9, 5, 0, 1, 0, 0, 1, 0, 1, 1, m_whiteWallWithWindowTexture},
		{ 5, 9, 10, 6, 0, 1, 0, 0, 1, 0, 1, 1, m_wallWithDoorTexture},
		{ 6, 10, 11, 7, 0, 1, 0, 0, 1, 0, 1, 1, m_wallTexture},
		{ 7, 11, 8, 4, 0, 1, 0, 0, 1, 0, 1, 1, m_whiteWallWithWindowTexture},

		{ 9, 13, 14, 10, 0, 1, 0, 0, 1, 0, 1, 1, m_wallTexture},
		{ 8, 11, 15, 12, 0, 1, 0, 0, 1, 0, 1, 1, m_wallTexture},

		//roof
		{ 9, 8, 12, 13, 1, 1, 0, 1, 0, 0, 1, 0, m_roofTexture},
		{ 10, 14, 15, 11, 0, 1, 0, 0, 1, 0, 1, 1, m_roofTexture},
		{ 12, 15, 14, 13, 0, 1, 0, 0, 1, 0, 1, 1, m_roofTexture},

		//garage
		{ 21, 25, 26, 22, 0, 1, 0, 0, 1, 0, 1, 1, m_wallTexture},
		{ 23, 27, 24, 20, 0, 1, 0, 0, 1, 0, 1, 1, m_wallTexture},
		{ 22, 26, 27, 23, 0, 1, 0, 0, 1, 0, 1, 1, m_garageTexture},
		{ 26, 25, 24, 27, 0, 1, 0, 0, 1, 0, 1, 1, m_roofTexture},
	};

	static unsigned const faceCount = sizeof(faces) / sizeof(*faces);

	for (unsigned faceIndex = 0; faceIndex < faceCount; ++faceIndex)
	{
		CubeFace const& face = faces[faceIndex];

		face.texture.Bind();

		// Рисуем 4 вершины квадрата
		glBegin(GL_QUADS);
		{
			CVector3f v0(vertices[face.vertex0]);
			v0 *= size;

			CVector3f v1(vertices[face.vertex1]);
			v1 *= size;

			CVector3f v2(vertices[face.vertex2]);
			v2 *= size;

			CVector3f v3(vertices[face.vertex3]);
			v3 *= size;

			CVector3f v01 = v1 - v0;
			CVector3f v02 = v2 - v0;
			CVector3f normal = Cross(v01, v02);
			normal.Normalize();
			glNormal3fv(normal);

			glTexCoord2f(face.tex0s, face.tex0t);
			glVertex3fv(v0);
			glTexCoord2f(face.tex1s, face.tex1t);
			glVertex3fv(v1);
			glTexCoord2f(face.tex2s, face.tex2t);
			glVertex3fv(v2);
			glTexCoord2f(face.tex3s, face.tex3t);
			glVertex3fv(v3);
		}
		glEnd();
	}
}

/*
Рисуем сферу при помощи последовательности triangle strip-ов
Каждая лента соответствует линии параллелей
*/
//void CSphere::DrawSphere() const
//{
//	// шаг по параллелям
//	const float stackStep = static_cast<float>(std::numbers::pi / m_stacks);
//
//	// шаг по меридианам
//	const float sliceStep = static_cast<float>(2 * std::numbers::pi / m_slices);
//
//	// начальный угол по параллелям
//	for (unsigned stack = 0; stack < m_stacks; ++stack)
//	{
//		float stackAngle = static_cast<float>(std::numbers::pi * 0.5 - stack * stackStep);
//		float nextStackAngle = stackAngle - stackStep;
//
//		const float stackRadius = m_radius * cosf(stackAngle);
//		const float nextStackRadius = m_radius * cosf(nextStackAngle);
//		const float z0 = m_radius * sinf(stackAngle);
//		const float z1 = m_radius * sinf(nextStackAngle);
//
//		glBegin(GL_TRIANGLE_STRIP);
//		// цикл по меридианам
//		for (unsigned slice = 0; slice <= m_slices; ++slice)
//		{
//			// вычисляем угол, текущего меридиана
//			float sliceAngle = (slice != m_slices) ? slice * sliceStep : 0;
//
//			// Вычисляем координаты на текущей параллели
//			float x0 = stackRadius * cosf(sliceAngle);
//			float y0 = stackRadius * sinf(sliceAngle);
//			// вычисляем и задаем вектор нормали, текстурные координаты
//			// и положение вершины в пространстве
//			CVector3f normal0(x0, y0, z0);
//			normal0.Normalize();
//			glNormal3fv(normal0);
//			glTexCoord2f(float(slice) / m_slices, float(stack) / m_stacks);
//			glVertex3f(x0, y0, z0);
//
//			float x1 = nextStackRadius * cosf(sliceAngle);
//			float y1 = nextStackRadius * sinf(sliceAngle);
//			CVector3f normal1(x1, y1, z1);
//			normal1.Normalize();
//			glNormal3fv(normal1);
//
//			glTexCoord2f(float(slice) / m_slices, float(stack + 1) / m_stacks);
//			glVertex3f(x1, y1, z1);
//		}
//		glEnd();
//	}
//}

CSphere::~CSphere()
{
	if (m_displayList)
	{
		glDeleteLists(m_displayList, 1);
	}
}

void CSphere::Draw() const
{
	if (!m_displayList)
	{
		m_displayList = glGenLists(1);
		glNewList(m_displayList, GL_COMPILE);

		DrawSphere(1);

		glEndList();
	}
	glCallList(m_displayList);
}
