#include "polygon.h"
#include <iostream>
#include <list>
#include "line.h"

Polygon::Polygon(const std::vector<Point> _points, const Pixel &_stroke_color, const int &_stroke_width)
    : m_points(_points), stroke_color(_stroke_color), stroke_width(_stroke_width) {}

Polygon::Polygon(const Point &p1, const Point &p2, const Point &p3, const Pixel &_stroke_color,
                 const int &_stroke_width)
    : stroke_color(_stroke_color), stroke_width(_stroke_width) {
    m_points.push_back(p1);
    m_points.push_back(p2);
    m_points.push_back(p3);
}

Polygon::Polygon(const Point &p1, const Point &p2, const Point &p3, const Point &p4,
                 const Pixel &_stroke_color, const int &_stroke_width)
    : stroke_color(_stroke_color), stroke_width(_stroke_width) {
    m_points.push_back(p1);
    m_points.push_back(p2);
    m_points.push_back(p3);
    m_points.push_back(p4);
}

void Polygon::setFillColor(const Pixel &color) {
    fill_color = std::make_shared<Pixel>(color);
}

void Polygon::addPoint(const Point &p) { m_points.push_back(p); }

void Polygon::draw(Canvas *canvas) {
    scanFill(canvas);

    if (fill_color == nullptr || stroke_color != *fill_color) {
        for (auto i = 0u; i < m_points.size(); i++) {
            auto line = Line(m_points[i], m_points[(i + 1) % m_points.size()], stroke_width, stroke_color);
            canvas->draw(line);
        }
    }
}

std::pair<Point, Point> Polygon::getBoundingBox() {
    int minX = (m_points.empty()) ? 0 : m_points[0].getX();
    int minY = (m_points.empty()) ? 0 : m_points[0].getY();
    int maxX = minX;
    int maxY = minY;

    for (auto &p : m_points) {
        if (p.getX() < minX) minX = p.getX();
        if (p.getX() > maxX) maxX = p.getX();
        if (p.getY() < minY) minY = p.getY();
        if (p.getY() > maxY) maxY = p.getY();
    }

    return std::pair<Point, Point>(Point(minX, minY), Point(maxX, maxY));
}

std::vector<Edge> Polygon::getEdges() {
    std::vector<Edge> edges;
    for (auto i = 0u; i < m_points.size(); i++)
        edges.push_back(Edge(m_points[i], m_points[(i + 1) % m_points.size()]));

    return edges;
}

void Polygon::scanFill(Canvas *canvas) {
    if (fill_color == nullptr || m_points.empty()) return;
    std::cout << "Starting scanFill\n";

    std::vector<Edge> et[canvas->getHeight()];
    std::list<Edge> aet;
    auto edges = getEdges();
    auto bbox = getBoundingBox();

    // Build up ET
    auto etCount = 0;
    for (auto &e : edges) {
        if (e.minY < canvas->getHeight()) {
            auto it = et[e.minY].begin();
            while (it != et[e.minY].end() && it->minY < e.minY) it++;
            et[e.minY].insert(it, e);

            etCount++;
        }
    }

    // Main loop
    int currentY = bbox.first.getY();
    while (etCount != 0 || !aet.empty()) {
        // Add current edges to aet
        for (auto &e : et[currentY]) {
            if (e.maxY > currentY) {
                auto it = aet.begin();
                while (it != aet.end() && it->x < e.x) it++;
                aet.insert(it, e);
            }

            etCount--;
        }

        // Draw by edge pairs
        for (auto it = aet.begin(); it != aet.end(); it++) {
            auto &e1 = *it++;
            auto &e2 = *it;

            for (auto i = e1.x + 1; i <= e2.x; i++) {
                canvas->setPixel(Point(i, currentY), *fill_color);
            }
        }

        // Update Y and remove old edges
        currentY++;
        auto it = aet.begin();
        while (it != aet.end()) {
            if (it->maxY <= currentY)
                it = aet.erase(it);
            else
                it++;
        }

        // Update x values
        for (auto &e : aet) e.updateX();
    }
}