#include "Planet.h"
#include "../libgl/TextureLoader.h"

CPlanet::CPlanet(
	std::wstring const& wallTextureName,
	std::wstring const& roofTextureName,
	std::wstring const& garageTextureName,
	std::wstring const& whiteWallWithWindowTextureName,
	std::wstring const& wallWithDoorTextureName,
	std::wstring const& grassTextureName,
	float radius,
	unsigned slices,
	unsigned stacks)
	: m_sphere(radius, slices, stacks)
	, m_roofTextureName(roofTextureName)
	, m_wallTextureName(wallTextureName)
	, m_garageTextureName(garageTextureName)
	, m_whiteWallWithWindowTextureName(whiteWallWithWindowTextureName)
	, m_wallWithDoorTextureName(wallWithDoorTextureName)
	, m_grassTextureName(grassTextureName)
	, m_rotationAngle(0)
	, m_inclinationAngle(0)
	, m_rotationSpeed(0)
	, m_animate(true)
	, m_initialized(false)
{
	m_material.SetDiffuse(1, 1, 1);
	m_material.SetShininess(50);
	m_material.SetSpecular(1, 1, 1);
}

void CPlanet::SetAnimation(bool animate)
{
	m_animate = animate;
}

// Изменяем угол вращения планеты вокруг своей оси
void CPlanet::Animate(float timeDelta)
{
	if (m_animate)
	{
		m_rotationAngle = fmodf(m_rotationAngle + m_rotationSpeed * timeDelta, 360);
	}
}

void CPlanet::SetInclinationAngle(float inclinationAngle)
{
	m_inclinationAngle = inclinationAngle;
}

void CPlanet::SetRotationSpeed(float rotationSpeed)
{
	m_rotationSpeed = rotationSpeed;
}

void CPlanet::Draw()
{
	if (!m_initialized)
	{
		// Загружаем текстуру при первом вызове метода Draw()
		CTextureLoader loader;
		m_sphere.SetTextures(
			loader.LoadTexture2D(m_wallTextureName),
			loader.LoadTexture2D(m_roofTextureName),
			loader.LoadTexture2D(m_garageTextureName),
			loader.LoadTexture2D(m_whiteWallWithWindowTextureName),
			loader.LoadTexture2D(m_wallWithDoorTextureName),
			loader.LoadTexture2D(m_grassTextureName)
		);
		m_initialized = true;
	}
	// Активизируем текстуру и материал планеты
	glEnable(GL_TEXTURE_2D);
	m_material.Activate();

	// Сохраняем текущую матрицу
	// (предполагается работа с матрицей modelview)
	// и поворачиваем планету
	// (сначала вокруг оси вращения, а затем наклоняем ось)
	glPushMatrix();
	glRotatef(m_inclinationAngle, 1, 0, 0);
	glRotatef(m_rotationAngle, 0, 0, 1);

	// рисуем сферу
	m_sphere.Draw();

	// восстанавливаем текущую матрицу
	glPopMatrix();
}
