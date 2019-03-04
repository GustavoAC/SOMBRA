#pragma once
#include <utility>
#include <vector>
#include "canvas.h"
#include "edge.h"
#include "pixel.h"
#include "point.h"
#include "shape.h"

class Polygon : public Shape {
   private:
    std::vector<Point> m_points;
    Pixel stroke_color;
    Pixel fill_color;

    void draw(Canvas *canvas);
    void scanFill(Canvas *canvas);
    std::vector<Edge> getEdges();

   public:
    Polygon(const std::vector<Point> _points, const Pixel &_stroke_color = Pixel(0, 0, 0),
            const Pixel &_fill_color = Pixel(255, 255, 255));
    Polygon(const Point &p1, const Point &p2, const Point &p3,
            const Pixel &_stroke_color = Pixel(0, 0, 0),
            const Pixel &_fill_color = Pixel(255, 255, 255));
    Polygon(const Point &p1, const Point &p2, const Point &p3, const Point &p4,
            const Pixel &_stroke_color = Pixel(0, 0, 0),
            const Pixel &_fill_color = Pixel(255, 255, 255));

    void addPoint(const Point &p);
    std::pair<Point, Point> getBoundingBox();
};