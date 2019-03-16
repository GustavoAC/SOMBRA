#pragma once
#include <memory>
#include <utility>
#include <vector>
#include "canvas.h"
#include "edge.h"
#include "pixel.h"
#include "point.h"
#include "shape.h"

//! Represents a polygon shape
class Polygon : public Shape {
   private:
    std::vector<Point> m_points;
    Pixel stroke_color;
    std::shared_ptr<Pixel> fill_color;
    int stroke_width;

    void draw(Canvas *canvas);
    void scanFill(Canvas *canvas);
    std::vector<Edge> getEdges();

   public:
    Polygon(const std::vector<Point> _points, const Pixel &_stroke_color = Pixel(0, 0, 0),
            const int &_stroke_width = 1);
    Polygon(const Point &p1, const Point &p2, const Point &p3,
            const Pixel &_stroke_color = Pixel(0, 0, 0), const int &_stroke_width = 1);
    Polygon(const Point &p1, const Point &p2, const Point &p3, const Point &p4,
            const Pixel &_stroke_color = Pixel(0, 0, 0), const int &_stroke_width = 1);
    
    //! Sets fill color of the polygon
    void setFillColor(const Pixel &color);

    //! Adds a new point after the last current point of the polygon
    void addPoint(const Point &p);

    //! Gets two points which, together, envelop the polygon
    std::pair<Point, Point> getBoundingBox();
};