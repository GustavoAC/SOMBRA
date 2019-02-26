#include "circle.h"
#include "canvas.h"
#include <functional>
#include <iostream>

Circle::Circle(const Point &_center, const int &_radius, const Pixel &_color)
    : m_center(_center), m_radius(_radius), m_color(_color) {}

Circle::Circle(const Point &_center, const int &_radius) : Circle(_center, _radius, Pixel(0, 0, 0)) {}

void Circle::draw(Canvas *canvas) {
    int x = m_center.getX();
    int y = m_center.getY() + m_radius;
    int d = 1 - m_radius;

    int deltaL = 3;
    int deltaSE = -2 * m_radius + 5;

    std::cout << "deltaL " << deltaL << ", deltaSE " << deltaSE << ", d " << d << "\n";
    canvas->setPixel(Point(x, y), m_color);
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
        std::cout << "deltaL " << deltaL << ", deltaSE " << deltaSE << ", d " << d << "\n";
        canvas->setPixel(Point(x, y), m_color);
    }
    draw2(canvas);
}

void Circle::draw2(Canvas *canvas) {
    int x = 0;
    int y = m_radius;
    int d = 1 - m_radius;

    int deltaL = 3;
    int deltaSE = -2 * m_radius + 5;

    std::cout << "deltaL " << deltaL << ", deltaSE " << deltaSE << ", d " << d << "\n";
    canvas->setPixel(Point(m_center.getX() - x, m_center.getY() + y), m_color);
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
        std::cout << "deltaL " << deltaL << ", deltaSE " << deltaSE << ", d " << d << "\n";
        canvas->setPixel(Point(m_center.getX() - x, m_center.getY() + y), m_color);
    }
}