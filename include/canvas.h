#pragma once

#include <memory>
#include <fstream>
#include "pixel.h"
#include "point.h"

class Canvas {
  private:
  	int m_width;
  	int m_height;
  	std::shared_ptr<Pixel*> canvas;

    Pixel m_backgroundColor;
  public:
  	Canvas(int _width, int _height);
    Canvas(int _width, int _height, Pixel m_backgroundColor);

    void clear();
    void setPixel(const Point &point, const Pixel &p);
    inline int getWidth() const;
    inline int getHeight() const;
    void writeToFile(const std::string &filename);
};