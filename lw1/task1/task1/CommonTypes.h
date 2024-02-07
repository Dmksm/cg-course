#pragma once

template <typename T>
struct Point
{
	T x;
	T y;

	auto operator<=>(const Point& other) const = default;
};

typedef Point<double> PointD;