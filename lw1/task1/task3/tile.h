#pragma once
#include "stdafx.h"
#include "geom.h"

class Tile
{
public:
	constexpr static int SIZE = 8;

	Tile(unsigned long color = ' ') noexcept
	{
		for (unsigned y = 0; y < SIZE; y++)
		{
			std::vector<unsigned long> row;
			for (unsigned x = 0; x < SIZE; x++)
			{
				row.push_back(color);
			}
			m_pixels.push_back(row);
		}
		assert(m_instanceCount >= 0);
		++m_instanceCount;
	}

	Tile(const Tile& other)
	{
		for (unsigned y = 0; y < SIZE; y++)
		{
			std::vector<unsigned long> row;
			for (unsigned x = 0; x < SIZE; x++)
			{
				unsigned long color = other.GetPixel({ (int)x, (int)y });
				row.push_back(color);
			}
			m_pixels.push_back(row);
		}
		assert(m_instanceCount >= 0);
		++m_instanceCount;
	}

	~Tile()
	{
		assert(m_instanceCount >= 0);
	}

	void SetPixel(Point p, unsigned long color) noexcept
	{
		if (!IsPointInSize(p, { SIZE, SIZE }))
		{
			return;
		}
		try
		{
			m_pixels.at(p.y).at(p.x) = color;
		}
		catch (std::out_of_range& e)
		{
			return;
		}
	}

	unsigned long GetPixel(Point p) const noexcept
	{
		if (!IsPointInSize(p, { SIZE, SIZE }))
		{
			return ' ';
		}
		try
		{
			return m_pixels.at(p.y).at(p.x);
		}
		catch (std::out_of_range& e)
		{
			return ' ';
		}
	}

	static int GetInstanceCount() noexcept
	{
		return m_instanceCount;
	}

private:
	inline static int m_instanceCount = 0;
	std::vector<std::vector<unsigned long>> m_pixels;
};