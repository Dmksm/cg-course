#include "image.h"
#include "stdafx.h"

int DivUp(int x, int y)
{
	return (x - 1) / y + 1;
}

Image::Image(Size size, unsigned long color)
{
	if (size.height < 0 || size.width < 0)
	{
		throw std::out_of_range("size must not be negative!");
	}

	int tileWidth = DivUp(size.width, Tile::SIZE);
	int tileHeight = DivUp(size.height, Tile::SIZE);
	std::shared_ptr<Tile> tilePtr = std::make_shared<Tile>(color);
	for (unsigned y = 0; y < tileHeight; y++)
	{
		std::vector<std::shared_ptr<Tile>> row;
		for (unsigned x = 0; x < tileWidth; x++)
		{
			row.push_back(tilePtr);
		}
		m_tiles.push_back(row);
	}
	m_size = size;
}

Size Image::GetSize() const noexcept
{
	return m_size;
}

unsigned long Image::GetPixel(Point p) const noexcept
{
	if (!IsPointInSize(p, m_size))
	{
		return 0;
	}
	try
	{
		int tileX = p.x / Tile::SIZE;
		int tileY = p.y / Tile::SIZE;
		p.x %= Tile::SIZE;
		p.y %= Tile::SIZE;
		return m_tiles.at(tileY).at(tileX)->GetPixel(p);
	}
	catch (std::out_of_range& e)
	{
		return 0;
	}
}

void Image::SetPixel(Point p, unsigned long color)
{
	if (!IsPointInSize(p, m_size))
	{
		return;
	}
	try
	{
		int tileX = p.x / Tile::SIZE;
		int tileY = p.y / Tile::SIZE;
		p.x %= Tile::SIZE;
		p.y %= Tile::SIZE;
		if (color != m_tiles.at(tileY).at(tileX)->GetPixel(p))
		{
			Tile tile = *m_tiles.at(tileY).at(tileX);
			std::shared_ptr<Tile> tilePtr = std::make_shared<Tile>(tile);
			tilePtr->SetPixel(p, color);
			m_tiles.at(tileY).at(tileX).swap(tilePtr);
		}
	}
	catch (std::out_of_range& e)
	{
		return;
	}
}

void Print(const Image& img, wxDC& dc)
{
	const auto size = img.GetSize();

	wxImage image(size.width, size.height);
	for (int y = 0; y < size.height; ++y)
	{
		for (int x = 0; x < size.width; ++x)
		{
			unsigned long pixel = img.GetPixel({ x, y });
			unsigned int red = (pixel & 0x00ff0000) >> 16;
			unsigned int green = (pixel & 0x0000ff00) >> 8;
			unsigned int blue = (pixel & 0x000000ff);
			image.SetRGB(x, y, red, green, blue);
		}
	}
	wxBitmap bmp(image);
	dc.DrawBitmap(bmp, 200, 200);
}

Image LoadImage(const std::string& pixels)
{
	std::istringstream s(pixels);
	Size size;
	std::string line;
	while (std::getline(s, line))
	{
		size.width = std::max(size.width, static_cast<int>(line.length()));
		++size.height;
	}

	Image img(size);

	s = std::istringstream(pixels);
	for (int y = 0; y < size.height; ++y)
	{
		if (!std::getline(s, line))
			break;

		int x = 0;
		for (char ch : line)
		{
			img.SetPixel({ x++, y }, ch);
		}
	}

	return img;
}