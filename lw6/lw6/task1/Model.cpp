#include "../libgl/Vector3.h"
#include "../libgl/GdiPlusInitializer.h"
#include "../libgl/TextureLoader.h"

#include "../libgl/stdafx.h"
#include "../libgl/Graphics.h"
#include "../libgl/Utils.h"
#include "../libgl/Texture.h"
#include "Model.h"

CModel::CModel(): m_displayList(0)
{
}

void CModel::SetModel(
	std::string cottageModelName,
	std::string defenderModelName,
	std::string treeModelName,
	std::string woodenSwingModelName,
	std::string groundModelName,
	std::string xpanderCarModelName
)
{
	float rotationMatrix1[16] = {
		1, 0, 0, 0,
		0, 0, -1, 0,
		0, 1, 0, 0,
		0, 0, 0, 1
	};
	float translationMatrix1[16] = {
		1, 0, 0, -15,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
	float scaleMatrix1[16] = {
		0.01, 0, 0, 0,
		0, 0.01, 0, 0,
		0, 0, 0.01, 0,
		0, 0, 0, 1
	};
	Load3DSModel(cottageModelName, rotationMatrix1, translationMatrix1, scaleMatrix1);
	float rotationMatrix2[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	float translationMatrix2[16] = {
		1, 0, 0, -7,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
	float scaleMatrix2[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	Load3DSModel(defenderModelName, rotationMatrix2, translationMatrix2, scaleMatrix2);
	float rotationMatrix3[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	float translationMatrix3[16] = {
		1, 0, 0, 5,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
	float scaleMatrix3[16] = {
		0.06, 0, 0, 0,
		0, 0.06, 0, 0,
		0, 0, 0.06, 0,
		0, 0, 0, 1
	};
	Load3DSModel(treeModelName, rotationMatrix3, translationMatrix3, scaleMatrix3);
	float rotationMatrix4[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	float translationMatrix4[16] = {
		1, 0, 0, 0,
		0, 1, 0, 10,
		0, 0, 1, 0.5,
		0, 0, 0, 1,
	};
	float scaleMatrix4[16] = {
		1.3, 0, 0, 0,
		0, 1.3, 0, 0,
		0, 0, 1.3, 0,
		0, 0, 0, 1
	};
	Load3DSModel(woodenSwingModelName, rotationMatrix4, translationMatrix4, scaleMatrix4);
	float rotationMatrix5[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	float translationMatrix5[16] = {
		1, 0, 0, 30,
		0, 1, 0, 0,
		0, 0, 1, -12,
		0, 0, 0, 1,
	};
	float scaleMatrix5[16] = {
		0.01, 0, 0, 0,
		0, 0.01, 0, 0,
		0, 0, 0.01, 0,
		0, 0, 0, 1
	};
	Load3DSModel(groundModelName, rotationMatrix5, translationMatrix5, scaleMatrix5);
	float rotationMatrix6[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	float translationMatrix6[16] = {
		1, 0, 0, -2,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
	float scaleMatrix6[16] = {
		0.05, 0, 0, 0,
		0, 0.05, 0, 0,
		0, 0, 0.05, 0,
		0, 0, 0, 1
	};
	Load3DSModel(xpanderCarModelName, rotationMatrix6, translationMatrix6, scaleMatrix6);
}

void CModel::ProcessMesh(aiMesh* mesh, ModelInfo& model)
{
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i) 
	{
		aiVector3D vertex = mesh->mVertices[i];
		aiVector3D normal = mesh->mNormals[i];
		aiVector3D texCoord = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : aiVector3D(0,0,0);

		Vertex v;
		v.x = vertex.x;
		v.y = vertex.y;
		v.z = vertex.z;

		v.nx = normal.x;
		v.ny = normal.y;
		v.nz = normal.z;

		v.u = texCoord.x;
		v.v = texCoord.y;

		aiVector3D scaledVertex = aiVector3D(
			model.scaleMatrix[0] * vertex.x + model.scaleMatrix[1] * vertex.y + model.scaleMatrix[2] * vertex.z + model.scaleMatrix[3],
			model.scaleMatrix[4] * vertex.x + model.scaleMatrix[5] * vertex.y + model.scaleMatrix[6] * vertex.z + model.scaleMatrix[7],
			model.scaleMatrix[8] * vertex.x + model.scaleMatrix[9] * vertex.y + model.scaleMatrix[10] * vertex.z + model.scaleMatrix[11]
		);

		aiVector3D rotatedVertex = aiVector3D(
			model.rotationMatrix[0] * scaledVertex.x + model.rotationMatrix[1] * scaledVertex.y + model.rotationMatrix[2] * scaledVertex.z,
			model.rotationMatrix[4] * scaledVertex.x + model.rotationMatrix[5] * scaledVertex.y + model.rotationMatrix[6] * scaledVertex.z,
			model.rotationMatrix[8] * scaledVertex.x + model.rotationMatrix[9] * scaledVertex.y + model.rotationMatrix[10] * scaledVertex.z
		);

		aiVector3D translatedVertex = aiVector3D(
			rotatedVertex.x + model.translationMatrix[3],
			rotatedVertex.y + model.translationMatrix[7],
			rotatedVertex.z + model.translationMatrix[11]
		);

		v.x = translatedVertex.x;
		v.y = translatedVertex.y;
		v.z = translatedVertex.z;

		model.vertices.push_back(v);
	}
}

void CModel::ProcessNode(aiNode* node, const aiScene* scene, ModelInfo& model) 
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i) 
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, model);
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i) 
	{
		ProcessNode(node->mChildren[i], scene, model);
	}
}

void CModel::Load3DSModel(const std::string& filename, const float rotationMatrix[16], const float translationMatrix[16], const float scaleMatrix[16]) 
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
	{
		std::cerr << "Error loading 3DS file: " << importer.GetErrorString() << std::endl;
		return;
	}

	ModelInfo model;
	memcpy(model.rotationMatrix, rotationMatrix, sizeof(float) * 16);
	memcpy(model.translationMatrix, translationMatrix, sizeof(float) * 16);
	memcpy(model.scaleMatrix, scaleMatrix, sizeof(float) * 16);
	ProcessNode(scene->mRootNode, scene, model);
	m_models.push_back(model);
}

void CModel::DrawModel()
{
	for (const auto& model : m_models)
	{
		glBegin(GL_TRIANGLES);
		for (const auto& vertex : model.vertices) 
		{
			glNormal3f(vertex.nx, vertex.ny, vertex.nz);
			glTexCoord2f(vertex.u, vertex.v);
			glVertex3f(vertex.x, vertex.y, vertex.z);
		}
		glEnd();
	}
}

CModel::~CModel()
{
	if (m_displayList)
	{
		glDeleteLists(m_displayList, 1);
	}
}

void CModel::Draw()
{
	if (!m_displayList)
	{
		m_displayList = glGenLists(1);
		glNewList(m_displayList, GL_COMPILE);

		DrawModel();

		glEndList();
	}
	glCallList(m_displayList);
}
