#pragma once
#include "shape.h"

class Line : public Shape{
private:
	Point m_start;
	Point m_end;

public:
	Line(const Point &_start, const Point &_end);
	void draw(Canvas &canvas);
};