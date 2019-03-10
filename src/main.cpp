#include <vector>
#include "canvas.h"
#include "circle.h"
#include "line.h"
#include "point.h"
#include "polygon.h"
#include "polyline.h"

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
    Line lur(Point(50, 50), Point(70, 5), 3);
    Line lru(Point(50, 50), Point(95, 30), 3, Pixel(255, 0, 0));
    Line lrd(Point(50, 50), Point(95, 70), 3, Pixel(255, 255, 0));
    Line ldr(Point(50, 50), Point(70, 95), 3, Pixel(0, 255, 0));
    Line ldl(Point(50, 50), Point(30, 95), 3, Pixel(0, 255, 255));
    Line lld(Point(50, 50), Point(5, 70), 3, Pixel(0, 0, 255));
    Line llu(Point(50, 50), Point(5, 30), 3, Pixel(255, 0, 255));
    Line lul(Point(50, 50), Point(30, 5), 3, Pixel(100, 200, 100));

    c.draw(lur);
    c.draw(lru);
    c.draw(lrd);
    c.draw(ldr);
    c.draw(ldl);
    c.draw(lld);
    c.draw(llu);
    c.draw(lul);

    Line ldia(Point(20,20), Point(60,60), 3);
    c.draw(ldia);

    Line lHor(Point(30, 30), Point(30, 80), 3, Pixel(255, 100, 0));
    Line lVer(Point(40, 30), Point(80, 30), 3, Pixel(100, 100, 255));

    c.draw(lHor);
    c.draw(lVer);

    // Polygon skuare(Point(25,25), Point(25, 50), Point(50, 50), Point(50, 25), Pixel(0,0,0), Pixel(0,255,0));
    // c.draw(skuare);

    // Circle cir(Point(70,70), 25, Pixel(0,0,255), Pixel(255,255,0));
    // c.draw(cir);

    // std::vector<Point> points;
    // points.push_back(Point(25,25));
    // points.push_back(Point(73, 23));
    // points.push_back(Point(55, 90));
    // points.push_back(Point(15, 40));

    // Polyline p(points, Pixel(255,0,0));
    // c.draw(p);

    // Line lgree(Point(55, 90), Point(15, 40));
    // Line lgreeok(Point(56, 95), Point(15, 45));
    // Line lgree2(Point(20, 45), Point(60, 95));
    // Line lgroo(Point(20, 45), Point(30, 30));
    // Line lgrii(Point(95, 45), Point(33, 33));
    // Line lgruu(Point(85, 80), Point(30, 95));
    // Line lgraa(Point(80, 30), Point(85, 90));

    // c.draw(lgree);
    // c.draw(lgreeok);
    // c.draw(lgroo);
    // c.draw(lgrii);
    // c.draw(lgruu);
    // c.draw(lgraa);

    // l1.draw(c);
    // l2.draw(c);
    // l3.draw(c);
    // l4.draw(c);

    c.writeToFile("pequeno");

    return 0;
}