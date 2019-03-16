#pragma once

#include <memory>
#include <fstream>
#include "pixel.h"
#include "point.h"
#include "shape.h"

class Canvas {
  private:
  	int m_width;
  	int m_height;
  	std::shared_ptr<Pixel> canvas;

    Pixel m_backgroundColor;
    Pixel& getPixel(int x, int y);
  
    void applyAntiAlias();

  public:
  	Canvas(int _width, int _height);
    Canvas(int _width, int _height, Pixel _backgroundColor);

    void setBackgroundColor(const Pixel &_backgroundColor);
    void clear();
    void draw(Shape &shape);
    void setPixel(const Point &point, const Pixel &p);
    void floodFill(int x, int y, const Pixel &newColor, const Pixel &limitColor);
    inline int getWidth() const { return m_width; }
    inline int getHeight() const { return m_height; }
    void writeToFile(const std::string &filename, const bool &antiAlias = true);
};