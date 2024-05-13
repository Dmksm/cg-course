#include "Picture.h"
#include "../libgl/TextureLoader.h"

CPicture::CPicture(
	std::string const& cottageModelName,
	std::string const& defenderModelName,
	std::string const& treeModelName,
	std::string const& woodenSwingModelName,
	std::string const& groundModelName,
	std::string const& xpanderCarModelName,
	bool animate)
	: m_model()
	, m_cottageModelName(cottageModelName)
	, m_defenderModelName(defenderModelName)
	, m_treeModelName(treeModelName)
	, m_woodenSwingModelName(woodenSwingModelName)
	, m_groundModelName(groundModelName)
	, m_xpanderCarModelName(xpanderCarModelName)
	, m_rotationAngle(0)
	, m_inclinationAngle(0)
	, m_rotationSpeed(0)
	, m_animate(animate)
	, m_initialized(false)
{
}

void CPicture::SetAnimation(bool animate)
{
	m_animate = animate;
}

void CPicture::Animate(float timeDelta)
{
	if (m_animate)
	{
		m_rotationAngle = fmodf(m_rotationAngle + m_rotationSpeed * timeDelta, 360);
	}
}

void CPicture::SetInclinationAngle(float inclinationAngle)
{
	m_inclinationAngle = inclinationAngle;
}

void CPicture::SetRotationSpeed(float rotationSpeed)
{
	m_rotationSpeed = rotationSpeed;
}

void CPicture::Draw()
{
	if (!m_initialized)
	{
		CTextureLoader loader;
		m_model.SetModel(
			m_cottageModelName,
			m_defenderModelName,
			m_treeModelName,
			m_woodenSwingModelName,
			m_groundModelName,
			m_xpanderCarModelName
		);
		m_initialized = true;
	}

	// Сохраняем текущую матрицу
	// (предполагается работа с матрицей modelview)
	// и поворачиваем модель
	// (сначала вокруг оси вращения, а затем наклоняем ось)
	glPushMatrix();
	glRotatef(m_inclinationAngle, 1, 0, 0);
	glRotatef(m_rotationAngle, 0, 0, 1);

	// рисуем модель
	m_model.Draw();

	// восстанавливаем текущую матрицу
	glPopMatrix();
}
