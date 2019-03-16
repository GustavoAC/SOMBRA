#pragma once

#include <memory>
#include <fstream>
#include "pixel.h"
#include "point.h"
#include "shape.h"

//! Class representing the canvas object in which the objects are drawn

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

    //! Sets a new background color for the Canvas
    void setBackgroundColor(const Pixel &_backgroundColor);
    //! Clears the canvas
    void clear(); 
    //! Draws the given shape on the image
    void draw(Shape &shape);
    //! Sets the given point with the given pixel
    void setPixel(const Point &point, const Pixel &p);
    //! Starts flood fill on the specified point
    void floodFill(int x, int y, const Pixel &newColor, const Pixel &limitColor);
    //! Returns canvas width
    inline int getWidth() const { return m_width; }
    //! Returns canvas height
    inline int getHeight() const { return m_height; }
    //! Writes canvas to file, applying convolution antialiasing is optional
    void writeToFile(const std::string &filename, const bool &antiAlias = true);
};