#pragma once
#include <functional>
#include <memory>
#include "pixel.h"
#include "point.h"
#include "shape.h"

/**
 * Represents the circle shape
 */

class Circle : public Shape {
   private:
    Point m_center;
    int m_radius;
    Pixel stroke_color;
    std::shared_ptr<Pixel> fill_color;

    void draw(Canvas *canvas);
    void draw2(Canvas *canvas, const std::function<void(int, int)> &drawPoint);

   public:
    Circle(const Point &_center, const int &_radius, const Pixel &stroke_color);
    Circle(const Point &_center, const int &_radius, const Pixel &stroke_color,
           const Pixel &fill_color);
    Circle(const Point &_center, const int &_radius);
};