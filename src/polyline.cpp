#include "polyline.h"
#include "line.h"

Polyline::Polyline(const Pixel &_stroke_color, const int &_stroke_width)
    : Polyline(std::vector<Point>(), _stroke_color, _stroke_width) {}

Polyline::Polyline(const std::vector<Point> &_points, const Pixel &_stroke_color,
                   const int &_stroke_width)
    : m_points(_points), stroke_color(_stroke_color), stroke_width(_stroke_width) {}

void Polyline::addPoint(const Point &p) { m_points.push_back(p); }

void Polyline::draw(Canvas *canvas) {
    for (auto i = 0u; i < m_points.size() - 1; i++) {
        auto line = Line(m_points[i], m_points[i + 1], stroke_width, stroke_color);
        canvas->draw(line);
    }
}