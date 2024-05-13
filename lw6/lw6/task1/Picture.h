#pragma once

#include "../libgl/Material.h"
#include "../libgl/Texture.h"
#include "Model.h"

class CPicture
{
public:
	CPicture(
		std::string const& cottageModelName,
		std::string const& defenderModelName,
		std::string const& treeModelName,
		std::string const& woodenSwingModelName,
		std::string const& groundModelName,
		std::string const& xpanderCarModelName,
		bool animate = false);

	void Animate(float timeDelta);

	void Draw();

	void SetInclinationAngle(float inclinationAngle);

	void SetAnimation(bool animate);

	void SetRotationSpeed(float rotationSpeed);

private:
	CModel m_model;
	float m_rotationAngle;
	float m_inclinationAngle;
	float m_rotationSpeed;
	std::string m_cottageModelName;
	std::string m_defenderModelName;
	std::string m_treeModelName;
	std::string m_woodenSwingModelName;
	std::string m_groundModelName;
	std::string m_xpanderCarModelName;
	bool m_animate;
	bool m_initialized;
};
