#include "canvas.h"
#include "line.h"
#include "point.h"

int main(int argc, char const *argv[]) {
    Canvas c(100, 100);
    // c.setPixel(0,0,Pixel(255,0,0));
    // c.setPixel(0,1,Pixel(0,255,0));
    // c.setPixel(0,2,Pixel(0,0,255));
    // c.setPixel(1,0,Pixel(255,255,0));
    // c.setPixel(1,1,Pixel(255,0,255));
    // c.setPixel(1,2,Pixel(0,255,255));
    // Line l1(Point(20, 20), Point(20, 50));
    // Line l2(Point(30, 30), Point(80, 30));
    // Line l3(Point(40, 40), Point(40, 80));
    // Line l4(Point(27, 55), Point(60, 88));
	Line lur(Point(50,50), Point(70, 5));
	Line lru(Point(50,50), Point(95, 30), Pixel(255,0,0));
	Line lrd(Point(50,50), Point(95, 70), Pixel(255,255,0));
	Line ldr(Point(50,50), Point(70, 95), Pixel(0,255,0));
	Line ldl(Point(50,50), Point(30, 95), Pixel(0,255,255));
	Line lld(Point(50,50), Point(5, 70), Pixel(0,0,255));
	Line llu(Point(50,50), Point(5, 30), Pixel(255,0,255));
	Line lul(Point(50,50), Point(30, 5), Pixel(100,200,100));

	c.draw(lur);
    c.draw(lru);
    c.draw(lrd);
	c.draw(ldr);
	c.draw(ldl);
	c.draw(lld);
	c.draw(llu);
	c.draw(lul);

    // l1.draw(c);
    // l2.draw(c);
    // l3.draw(c);
    // l4.draw(c);

    c.writeToFile("pequeno");

    return 0;
}