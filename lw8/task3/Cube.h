#pragma once
#include "Shape.h"

class CCube : public CShape
{
public:
	CCube(
		std::vector<Vertex> vertices = {
			CVector3d(-1, -1, -1),
			CVector3d(-1, 1, -1),
			CVector3d(1, -1, -1),
			CVector3d(1, 1, -1),
			CVector3d(-1, -1, 1),
			CVector3d(-1, 1, 1),
			CVector3d(1, -1, 1),
			CVector3d(1, 1, 1),
		},
		std::vector<Face> faces = {
			{ 1, 2, 0 },
			{ 1, 3, 2 },
			{ 0, 5, 1 },
			{ 0, 4, 5 },
			{ 4, 6, 5 },
			{ 5, 6, 7 },
			{ 0, 2, 6 },
			{ 0, 6, 4 },
			{ 2, 7, 6 },
			{ 3, 7, 2 },
			{ 1, 5, 7 },
			{ 1, 7, 3 },
		}
	);
};