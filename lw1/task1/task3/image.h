#pragma once
#include "stdafx.h"
#include "geom.h"
#include "tile.h"

class Image
{
public:
    /**
     * Конструирует изображение заданного размера. Если размеры не являются положительными,
     * выбрасывает исключение std::out_of_range.
     */
    explicit Image(Size size, uint8_t color = 0);

    // Возвращает размер изображения в пикселях.
    Size GetSize() const noexcept;

    /**
     * Возвращает «цвет» пикселя в указанных координатах.Если координаты выходят за пределы
     * изображения, возвращает «пробел».
     */
    uint8_t GetPixel(Point p) const noexcept;

    /**
     * Задаёт «цвет» пикселя в указанных координатах. Если координаты выходят за пределы изображения
     * действие игнорируется.
     */
    void SetPixel(Point p, uint8_t color);

private:
    Size m_size;
    std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
};

/**
 * Выводит в поток out изображение в виде символов.
 */
void Print(const Image& img, wxDC& dc);

/**
 * Загружает изображение из pixels. Линии изображения разделяются символами \n.
 * Размеры картинки определяются по количеству переводов строки и самой длинной линии.
 */
Image LoadImage(const std::string& pixels);