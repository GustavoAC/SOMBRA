#pragma once
#include <functional>
#include "pixel.h"
#include "point.h"
#include "shape.h"

class Circle : public Shape {
   private:
    Point m_center;
    int m_radius;
    Pixel stroke_color;
    Pixel fill_color;

    void draw(Canvas *canvas);
    void draw2(Canvas *canvas, const std::function<void(int, int)> &drawPoint);

   public:
    Circle(const Point &_center, const int &_radius, const Pixel &stroke_color,
           const Pixel &fill_color = Pixel(255, 255, 255));
    Circle(const Point &_center, const int &_radius);
};