#include <iostream>
#include <memory>
#include <vector>
#include "canvas.h"
#include "circle.h"
#include "line.h"
#include "point.h"
#include "polygon.h"
#include "polyline.h"
#include "tinyxml.h"

Pixel GET_COLOR(const std::string& colorName) {
    if (colorName == "black") return COLOR_BLACK;
    if (colorName == "red") return COLOR_RED;
    if (colorName == "green") return COLOR_GREEN;
    if (colorName == "blue") return COLOR_BLUE;
    if (colorName == "cyan") return COLOR_CYAN;
    if (colorName == "yellow") return COLOR_YELLOW;
    if (colorName == "magenta") return COLOR_MAGENTA;
    if (colorName == "orange") return COLOR_ORANGE;
    if (colorName == "purple") return COLOR_PURPLE;

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
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS)
                    x1 = std::make_shared<int>(ival);
            } else if (attribName == "y1") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS)
                    y1 = std::make_shared<int>(ival);
            } else if (attribName == "x2") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS)
                    x2 = std::make_shared<int>(ival);
            } else if (attribName == "y2") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS)
                    y2 = std::make_shared<int>(ival);
            } else if (attribName == "width") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) width = ival;
            } else if (attribName == "color") {
                color = GET_COLOR(std::string(pAttrib->Value()));
            } else if (attribName == "color_r") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) color.setR(ival);
            } else if (attribName == "color_g") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) color.setG(ival);
            } else if (attribName == "color_b") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) color.setB(ival);
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
                color = GET_COLOR(std::string(pAttrib->Value()));
            } else if (attribName == "color_r") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) color.setR(ival);
            } else if (attribName == "color_g") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) color.setG(ival);
            } else if (attribName == "color_b") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) color.setB(ival);
            }

            pAttrib = pAttrib->Next();
        }
        Polyline* s = new Polyline(color, width);

        TiXmlNode* pChild;
        for (pChild = pShape->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
            if (pChild->Type() == TiXmlNode::TINYXML_ELEMENT &&
                std::string(pChild->Value()) == "point") {
                std::shared_ptr<int> x;
                std::shared_ptr<int> y;

                TiXmlAttribute* pAttrib = pChild->ToElement()->FirstAttribute();
                int ival;
                while (pAttrib) {
                    std::string attribName(pAttrib->Name());
                    if (attribName == "x") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS)
                            x = std::make_shared<int>(ival);
                    } else if (attribName == "y") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS)
                            y = std::make_shared<int>(ival);
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
            } else if (attribName == "stroke_color_r") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) stroke_color.setR(ival);
            } else if (attribName == "stroke_color_g") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) stroke_color.setG(ival);
            } else if (attribName == "stroke_color_b") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) stroke_color.setB(ival);
            } else if (attribName == "fill_color_r") {
                if (fill_color == nullptr) fill_color = std::make_shared<Pixel>(COLOR_BLACK);
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) fill_color->setR(ival);
            } else if (attribName == "fill_color_g") {
                if (fill_color == nullptr) fill_color = std::make_shared<Pixel>(COLOR_BLACK);
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) fill_color->setG(ival);
            } else if (attribName == "fill_color_b") {
                if (fill_color == nullptr) fill_color = std::make_shared<Pixel>(COLOR_BLACK);
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) fill_color->setB(ival);
            }

            pAttrib = pAttrib->Next();
        }

        std::vector<Point> points;

        TiXmlNode* pChild;
        for (pChild = pShape->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
            if (pChild->Type() == TiXmlNode::TINYXML_ELEMENT &&
                std::string(pChild->Value()) == "point") {
                std::shared_ptr<int> x;
                std::shared_ptr<int> y;

                TiXmlAttribute* pAttrib = pChild->ToElement()->FirstAttribute();
                int ival;
                while (pAttrib) {
                    std::string attribName(pAttrib->Name());
                    if (attribName == "x") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS)
                            x = std::make_shared<int>(ival);
                    } else if (attribName == "y") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS)
                            y = std::make_shared<int>(ival);
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

        Polygon* s = new Polygon(points, stroke_color, width);
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
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS)
                    radius = std::make_shared<int>(ival);
            } else if (attribName == "fill_color") {
                fill_color = std::make_shared<Pixel>(GET_COLOR(std::string(pAttrib->Value())));
            } else if (attribName == "stroke_color") {
                stroke_color = GET_COLOR(std::string(pAttrib->Value()));
            } else if (attribName == "stroke_color_r") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) stroke_color.setR(ival);
            } else if (attribName == "stroke_color_g") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) stroke_color.setG(ival);
            } else if (attribName == "stroke_color_b") {
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) stroke_color.setB(ival);
            } else if (attribName == "fill_color_r") {
                if (fill_color == nullptr) fill_color = std::make_shared<Pixel>(COLOR_BLACK);
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) fill_color->setR(ival);
            } else if (attribName == "fill_color_g") {
                if (fill_color == nullptr) fill_color = std::make_shared<Pixel>(COLOR_BLACK);
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) fill_color->setG(ival);
            } else if (attribName == "fill_color_b") {
                if (fill_color == nullptr) fill_color = std::make_shared<Pixel>(COLOR_BLACK);
                if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) fill_color->setB(ival);
            }

            pAttrib = pAttrib->Next();
        }

        if (x == nullptr || y == nullptr || radius == nullptr) {
            std::cout << "Unable to create circle with given parameters\n";
            return nullptr;
        }

        Shape* s;
        if (fill_color == nullptr)
            s = new Circle(Point(*x, *y), *radius, stroke_color);
        else
            s = new Circle(Point(*x, *y), *radius, stroke_color, *fill_color);

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
                    } else if (attribName == "color_r") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) color.setR(ival);
                    } else if (attribName == "color_g") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) color.setG(ival);
                    } else if (attribName == "color_b") {
                        if (pAttrib->QueryIntValue(&ival) == TIXML_SUCCESS) color.setB(ival);
                    }

                    pAttrib = pAttrib->Next();
                }

                if (width < 0 || height < 0) {
                    std::cout << "Please specify positive values for canvas width and height\n";
                    return nullptr;
                }

                std::cout << "Creating Canvas...\n";
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
    if (argc < 2) {
        std::cout << "Please insert the xml description path as an argument" << std::endl;
        return 1;
    }

    TiXmlDocument doc(argv[1]);
    if (!doc.LoadFile()) {
        std::cout << "Cannot parse the file\n";
        return 1;
    }

    Canvas* canvas = createCanvas(&doc);

    if (argc > 2)
        canvas->writeToFile(argv[2]);
    else
        canvas->writeToFile(argv[1]);
    delete canvas;

    return 0;
}