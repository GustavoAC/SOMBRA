#pragma once

class Canvas;

/**
 * @brief
 * Interface representing any generic shape. All shapes must implement this interface to be drawn on the Canvas
 */
class Shape {
   public:
    virtual ~Shape() {}

   private:
    virtual void draw(Canvas *canvas) = 0;
    friend class Canvas;
};