#include "canvas.h"
#include "line.h"
#include "point.h"

int main(int argc, char const *argv[]) {
	Canvas c(100,100);
	// c.setPixel(0,0,Pixel(255,0,0));
	// c.setPixel(0,1,Pixel(0,255,0));
	// c.setPixel(0,2,Pixel(0,0,255));
	// c.setPixel(1,0,Pixel(255,255,0));
	// c.setPixel(1,1,Pixel(255,0,255));
	// c.setPixel(1,2,Pixel(0,255,255));
	Line l(Point(20,20), Point(60,50));
	l.draw(c);

	c.writeToFile("pequeno");

	return 0;
}