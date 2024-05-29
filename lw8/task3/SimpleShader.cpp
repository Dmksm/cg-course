#include "stdafx.h"
#include "SimpleShader.h"
#include "Vector4.h"
#include "Scene.h"
#include "ShadeContext.h"
#include "ILightSource.h"
#include "VectorMath.h"

CSimpleShader::CSimpleShader(CSimpleMaterial const& material, CVector3d cameraPosition)
:m_material(material)
,m_cameraPos(cameraPosition)
{
}
void CSimpleShader::SetMaterial(CSimpleMaterial const& material)
{
	m_material = material;
}

CVector4f CSimpleShader::Shade(CShadeContext const & shadeContext)const
{
    CScene const& scene = shadeContext.GetScene();
    CVector4f shadedColor = m_material.GetAmbientColor();

    const size_t numLights = scene.GetLightsCount();
    for (size_t i = 0; i < numLights; ++i) {
        ILightSource const& light = scene.GetLight(i);

        CVector3d lightDirection = light.GetDirectionFromPoint(shadeContext.GetSurfacePoint());
        double lightIntensity = light.GetIntensityInDirection(-lightDirection);

        CVector3d const& n = shadeContext.GetSurfaceNormal();

        double nDotL = Max(Dot(n, Normalize(lightDirection)), 0.0);

        CVector4f diffuseColor = static_cast<float>(nDotL * lightIntensity) * light.GetDiffuseIntensity() * m_material.GetDiffuseColor();
        
        CVector3d viewDirection = Normalize((m_cameraPos - shadeContext.GetSurfacePoint()));
        CVector3d reflectDirection = (n * 2.0 * Dot(n, lightDirection)) - lightDirection;
        double specularIntensity = std::pow(Max(Dot(viewDirection, Normalize(reflectDirection)), 0.0), m_material.GetShininess());
        CVector4f specularColor = static_cast<float>(specularIntensity * lightIntensity) * light.GetSpecularIntensity() * m_material.GetSpecularColor();

        shadedColor += diffuseColor + specularColor;
    }

    return shadedColor;
}