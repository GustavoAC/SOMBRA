#pragma once
#include "shape.h"
#include "point.h"
#include "pixel.h"

class Line : public Shape{
private:
	Point m_start;
	Point m_end;
	Pixel m_color;

	void drawBresenham(Canvas *canvas);
	void draw(Canvas *canvas);

public:
	Line(const Point &_start, const Point &_end, const Pixel &_color);
	Line(const Point &_start, const Point &_end);
	
	inline bool isHorizontal() const;
	inline bool isVertical() const;
	inline bool is45DegreeDiagonal() const;
};