#pragma once
#include "Shape.h"

class CTetrahedron: public CShape
{
public:
	CTetrahedron(
		std::vector<Vertex> vertices = {
			CVector3d(-1, 0, 1),
			CVector3d(1, 0, 1),
			CVector3d(0, 0, -1),
			CVector3d(0, 2, 0),
		},
		std::vector<Face> faces = {
			{ 0, 2, 1 },
			{ 3, 0, 1 },
			{ 3, 1, 2 },
			{ 3, 2, 0 },
		}
	);
};