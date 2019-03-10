#include "canvas.h"
#include <cmath>
#include <iostream>

Canvas::Canvas(int _width, int _height) : Canvas(_width, _height, Pixel(255, 255, 255)) {}

Canvas::Canvas(int _width, int _height, Pixel _backgroundColor)
    : m_width(_width), m_height(_height), m_backgroundColor(_backgroundColor) {
    canvas = std::make_shared<Pixel *>(new Pixel[_width * _height]);
    clear();
}

// Add memset for white case
void Canvas::clear() {
    for (int i = 0; i < m_width * m_height; i++) (*canvas)[i] = m_backgroundColor;
}

void Canvas::draw(Shape &shape) { shape.draw(this); }

void Canvas::floodFill(int x, int y, const Pixel &newColor, const Pixel &limitColor) {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) return;
    if (getPixel(x, y) != newColor && getPixel(x, y) != limitColor) {
        setPixel(Point(x, y), newColor);
        floodFill(x - 1, y, newColor, limitColor);
        floodFill(x + 1, y, newColor, limitColor);
        floodFill(x, y - 1, newColor, limitColor);
        floodFill(x, y + 1, newColor, limitColor);
    }
}

void Canvas::setPixel(const Point &point, const Pixel &p) {
    // std::cout << "Painting position (" << (int)point.getX() << ", " << (int)point.getY()
    //   << ") with color (" << (int)p.getR() << ", " << (int)p.getG() << ", " << (int)p.getB()
    //   << ")\n";
    if (point.getX() < m_width && point.getX() >= 0 && point.getY() < m_height && point.getY() >= 0)
        (*canvas)[point.getY() * m_width + point.getX()] = p;
}

Pixel &Canvas::getPixel(int x, int y) { return (*canvas)[y * m_width + x]; }

void Canvas::writeToFile(const std::string &filename, const bool &antiAlias) {
    if (antiAlias) applyAntiAlias();
    std::ofstream file(filename + std::string(".ppm"));

    file << "P3" << std::endl << m_width << " " << m_height << std::endl << "256" << std::endl;

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            Pixel &p = getPixel(x, y);
            file << (int)p.getR() << " " << (int)p.getG() << " " << (int)p.getB() << " ";
        }
        file << std::endl;
    }

    file.close();
}

void Canvas::applyAntiAlias() {
    Pixel *new_image = new Pixel[m_width * m_height];

    // fill borders
    for (int i = 0; i < m_width; i++) {
        new_image[i * m_width + 0] = getPixel(0, i);
        new_image[i * m_width + (m_height - 1)] = getPixel(m_height - 1, i);
    }

    for (int i = 0; i < m_height; i++) {
        new_image[0 * m_width + i] = getPixel(i, 0);
        new_image[(m_width - 1) * m_width + i] = getPixel(i, m_width - 1);
    }

    // Apply convolution
    int gauss[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

    for (int i = 1; i < m_width - 1; i++) {
        for (int j = 1; j < m_height - 1; j++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    Pixel p = getPixel(i + k, j + l);
                    sumR += gauss[k + 1][l + 1] * (p.getR() * p.getR());
                    sumG += gauss[k + 1][l + 1] * (p.getG() * p.getG());
                    sumB += gauss[k + 1][l + 1] * (p.getB() * p.getB());
                }
            }

            Pixel p(sqrt(sumR / 16), sqrt(sumG / 16), sqrt(sumB / 16));
            new_image[j * m_width + i] = p;
        }
    }

    canvas = std::make_shared<Pixel *>(new_image);
}