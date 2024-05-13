#pragma once
#include <vector>
#include <string>
#include "common_inc.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

class CModel
{
public:
	CModel();
	~CModel();

	void Draw();
	void SetModel(
		std::string cottageModelName,
		std::string defenderModelName,
		std::string treeModelName,
		std::string woodenSwingModelName,
		std::string groundModelName,
		std::string xpanderCarModelName
	);
private:
	void DrawModel();

	struct Vertex {
		float x, y, z;
		float nx, ny, nz;
		float u, v;
	};

	struct ModelInfo {
		std::vector<Vertex> vertices;
		float rotationMatrix[16];
		float translationMatrix[16];
		float scaleMatrix[16];
	};

	std::vector<ModelInfo> m_models;
	mutable GLuint m_displayList;

	void ProcessMesh(aiMesh* mesh, ModelInfo& model);
	void ProcessNode(aiNode* node, const aiScene* scene, ModelInfo& model);
	void Load3DSModel(const std::string& filename, const float rotationMatrix[16], const float translationMatrix[16], const float scaleMatrix[16]);
};
