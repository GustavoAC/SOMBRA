#pragma once

#include <vector>
#include "shape.h"
#include "pixel.h"
#include "point.h"
#include "canvas.h"

//! Represents a Polyline Shape
class Polyline: public Shape {
private:
    std::vector<Point> m_points;
    Pixel stroke_color;
    int stroke_width;

    void draw(Canvas *canvas);

public:
    Polyline(const Pixel &_stroke_color = Pixel(0, 0, 0), const int &_stroke_width = 1);
    Polyline(const std::vector<Point> &_points, const Pixel &_stroke_color = Pixel(0, 0, 0), const int &_stroke_width = 1);

    //! Adds a new point to the Polyline
    void addPoint(const Point &p);
};
