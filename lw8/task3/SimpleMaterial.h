#pragma once

#include "Vector4.h"

/*
Простейший материал, для которого задан только лишь диффузный цвет
*/
class CSimpleMaterial
{
public:
	CSimpleMaterial(void)
	{}

	float GetShininess()const
	{
		return m_shininess;
	}

	CVector4f const& GetDiffuseColor()const
	{
		return m_diffuseColor;
	}

	CVector4f const& GetAmbientColor()const
	{
		return m_ambientColor;
	}

	CVector4f const& GetSpecularColor()const
	{
		return m_specularColor;
	}

	void SetShininess(float shininess)
	{
		m_shininess = shininess;
	}

	void SetDiffuseColor(CVector4f const& diffuseColor)
	{
		m_diffuseColor = diffuseColor;
	}

	void SetAmbientColor(CVector4f const& ambientColor)
	{
		m_ambientColor = ambientColor;
	}

	void SetSpecularColor(CVector4f const& specularColor)
	{
		m_specularColor = specularColor;
	}

private:
	CVector4f m_diffuseColor;
	CVector4f m_ambientColor;
	CVector4f m_specularColor;
	float m_shininess = 32;
};
