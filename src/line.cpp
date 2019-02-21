#include "line.h"

Line::Line(const Point &_start, const Point &_end) {
	m_start = _start;
	m_end = _end;
}

void Line::draw(Canvas &canvas) {
	canvas.setPixel(m_start, Pixel(0,255,0));
	canvas.setPixel(m_end, Pixel(0,255,0));
}
