#include "line.h"
#include <cmath>
#include <functional>
#include <iostream>
#include "canvas.h"
#include "polygon.h"

Line::Line(const Point &_start, const Point &_end, const int &_width, const Pixel &_color)
    : m_start(_start), m_end(_end), m_color(_color), m_width(_width) {}

void Line::draw(Canvas *canvas) {
    if (m_width > 1) {
        drawThickLine(canvas);
        return;
    }

    std::cout << "Drawing line...\n\n";
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

void Line::drawThickLine(Canvas *canvas) {
    int deltaX = m_end.getX() - m_start.getX();
    int deltaY = m_end.getY() - m_start.getY();

    // inverted since you want the m is also inverted
    bool isXMaster = (std::abs(deltaX) < std::abs(deltaY));

    int masterNegDeviation = -m_width / 2;
    int masterPosDeviation = (m_width - 1) / 2;

    float invertedM;
    if (!isHorizontal() && !isVertical()) invertedM = -1 * deltaY / (float)deltaX;

    int slaveNegDeviation = 0;
    int slavePosDeviation = 0;

    if (isXMaster) {
        // Y is slave
        if (!isVertical()) {
            slaveNegDeviation = std::round(masterNegDeviation * invertedM);
            slavePosDeviation = std::round(masterPosDeviation * invertedM);
        }
    } else {
        // X is slave
        if (!isHorizontal()) {
            slaveNegDeviation = std::round(masterNegDeviation / invertedM);
            slavePosDeviation = std::round(masterPosDeviation / invertedM);
        }
    }

    if (isXMaster) {
        Point startPos(m_start.getX() + masterPosDeviation, m_start.getY() + slavePosDeviation);
        Point startNeg(m_start.getX() + masterNegDeviation, m_start.getY() + slaveNegDeviation);
        Point endPos(m_end.getX() + masterPosDeviation, m_end.getY() + slavePosDeviation);
        Point endNeg(m_end.getX() + masterNegDeviation, m_end.getY() + slaveNegDeviation);

        Polygon p(startPos, endPos, endNeg, startNeg, m_color, m_color);
        canvas->draw(p);
    } else {
        Point startPos(m_start.getX() + slavePosDeviation, m_start.getY() + masterPosDeviation);
        Point startNeg(m_start.getX() + slaveNegDeviation, m_start.getY() + masterNegDeviation);
        Point endPos(m_end.getX() + slavePosDeviation, m_end.getY() + masterPosDeviation);
        Point endNeg(m_end.getX() + slaveNegDeviation, m_end.getY() + masterNegDeviation);

        Polygon p(startPos, endPos, endNeg, startNeg, m_color, m_color);
        canvas->draw(p);
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

    int step = (getMasterParam(m_start) < getMasterParam(m_end)) ? 1 : -1;

    int master;
    float dMaster, dSlave, slave, m;
    dSlave = getSlaveParam(m_end) - getSlaveParam(m_start);
    dMaster = getMasterParam(m_end) - getMasterParam(m_start);
    m = dSlave / dMaster * step;
    slave = getSlaveParam(m_start);

    // Draw until right before end point
    for (master = getMasterParam(m_start); master != getMasterParam(m_end); master += step) {
        drawPoint(master, slave);
        slave += m;
    }

    // Draw endpoint
    drawPoint(master, slave);
}

void Line::drawBresenham(Canvas *canvas) {
    int deltaX = m_end.getX() - m_start.getX();
    int deltaY = m_end.getY() - m_start.getY();

    // sets function for retrieving correct master and slave coordinates
    bool isXMaster = (std::abs(deltaX) > std::abs(deltaY));
    auto getMasterParam = (isXMaster) ? ([](Point &p) -> int { return p.getX(); })
                                      : ([](Point &p) -> int { return p.getY(); });
    auto getSlaveParam = (isXMaster) ? ([](Point &p) -> int { return p.getY(); })
                                     : ([](Point &p) -> int { return p.getX(); });

    // Draws a point using the correct coordinate system
    std::function<void(int, int)> drawPoint;
    if (isXMaster)
        drawPoint = ([this, canvas](int master, int slave) {
            canvas->setPixel(Point(master, slave), m_color);
        });
    else
        drawPoint = ([this, canvas](int master, int slave) {
            canvas->setPixel(Point(slave, master), m_color);
        });

    // Calculates master and slave deltas
    int deltaMaster = getMasterParam(m_end) - getMasterParam(m_start);
    int deltaSlave = getSlaveParam(m_end) - getSlaveParam(m_start);

    // Invert values if negative and sets correct step
    int masterStep = (deltaMaster > 0) ? 1 : -1;
    int slaveStep = (deltaSlave > 0) ? 1 : -1;

    if (deltaSlave < 0) deltaSlave *= -1;
    if (deltaMaster < 0) deltaMaster *= -1;

    // Initialize values
    int p = ((isXMaster) ? 2 : -2) * deltaSlave - deltaMaster;
    int master = getMasterParam(m_start);
    int slave = getSlaveParam(m_start);

    // Sets for condition
    auto forCondition = (getMasterParam(m_end) > getMasterParam(m_start))
                            ? ([](int master, int limit) -> bool { return master <= limit; })
                            : ([](int master, int limit) -> bool { return master >= limit; });

    // Draw points
    drawPoint(master, slave);
    for (; forCondition(master, getMasterParam(m_end)); master += masterStep) {
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