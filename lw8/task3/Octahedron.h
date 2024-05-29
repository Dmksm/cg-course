#pragma once
#include "Shape.h"

class COctahedron : public CShape
{
public:
	COctahedron(
		std::vector<Vertex> vertices = {
			CVector3d(0, -1, 0),
			CVector3d(+1, 0, 0),
			CVector3d(0, 0, 1),
			CVector3d(0, 0, -1),
			CVector3d(0, 1, 0),
			CVector3d(-1, 0, 0),
		},
		std::vector<Face> faces = {
			{ 0, 1, 2 },
			{ 0, 3, 1 },
			{ 2, 1, 4 },
			{ 3, 4, 1 },
			{ 2, 4, 5 },
			{ 5, 4, 3 },
			{ 0, 2, 5 },
			{ 0, 5, 3 },
		}
	);
};