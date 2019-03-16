#pragma once
#include "shape.h"
#include "point.h"
#include "pixel.h"

//! Represents the Line Shape
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
	
	//! Returns true if line is horizontal
	inline bool isHorizontal() const;
	//! Returns true if line is vertical
	inline bool isVertical() const;
	//! Returns true if line is diagonal to 45 degrees
	inline bool is45DegreeDiagonal() const;
};