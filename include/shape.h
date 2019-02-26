#pragma once

class Canvas;

class Shape {
private:
	virtual void draw(Canvas *canvas) = 0;
	friend class Canvas;
};