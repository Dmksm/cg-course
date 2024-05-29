#include "stdafx.h"
#include "Tetrahedron.h"

CTetrahedron::CTetrahedron(std::vector<Vertex> vertices, std::vector<Face> faces) 
	: CShape(vertices, faces) 
{};