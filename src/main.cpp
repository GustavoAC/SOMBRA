#include <iostream>
#include <vector>
#include <memory>
#include "canvas.h"
#include "circle.h"
#include "line.h"
#include "point.h"
#include "polygon.h"
#include "polyline.h"
#include "tinyxml.h"

Pixel GET_COLOR(const std::string &colorName) {
    if (colorName == "black") return COLOR_BLACK;
    if (colorName == "red") return COLOR_RED;
    if (colorName == "green") return COLOR_GREEN;
    if (colorName == "blue") return COLOR_BLUE;
    if (colorName == "cyan") return COLOR_CYAN;
    if (colorName == "yellow") return COLOR_YELLOW;
    if (colorName == "magenta") return COLOR_MAGENTA;
    
    return COLOR_WHITE;
}

Shape* readShape(TiXmlNode* pShape) {
    std::string shapeValue(pShape->Value());
    if (shapeValue == "line") {
        std::shared_ptr<int> x1;
        std::shared_ptr<int> y1;
        std::shared_ptr<int> x2;
        std::shared_ptr<int> y2;
        int width = 1;
        Pixel color = COLOR_BLACK;

        TiXmlAttribute* pAttrib = pShape->ToElement()->FirstAttribute();
        int ival;
        while (pAttrib) {
            std::string attribName(pAttrib->Name());
            if (attribName == "x1") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) x1 = std::make_shared<int>(ival);
            } else if (attribName == "y1") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) y1 = std::make_shared<int>(ival);
            } else if (attribName == "x2") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) x2 = std::make_shared<int>(ival);
            } else if (attribName == "y2") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) y2 = std::make_shared<int>(ival);
            } else if (attribName == "width") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) width = ival;
            } else if (attribName == "color") {
                color = GET_COLOR(std::string(pAttrib->Value()));
            }

            pAttrib = pAttrib->Next();
        }

        if (x1 == nullptr || x2 == nullptr || y1 == nullptr || y2 == nullptr) {
            std::cout << "Unable to create line with given parameters\n";
            return nullptr;
        }

        Shape* s = new Line(Point(*x1, *y1), Point(*x2, *y2), width, color);
        return s;
    } else if (shapeValue == "polyline") {
        // if empty return null
        if (pShape->FirstChild() == nullptr) return nullptr;

        int width = 1;
        Pixel color = COLOR_BLACK;

        TiXmlAttribute* pAttrib = pShape->ToElement()->FirstAttribute();
        int ival;
        while (pAttrib) {
            std::string attribName(pAttrib->Name());
            if (attribName == "width") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) width = ival;
            } else if (attribName == "color") {
                color = GET_COLOR(std::string(pAttrib->Value()));;
            }

            pAttrib = pAttrib->Next();
        }
        Polyline *s = new Polyline(color, width);

        TiXmlNode* pChild;
        for (pChild = pShape->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
            if (pChild->Type() == TiXmlNode::TINYXML_ELEMENT && std::string(pChild->Value()) == "point") {
                std::shared_ptr<int> x;
                std::shared_ptr<int> y;

                TiXmlAttribute* pAttrib = pChild->ToElement()->FirstAttribute();
                int ival;
                while (pAttrib) {
                    std::string attribName(pAttrib->Name());
                    if (attribName == "x") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) x = std::make_shared<int>(ival);
                    } else if (attribName == "y") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) y = std::make_shared<int>(ival);
                    }

                    pAttrib = pAttrib->Next();
                }

                if (x == nullptr || y == nullptr) {
                    std::cout << "Unable to create point with given parameters\n";
                    continue;
                }

                s->addPoint(Point(*x, *y));
            }
        }
        
        return s;
    } else if (shapeValue == "polygon") {
        // if empty return null
        if (pShape->FirstChild() == nullptr) return nullptr;

        int width = 1;
        Pixel stroke_color = COLOR_BLACK;
        std::shared_ptr<Pixel> fill_color;

        TiXmlAttribute* pAttrib = pShape->ToElement()->FirstAttribute();
        int ival;
        while (pAttrib) {
            std::string attribName(pAttrib->Name());
            if (attribName == "width") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) width = ival;
            } else if (attribName == "stroke_color") {
                stroke_color = GET_COLOR(std::string(pAttrib->Value()));
            } else if (attribName == "fill_color") {
                fill_color = std::make_shared<Pixel>(GET_COLOR(std::string(pAttrib->Value())));
            }

            pAttrib = pAttrib->Next();
        }
    
        std::vector<Point> points;

        TiXmlNode* pChild;
        for (pChild = pShape->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
            if (pChild->Type() == TiXmlNode::TINYXML_ELEMENT && std::string(pChild->Value()) == "point") {
                std::shared_ptr<int> x;
                std::shared_ptr<int> y;

                TiXmlAttribute* pAttrib = pChild->ToElement()->FirstAttribute();
                int ival;
                while (pAttrib) {
                    std::string attribName(pAttrib->Name());
                    if (attribName == "x") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) x = std::make_shared<int>(ival);
                    } else if (attribName == "y") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) y = std::make_shared<int>(ival);
                    }

                    pAttrib = pAttrib->Next();
                }

                if (x == nullptr || y == nullptr) {
                    std::cout << "Unable to create point with given parameters\n";
                    continue;
                }

                points.push_back(Point(*x, *y));
            }
        }

        Polygon *s = new Polygon(points, stroke_color, width);
        if (fill_color != nullptr) s->setFillColor(*fill_color);
        
        return s;
    } else if (shapeValue == "circle") {
        std::shared_ptr<int> x;
        std::shared_ptr<int> y;
        std::shared_ptr<int> radius;
        std::shared_ptr<Pixel> fill_color;
        Pixel stroke_color = COLOR_BLACK;
        
        TiXmlAttribute* pAttrib = pShape->ToElement()->FirstAttribute();
        int ival;
        while (pAttrib) {
            std::string attribName(pAttrib->Name());
            if (attribName == "x") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) x = std::make_shared<int>(ival);
            } else if (attribName == "y") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) y = std::make_shared<int>(ival);
            } else if (attribName == "radius") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) radius = std::make_shared<int>(ival);
            } else if (attribName == "fill_color") {
                fill_color = std::make_shared<Pixel>(GET_COLOR(std::string(pAttrib->Value())));
            } else if (attribName == "stroke_color") {
                stroke_color = GET_COLOR(std::string(pAttrib->Value()));
            }

            pAttrib = pAttrib->Next();
        }

        if (x == nullptr || y == nullptr || radius == nullptr) {
            std::cout << "Unable to create circle with given parameters\n";
            return nullptr;
        }

        Shape* s;
        if (fill_color == nullptr) s = new Circle(Point(*x, *y), *radius, stroke_color);
        else s = new Circle(Point(*x, *y), *radius, stroke_color, *fill_color);

        return s;
    }

    return nullptr;
}

void addShapesToCanvas(Canvas* canvas, TiXmlNode* pXmlCanvas) {
    TiXmlNode* pChild;
    for (pChild = pXmlCanvas->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
        if (pChild->Type() == TiXmlNode::TINYXML_ELEMENT) {
            Shape* s = readShape(pChild);
            if (s != nullptr) {
                canvas->draw(*s);
                delete s;
            }
        }
    }
}

Canvas* createCanvas(TiXmlNode* pParent) {
    if (!pParent) return nullptr;

    int t = pParent->Type();
    switch (t) {
        case TiXmlNode::TINYXML_ELEMENT:
            if (std::string(pParent->Value()) == "canvas") {
                int height = -1;
                int width = -1;
                Pixel color = COLOR_WHITE;

                TiXmlAttribute* pAttrib = pParent->ToElement()->FirstAttribute();
                int ival;
                while (pAttrib) {
                    std::string attribName(pAttrib->Name());
                    if (attribName == "width") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) width = ival;
                    } else if (attribName == "height") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) height = ival;
                    } else if (attribName == "color") {
                        color = GET_COLOR(std::string(pAttrib->Value()));
                    }

                    pAttrib = pAttrib->Next();
                }

                if (width < 0 || height < 0) {
                    std::cout << "Please specify positive values for canvas width and height\n";
                    return nullptr;
                }

                Canvas* canvas = new Canvas(width, height, color);
                addShapesToCanvas(canvas, pParent);

                return canvas;
            }

            break;
        default:
            break;
    }

    Canvas* canvas = nullptr;
    TiXmlNode* pChild;

    for (pChild = pParent->FirstChild(); pChild != 0 && canvas == nullptr;
         pChild = pChild->NextSibling()) {
        canvas = createCanvas(pChild);
    }

    return canvas;
}

int main(int argc, char const* argv[]) {
    TiXmlDocument doc("example.xml");
    if (!doc.LoadFile()) {
        std::cout << "Cannot parse the file\n";
        return 1;
    }
    
    Canvas *canvas = createCanvas(&doc);
    canvas->writeToFile("pequeno");
    delete canvas;

    // Canvas c(100, 100);
    // // c.setPixel(0,0,Pixel(255,0,0));
    // // c.setPixel(0,1,Pixel(0,255,0));
    // // c.setPixel(0,2,Pixel(0,0,255));
    // // c.setPixel(1,0,Pixel(255,255,0));
    // // c.setPixel(1,1,Pixel(255,0,255));
    // // c.setPixel(1,2,Pixel(0,255,255));
    // // Line l1(Point(20, 20), Point(20, 50));
    // // Line l2(Point(30, 30), Point(80, 30));
    // // Line l3(Point(40, 40), Point(40, 80));
    // // Line l4(Point(27, 55), Point(60, 88));
    // Line lur(Point(50, 50), Point(70, 5), 3);
    // Line lru(Point(50, 50), Point(95, 30), 3, Pixel(255, 0, 0));
    // Line lrd(Point(50, 50), Point(95, 70), 3, Pixel(255, 255, 0));
    // Line ldr(Point(50, 50), Point(70, 95), 3, Pixel(0, 255, 0));
    // Line ldl(Point(50, 50), Point(30, 95), 3, Pixel(0, 255, 255));
    // Line lld(Point(50, 50), Point(5, 70), 3, Pixel(0, 0, 255));
    // Line llu(Point(50, 50), Point(5, 30), 3, Pixel(255, 0, 255));
    // Line lul(Point(50, 50), Point(30, 5), 3, Pixel(100, 200, 100));

    // c.draw(lur);
    // c.draw(lru);
    // c.draw(lrd);
    // c.draw(ldr);
    // c.draw(ldl);
    // c.draw(lld);
    // c.draw(llu);
    // c.draw(lul);

    // Line ldia(Point(20,20), Point(60,60), 3);
    // c.draw(ldia);

    // Line lHor(Point(30, 30), Point(30, 80), 3, Pixel(255, 100, 0));
    // Line lVer(Point(40, 30), Point(80, 30), 3, Pixel(100, 100, 255));

    // c.draw(lHor);
    // c.draw(lVer);

    // // Polygon skuare(Point(25,25), Point(25, 50), Point(50, 50), Point(50, 25),
    // Pixel(0,0,0), Pixel(0,255,0));
    // // c.draw(skuare);

    // // Circle cir(Point(70,70), 25, Pixel(0,0,255), Pixel(255,255,0));
    // // c.draw(cir);

    // // std::vector<Point> points;
    // // points.push_back(Point(25,25));
    // // points.push_back(Point(73, 23));
    // // points.push_back(Point(55, 90));
    // // points.push_back(Point(15, 40));

    // // Polyline p(points, Pixel(255,0,0));
    // // c.draw(p);

    // // Line lgree(Point(55, 90), Point(15, 40));
    // // Line lgreeok(Point(56, 95), Point(15, 45));
    // // Line lgree2(Point(20, 45), Point(60, 95));
    // // Line lgroo(Point(20, 45), Point(30, 30));
    // // Line lgrii(Point(95, 45), Point(33, 33));
    // // Line lgruu(Point(85, 80), Point(30, 95));
    // // Line lgraa(Point(80, 30), Point(85, 90));

    // // c.draw(lgree);
    // // c.draw(lgreeok);
    // // c.draw(lgroo);
    // // c.draw(lgrii);
    // // c.draw(lgruu);
    // // c.draw(lgraa);

    // // l1.draw(c);
    // // l2.draw(c);
    // // l3.draw(c);
    // // l4.draw(c);

    // c.writeToFile("pequeno");

    return 0;
}