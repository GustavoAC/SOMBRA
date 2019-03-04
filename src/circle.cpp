#include "circle.h"
#include "canvas.h"
#include <functional>
#include <iostream>

Circle::Circle(const Point &_center, const int &_radius, const Pixel &_stroke_color, const Pixel &_fill_color)
    : m_center(_center), m_radius(_radius), stroke_color(_stroke_color), fill_color(_fill_color) {}

Circle::Circle(const Point &_center, const int &_radius) : Circle(_center, _radius, Pixel(0, 0, 0)) {}

void Circle::draw(Canvas *canvas) {
    std::cout << "Drawing Circle...\n\n";
    draw2(canvas, [this, canvas](const int &x, const int &y) {canvas->setPixel(Point(m_center.getX() + x, m_center.getY() + y), stroke_color);});
    draw2(canvas, [this, canvas](const int &x, const int &y) {canvas->setPixel(Point(m_center.getY() + y, m_center.getX() + x), stroke_color);});
    draw2(canvas, [this, canvas](const int &x, const int &y) {canvas->setPixel(Point(m_center.getY() + y, m_center.getX() - x), stroke_color);});
    draw2(canvas, [this, canvas](const int &x, const int &y) {canvas->setPixel(Point(m_center.getX() + x, m_center.getY() - y), stroke_color);});
    draw2(canvas, [this, canvas](const int &x, const int &y) {canvas->setPixel(Point(m_center.getX() - x, m_center.getY() - y), stroke_color);});
    draw2(canvas, [this, canvas](const int &x, const int &y) {canvas->setPixel(Point(m_center.getY() - y, m_center.getX() - x), stroke_color);});
    draw2(canvas, [this, canvas](const int &x, const int &y) {canvas->setPixel(Point(m_center.getY() - y, m_center.getX() + x), stroke_color);});
    draw2(canvas, [this, canvas](const int &x, const int &y) {canvas->setPixel(Point(m_center.getX() - x, m_center.getY() + y), stroke_color);});

    canvas->floodFill(m_center.getX(), m_center.getY(), fill_color, stroke_color);
}

void Circle::draw2(Canvas *canvas, const std::function<void (int,int)> &drawPoint) {
    int x = 0;
    int y = m_radius;
    int d = 1 - m_radius;

    int deltaL = 3;
    int deltaSE = -2 * m_radius + 5;

    drawPoint(x, y);
    while (y > x) {
        if (d < 0) {
            d += deltaL;
            deltaL += 2;
            deltaSE += 2;
        } else {
            d += deltaSE;
            deltaL += 2;
            deltaSE += 4;
            y--;
        }
        x++;
        drawPoint(x, y);
    }
}