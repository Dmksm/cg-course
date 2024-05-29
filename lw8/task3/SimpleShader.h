#pragma once
#include "IShader.h"
#include "SimpleMaterial.h"

class CSimpleShader :
	public IShader
{
public:
	CSimpleShader(CSimpleMaterial const& material = CSimpleMaterial(), CVector3d cameraPosition = CVector3d(0, 1, 0));

	void SetMaterial(CSimpleMaterial const& material);

	virtual CVector4f Shade(CShadeContext const & shadeContext)const;
private:
	CSimpleMaterial m_material;
	CVector3d m_cameraPos;
};
