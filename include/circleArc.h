#pragma once
#include <functional>
#include <memory>
#include "pixel.h"
#include "point.h"
#include "shape.h"

class CircleArc : public Shape {
   private:
    Point m_center;
    int m_radius;
    float m_angle_start;
    float m_angle_end;
    Pixel stroke_color;
    std::shared_ptr<Pixel> fill_color;

    void draw(Canvas *canvas);
    void draw2(Canvas *canvas, const std::function<void(int, int)> &drawPoint);

   public:
    CircleArc(const Point &_center, const int &_radius, const float &_angle_start, const float &_angle_end, const Pixel &stroke_color);
    CircleArc(const Point &_center, const int &_radius, const float &_angle_start, const float &_angle_end, const Pixel &stroke_color,
           const Pixel &fill_color);
};