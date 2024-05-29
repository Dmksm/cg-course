#pragma once
#include "TriangleMesh.h"

class CShape
{
public:
	CShape(std::vector<Vertex> vertices, std::vector<Face> faces);

	std::vector<Vertex> GetVertices()const;
	std::vector<Face> GetFaces()const;

private:
	std::vector<Vertex> m_vertices;
	std::vector<Face> m_faces;
};