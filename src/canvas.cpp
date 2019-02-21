#include "canvas.h"

Canvas::Canvas(int _width, int _height) : Canvas(_width, _height, Pixel(255,255,255)) {}

Canvas::Canvas(int _width, int _height, Pixel _backgroundColor) : m_width(_width), m_height(_height), m_backgroundColor(_backgroundColor) {
  	canvas = std::make_shared<Pixel*>(new Pixel[_width * _height]);
  	clear();
}

// Add memset for white case
void Canvas::clear() {
	for (int i; i < m_width * m_height; i++) (*canvas)[i] = m_backgroundColor;
}

void Canvas::setPixel(const Point &point, const Pixel &p) {
	(*canvas)[point.getX() * m_width + point.getY()] = p;
}

inline int Canvas::getWidth() const {
	return m_width;
}

inline int Canvas::getHeight() const {
	return m_height;
}

void Canvas::writeToFile(const std::string &filename) {
	std::ofstream file(filename + std::string(".ppm"));

	file << "P3" << std::endl << m_width << " " << m_height << std::endl << "255" << std::endl;

	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_width; ++j) {
			Pixel &p = (*canvas)[i * m_width + j];
			file << (int) p.getR() << " " << (int) p.getG() << " " << (int) p.getB() << " ";
		}
		file << std::endl;
	}

	file.close();
}