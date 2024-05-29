#pragma once
#include "Shape.h"

class CIcosahedron : public CShape
{
public:
	CIcosahedron(
		std::vector<Vertex> vertices = {
			CVector3d(1.989, 1.6, -2.709),
			CVector3d(-1.949, 1.6, -2.709),
			CVector3d(0.02, -1.812, -3.349),
			CVector3d(3.205, -1.812, -1.035),
			CVector3d(3.205, 1.6, 1.035),
			CVector3d(0.02, 3.674, 0),
			CVector3d(-3.165, 1.6, 1.035),
			CVector3d(-3.165, -1.812, -1.035),
			CVector3d(0.02, -3.886, 0),
			CVector3d(1.989, -1.812, 2.709),
			CVector3d(-1.989, -1.812, 2.709),
			CVector3d(0.02, 1.6, 3.349),
		},
		std::vector<Face> faces = {
			{ 0, 2, 1 },
			{ 3, 2, 0 },
			{ 3, 0, 4 },
			{ 4, 0, 5 },
			{ 0, 1, 5 },
			{ 1, 6, 5 },
			{ 1, 7, 6 },
			{ 1, 2, 7 },
			{ 2, 8, 7 },
			{ 2, 3, 8 },
			{ 3, 4, 9 },
			{ 4, 11, 9 },
			{ 4, 5, 11 },
			{ 11, 5, 6 },
			{ 11, 6, 10 },
			{ 9, 11, 10 },
			{ 3, 9, 8 },
			{ 8, 9, 10 },
			{ 10, 7, 8 },
			{ 10, 6, 7 },
		}
	);
};