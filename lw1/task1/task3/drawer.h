#pragma once
#include "stdafx.h"
#include "image.h"


void DrawLine(Image& image, Point from, Point to, unsigned long color);

void DrawCircle(Image& image, Point center, int radius, unsigned long color);

void FillCircle(
	Image& image,
	Point center,
	int radius,
	unsigned long fillColor,
	unsigned long outlineColor
);