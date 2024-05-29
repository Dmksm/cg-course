#include "stdafx.h"
#include "ModelLoader.h"

std::vector<Vertex> CModelLoader::GetVertices()const
{
    return m_vertices;
}

std::vector<Face> CModelLoader::GetFaces()const
{
    return m_faces;
}


const std::vector<CSimpleMaterial>& CModelLoader::GetMaterials()const
{
    return m_materials;
}

void CModelLoader::ClearModelInfo()
{
    m_vertices.clear();
    m_faces.clear();
}

bool CModelLoader::Load(const std::string& fileName) 
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cerr << "Error loading 3DS file: " << importer.GetErrorString() << std::endl;
        return false;
    }

    ClearModelInfo();

    ProcessNode(scene->mRootNode, scene);
    return true;
}

void CModelLoader::ProcessNode(aiNode* node, const aiScene* scene) 
{
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) 
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene);
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) 
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

void CModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) 
    {
        CVector3d position(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        CVector3d normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

        Vertex vertex(position, normal);
        m_vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) 
    {
        aiFace& ai_face = mesh->mFaces[i];
        if (ai_face.mNumIndices != 3) 
        {
            continue;
        }

        Face face(ai_face.mIndices[0], ai_face.mIndices[1], ai_face.mIndices[2]);
        m_faces.push_back(face);
    }

    if (mesh->mMaterialIndex >= 0) 
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        CSimpleMaterial simpleMaterial = LoadMaterial(material);
        m_materials.push_back(simpleMaterial);
    }
}

CSimpleMaterial CModelLoader::LoadMaterial(aiMaterial* material) 
{
    CSimpleMaterial simpleMaterial;
    aiColor4D color;
    float shininess;

    if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color)) 
    {
        simpleMaterial.SetDiffuseColor(CVector4f(color.r, color.g, color.b, color.a));
    }
    if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color))
    {
        simpleMaterial.SetAmbientColor(CVector4f(color.r, color.g, color.b, color.a));
    }
    if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color)) 
    {
        simpleMaterial.SetSpecularColor(CVector4f(color.r, color.g, color.b, color.a));
    }
    if (AI_SUCCESS == aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess)) 
    {
        simpleMaterial.SetShininess(shininess);
    }

    return simpleMaterial;
}
