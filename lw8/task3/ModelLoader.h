#pragma once
#include "TriangleMesh.h"
#include "SimpleMaterial.h"

class CModelLoader
{
public:
    bool Load(const std::string& fileName);

    std::vector<Vertex> GetVertices()const;
    std::vector<Face> GetFaces()const; 
    const std::vector<CSimpleMaterial>& GetMaterials()const;

private:
    void ProcessNode(aiNode* node, const aiScene* scene);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
    CSimpleMaterial LoadMaterial(aiMaterial* material);
    void ClearModelInfo();

    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;
    std::vector<CSimpleMaterial> m_materials;
};