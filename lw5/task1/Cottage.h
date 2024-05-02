#pragma once

#include "../libgl/Material.h"
#include "../libgl/Texture.h"
#include "House.h"

class CCottage
{
public:
	CCottage(
		std::wstring const& wallTextureName,
		std::wstring const& roofTextureName,
		std::wstring const& garageTextureName,
		std::wstring const& whiteWallWithWindowTextureName,
		std::wstring const& wallWithDoorTextureName,
		std::wstring const& grassTextureName,
		float radius = 1, unsigned slices = 50,
		unsigned stacks = 25);

	// Анимируем планету (вращение вокруг своей оси)
	void Animate(float timeDelta);

	// рисуем планету
	void Draw();

	// Угол наклона оси вращения
	void SetInclinationAngle(float inclinationAngle);

	void SetAnimation(bool animate);

	// Скорость вращения вокруг своей оси
	void SetRotationSpeed(float rotationSpeed);

private:
	CHouse m_house; // сфера, аппроксимирующая поверхность планеты
	CMaterial m_material; // материал планеты
	float m_rotationAngle; // угол поворота вокруг своекй оси
	float m_inclinationAngle; // угол наклона оси вращения
	float m_rotationSpeed; // Скорость вращения вокруг собсвтенной оси
	mutable CTexture2D m_texture; // текстура планеты
	mutable CTexture2D m_wallTexture; // текстура планеты
	mutable CTexture2D m_garageTexture; // текстура планеты
	std::wstring m_roofTextureName; // имя файла с текстурой
	std::wstring m_wallTextureName; // имя файла с текстурой
	std::wstring m_garageTextureName; // имя файла с текстурой
	std::wstring m_whiteWallWithWindowTextureName; // имя файла с текстурой
	std::wstring m_wallWithDoorTextureName; // имя файла с текстурой
	std::wstring m_grassTextureName; // имя файла с текстурой
	bool m_animate;
	bool m_initialized;
};
