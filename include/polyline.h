#pragma once

#include <vector>
#include "shape.h"
#include "pixel.h"
#include "point.h"
#include "canvas.h"

class Polyline: public Shape {
private:
    std::vector<Point> m_points;
    Pixel stroke_color;
    int stroke_width;

    void draw(Canvas *canvas);

public:
    Polyline(const Pixel &_stroke_color = Pixel(0, 0, 0), const int &_stroke_width = 1);
    Polyline(const std::vector<Point> &_points, const Pixel &_stroke_color = Pixel(0, 0, 0), const int &_stroke_width = 1);

    void addPoint(const Point &p);
};
