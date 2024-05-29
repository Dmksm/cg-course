#include "stdafx.h"
#include "Cube.h"

CCube::CCube(std::vector<Vertex> vertices, std::vector<Face> faces)
	: CShape(vertices, faces)
{};