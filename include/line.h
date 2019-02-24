#pragma once
#include "shape.h"

class Line : public Shape{
private:
	Point m_start;
	Point m_end;
	Pixel m_color;

	void drawBresenham(Canvas &canvas);

public:
	Line(const Point &_start, const Point &_end, const Pixel &_color);
	Line(const Point &_start, const Point &_end);
	void draw(Canvas &canvas);
	
	inline bool isHorizontal() const;
	inline bool isVertical() const;
	inline bool is45DegreeDiagonal() const;
};