#pragma once

#include "common_inc.h"

class CHouse
{
public:
	CHouse(float radius, unsigned slices, unsigned stacks);
	~CHouse();

	void Draw() const;
	void SetTextures(
		GLuint wallTexture,
		GLuint roofTexture,
		GLuint garageTexture,
		GLuint whiteWallWithWindowTextureName,
		GLuint wallWithDoorTextureName,
		GLuint grassTextureName
	);
private:
	void DrawHouse(GLfloat size) const;

	// Идентификатор дисплейного списка, выполняющего рисование сферы
	mutable GLuint m_displayList;
	float m_radius; // радиус
	unsigned m_slices; // количество меридианов
	unsigned m_stacks; // количество параллелей
	CTexture2D m_wallTexture;
	CTexture2D m_roofTexture;
	CTexture2D m_garageTexture;
	CTexture2D m_whiteWallWithWindowTexture;
	CTexture2D m_wallWithDoorTexture;
	CTexture2D m_grassTexture;
};
