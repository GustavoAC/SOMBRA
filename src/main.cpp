#include <iostream>
#include <vector>
#include "canvas.h"
#include "circle.h"
#include "line.h"
#include "point.h"
#include "polygon.h"
#include "polyline.h"
#include "tinyxml.h"

const unsigned int NUM_INDENTS_PER_SPACE = 2;

const char* getIndent(unsigned int numIndents) {
    static const char* pINDENT = "                                      + ";
    static const unsigned int LENGTH = strlen(pINDENT);
    unsigned int n = numIndents * NUM_INDENTS_PER_SPACE;
    if (n > LENGTH) n = LENGTH;

    return &pINDENT[LENGTH - n];
}

// same as getIndent but no "+" at the end
const char* getIndentAlt(unsigned int numIndents) {
    static const char* pINDENT = "                                        ";
    static const unsigned int LENGTH = strlen(pINDENT);
    unsigned int n = numIndents * NUM_INDENTS_PER_SPACE;
    if (n > LENGTH) n = LENGTH;

    return &pINDENT[LENGTH - n];
}

int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent) {
    if (!pElement) return 0;

    TiXmlAttribute* pAttrib = pElement->FirstAttribute();
    int i = 0;
    int ival;
    double dval;
    const char* pIndent = getIndent(indent);
    printf("\n");
    while (pAttrib) {
        printf("%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());

        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) printf(" int=%d", ival);
        if (pAttrib->QueryDoubleValue(&dval) == TIXML_SUCCESS) printf(" d=%1.1f", dval);
        printf("\n");
        i++;
        pAttrib = pAttrib->Next();
    }
    return i;
}

void dump_to_stdout(TiXmlNode* pParent, unsigned int indent = 0) {
    if (!pParent) return;

    TiXmlNode* pChild;
    TiXmlText* pText;
    int t = pParent->Type();
    printf("%s", getIndent(indent));
    int num;

    switch (t) {
        case TiXmlNode::TINYXML_DOCUMENT:
            printf("Document");
            break;

        case TiXmlNode::TINYXML_ELEMENT:
            printf("Element [%s]", pParent->Value());
            num = dump_attribs_to_stdout(pParent->ToElement(), indent + 1);
            switch (num) {
                case 0:
                    printf(" (No attributes)");
                    break;
                case 1:
                    printf("%s1 attribute", getIndentAlt(indent));
                    break;
                default:
                    printf("%s%d attributes", getIndentAlt(indent), num);
                    break;
            }
            break;

        case TiXmlNode::TINYXML_COMMENT:
            printf("Comment: [%s]", pParent->Value());
            break;

        case TiXmlNode::TINYXML_UNKNOWN:
            printf("Unknown");
            break;

        case TiXmlNode::TINYXML_TEXT:
            pText = pParent->ToText();
            printf("Text: [%s]", pText->Value());
            break;

        case TiXmlNode::TINYXML_DECLARATION:
            printf("Declaration");
            break;
        default:
            break;
    }
    printf("\n");
    for (pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
        dump_to_stdout(pChild, indent + 1);
    }
}

Shape* readShape(TiXmlNode* pShape) {
    if (pShape->Value() == "line") {
        int* x1;
        int* y1;
        int* x2;
        int* y2;
        int width = 1;
        Pixel color = COLOR_BLACK;

        TiXmlAttribute* pAttrib = pShape->ToElement()->FirstAttribute();
        int ival;
        while (pAttrib) {
            if (pAttrib->Name() == "x1") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) x1 = new int(ival);
            } else if (pAttrib->Name() == "y1") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) y1 = new int(ival);
            } else if (pAttrib->Name() == "x2") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) x2 = new int(ival);
            } else if (pAttrib->Name() == "y2") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) y2 = new int(ival);
            } else if (pAttrib->Name() == "width") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) width = ival;
            } else if (pAttrib->Name() == "color") {
                color = GET_COLOR(pAttrib->Value());
            }

            pAttrib = pAttrib->Next();
        }

        if (x1 == nullptr || x2 == nullptr || y1 == nullptr || y2 == nullptr) {
            std::cout << "Unable to create line with given parameters\n";
            return nullptr;
        }

        Shape* s = new Line(Point(*x1, *y1), Point(*x2, *y2), width, color);
        delete x1;
        delete y1;
        delete x2;
        delete y2;
        return s;
    } else if (pShape->Value() == "polyline") {
    } else if (pShape->Value() == "polygon") {
    } else if (pShape->Value() == "circle") {
        int* x;
        int* y;
        int* radius;
        Pixel *fill_color;
        Pixel stroke_color = COLOR_BLACK;
        
        TiXmlAttribute* pAttrib = pShape->ToElement()->FirstAttribute();
        int ival;
        while (pAttrib) {
            if (pAttrib->Name() == "x") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) x = new int(ival);
            } else if (pAttrib->Name() == "y") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) y = new int(ival);
            } else if (pAttrib->Name() == "radius") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) radius = new int(ival);
            } else if (pAttrib->Name() == "fill_color") {
                fill_color = new Pixel(GET_COLOR(pAttrib->Value()));
            } else if (pAttrib->Name() == "stroke_color") {
                stroke_color = GET_COLOR(pAttrib->Value());
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
        delete x;
        delete y;
        delete radius;
        if (fill_color != nullptr) delete fill_color;
        return s;
    }
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
    if (!pParent) return;

    int t = pParent->Type();
    switch (t) {
        case TiXmlNode::TINYXML_ELEMENT:
            if (pParent->Value() == "canvas") {
                int height = -1;
                int width = -1;
                Pixel color = COLOR_WHITE;

                TiXmlAttribute* pAttrib = pParent->ToElement()->FirstAttribute();
                int ival;
                while (pAttrib) {
                    if (pAttrib->Name() == "width") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) width = ival;
                    } else if (pAttrib->Name() == "height") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) height = ival;
                    } else if (pAttrib->Name() == "color") {
                        color = GET_COLOR(pAttrib->Value());
                    }

                    pAttrib = pAttrib->Next();
                }

                if (width < 0 || height < 0) {
                    std::cout << "Please specify positive values for canvas width and height\n";
                    return nullptr;
                }

                Canvas* canvas = new Canvas(width, height, color);
                addShapesToCanvas(canvas, pParent);
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
    if (doc.LoadFile()) {
        dump_to_stdout(&doc);
    } else {
        std::cout << "dekinai\n";
    }

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