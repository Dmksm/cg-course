#include "stdafx.h"
#include "Shape.h"

CShape::CShape(std::vector<Vertex> vertices, std::vector<Face> faces)
    : m_vertices(vertices)
    , m_faces(faces) {}

std::vector<Vertex> CShape::GetVertices()const
{
    return m_vertices;
}

std::vector<Face> CShape::GetFaces()const
{
    return m_faces;
}