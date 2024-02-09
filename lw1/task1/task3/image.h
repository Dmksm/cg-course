#pragma once
#include "stdafx.h"
#include "geom.h"
#include "tile.h"

class Image
{
public:
    /**
     * ������������ ����������� ��������� �������. ���� ������� �� �������� ��������������,
     * ����������� ���������� std::out_of_range.
     */
    explicit Image(Size size, unsigned long color = 0);

    // ���������� ������ ����������� � ��������.
    Size GetSize() const noexcept;

    /**
     * ���������� ����� ������� � ��������� �����������.���� ���������� ������� �� �������
     * �����������, ���������� �������.
     */
    unsigned long GetPixel(Point p) const noexcept;

    /**
     * ����� ����� ������� � ��������� �����������. ���� ���������� ������� �� ������� �����������
     * �������� ������������.
     */
    void SetPixel(Point p, unsigned long color);

private:
    Size m_size;
    std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
};

/**
 * ������� � ����� out ����������� � ���� ��������.
 */
void Print(const Image& img, wxDC& dc);

/**
 * ��������� ����������� �� pixels. ����� ����������� ����������� ��������� \n.
 * ������� �������� ������������ �� ���������� ��������� ������ � ����� ������� �����.
 */
Image LoadImage(const std::string& pixels);