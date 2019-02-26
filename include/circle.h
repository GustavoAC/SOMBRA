#pragma once
#include <functional>
#include "shape.h"
#include "point.h"
#include "pixel.h"

class Circle : public Shape{
private:
	Point m_center;
	int m_radius;
	Pixel m_color;

	void draw(Canvas *canvas);
	void draw2(Canvas *canvas, const std::function<void (int,int)> &drawPoint);

public:
	Circle(const Point &_center, const int &_radius, const Pixel &_color);
	Circle(const Point &_center, const int &_radius);
};