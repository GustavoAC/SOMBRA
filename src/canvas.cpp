#include "canvas.h"
#include <iostream>

Canvas::Canvas(int _width, int _height) : Canvas(_width, _height, Pixel(255,255,255)) {}

Canvas::Canvas(int _width, int _height, Pixel _backgroundColor) : m_width(_width), m_height(_height), m_backgroundColor(_backgroundColor) {
  	canvas = std::make_shared<Pixel*>(new Pixel[_width * _height]);
  	clear();
}

// Add memset for white case
void Canvas::clear() {
	for (int i = 0; i < m_width * m_height; i++) (*canvas)[i] = m_backgroundColor;
}

void Canvas::setPixel(const Point &point, const Pixel &p) {
	std::cout << "Painting position (" << (int) point.getX() << ", " << (int) point.getY() << ") with color (" << (int) p.getR() << ", " << (int) p.getG() << ", " << (int) p.getB() << ")\n";
	if (point.getX() < m_width && point.getX() >= 0 && point.getY() < m_height && point.getY() >= 0) (*canvas)[point.getY() * m_width + point.getX()] = p;
}

Pixel& Canvas::getPixel(int x, int y) {
	return (*canvas)[y * m_width + x];
}

inline int Canvas::getWidth() const {
	return m_width;
}

inline int Canvas::getHeight() const {
	return m_height;
}

void Canvas::writeToFile(const std::string &filename) {
	std::ofstream file(filename + std::string(".ppm"));

	file << "P3" << std::endl << m_width << " " << m_height << std::endl << "256" << std::endl;

	for (int y = 0; y < m_height; ++y) {
		for (int x = 0; x < m_width; ++x) {
			Pixel &p = getPixel(x,y);
			file << (int) p.getR() << " " << (int) p.getG() << " " << (int) p.getB() << " ";
		}
		file << std::endl;
	}

	file.close();
}