#pragma once
#include "shape.h"
#include "point.h"
#include "pixel.h"

class Line : public Shape{
private:
	Point m_start;
	Point m_end;
	Pixel m_color;
	int m_width;

	void drawDDA(Canvas *canvas);
	void drawBresenham(Canvas *canvas);
	void draw(Canvas *canvas);
	void drawThickLine(Canvas *canvas);

public:
	Line(const Point &_start, const Point &_end, const int &_width = 1, const Pixel &_color = Pixel(0,0,0));
	
	inline bool isHorizontal() const;
	inline bool isVertical() const;
	inline bool is45DegreeDiagonal() const;
};