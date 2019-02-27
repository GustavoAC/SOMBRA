#include "line.h"
#include "canvas.h"
#include <functional>
#include <iostream>
#include <cmath>

Line::Line(const Point &_start, const Point &_end, const Pixel &_color)
    : m_start(_start), m_end(_end), m_color(_color) {}

Line::Line(const Point &_start, const Point &_end) : Line(_start, _end, Pixel(0, 0, 0)) {}

void Line::draw(Canvas *canvas) {
    // if (isHorizontal()) {
    //     int step = (m_start.getX() < m_end.getX()) ? 1 : -1;
    //     for (int i = m_start.getX(); i != m_end.getX(); i += step)
    //         canvas.setPixel(Point(i, m_start.getY()), m_color);
    //     canvas.setPixel(m_end, m_color);
    // } else if (isVertical()) {
    //     int step = (m_start.getY() < m_end.getY()) ? 1 : -1;
    //     for (int i = m_start.getY(); i != m_end.getY(); i += step)
    //         canvas.setPixel(Point(m_start.getX(), i), m_color);
    //     canvas.setPixel(m_end, m_color);
    if (is45DegreeDiagonal()) {
        int step = (m_start.getX() < m_end.getX()) ? 1 : -1;
        int lastY = m_start.getY();

        for (int i = m_start.getX(); i != m_end.getX(); i += step) {
            canvas->setPixel(Point(i, lastY), m_color);
            lastY += step;
        }
        canvas->setPixel(m_end, m_color);
    } else {
        drawBresenham(canvas);
    }
}

void Line::drawDDA(Canvas *canvas) {
    int deltaX = m_end.getX() - m_start.getX();
    int deltaY = m_end.getY() - m_start.getY();

    bool isXMaster = (std::abs(deltaX) > std::abs(deltaY));
    auto getMasterParam = (isXMaster) ? ([](Point &p) -> int { return p.getX(); })
                                      : ([](Point &p) -> int { return p.getY(); });
    auto getSlaveParam = (isXMaster) ? ([](Point &p) -> int { return p.getY(); })
                                     : ([](Point &p) -> int { return p.getX(); });

    std::function<void(int, int)> drawPoint;
    if (isXMaster)
        drawPoint = ([this, canvas](int master, int slave) {
            canvas->setPixel(Point(master, slave), m_color);
        });
    else
        drawPoint = ([this, canvas](int master, int slave) {
            canvas->setPixel(Point(slave, master), m_color);
        });

    Point *start, *end;
    if (getMasterParam(m_start) < getMasterParam(m_end)) {
        start = &m_start;
        end = &m_end;
    } else {
        start = &m_end;
        end = &m_start;
    }

    int master;
    float dMaster, dSlave, slave, m;
    dSlave = getSlaveParam(*end) - getSlaveParam(*start);
    dMaster = getMasterParam(*end) - getMasterParam(*start);
    m = dSlave/dMaster;
    slave = getSlaveParam(*start);
    
    for(master = getMasterParam(*start); master <= getMasterParam(*end); master++ ) {
        drawPoint(master, slave);
        slave += m;
    }
}

void Line::drawBresenham(Canvas *canvas) {
    int deltaX = m_end.getX() - m_start.getX();
    int deltaY = m_end.getY() - m_start.getY();

    bool isXMaster = (std::abs(deltaX) > std::abs(deltaY));
    auto getMasterParam = (isXMaster) ? ([](Point &p) -> int { return p.getX(); })
                                      : ([](Point &p) -> int { return p.getY(); });
    auto getSlaveParam = (isXMaster) ? ([](Point &p) -> int { return p.getY(); })
                                     : ([](Point &p) -> int { return p.getX(); });

    std::function<void(int, int)> drawPoint;
    if (isXMaster)
        drawPoint = ([this, canvas](int master, int slave) {
            canvas->setPixel(Point(master, slave), m_color);
        });
    else
        drawPoint = ([this, canvas](int master, int slave) {
            canvas->setPixel(Point(slave, master), m_color);
        });

    Point *start, *end;
    if (getMasterParam(m_start) < getMasterParam(m_end)) {
        start = &m_start;
        end = &m_end;
    } else {
        start = &m_end;
        end = &m_start;
    }

    int deltaMaster = getMasterParam(*end) - getMasterParam(*start);
    int deltaSlave = getSlaveParam(*end) - getSlaveParam(*start);
    int slaveStep = (deltaSlave > 0) ? 1 : -1;

    if (deltaSlave < 0) deltaSlave *= -1;
    int p = 2 * deltaSlave - deltaMaster;
    int master = getMasterParam(*start);
    int slave = getSlaveParam(*start);

    drawPoint(master, slave);
    for (; master <= getMasterParam(*end); master++) {
        if (p < 0) {
            p += 2 * deltaSlave;
        } else {
            slave += slaveStep;
            p += 2 * deltaSlave - 2 * deltaMaster;
        }
        drawPoint(master, slave);
    }
}

inline bool Line::isHorizontal() const { return m_start.getY() == m_end.getY(); }

inline bool Line::isVertical() const { return m_start.getX() == m_end.getX(); }

inline bool Line::is45DegreeDiagonal() const {
    return (m_end.getX() - m_start.getX()) - (m_end.getY() - m_start.getY()) == 0;
}