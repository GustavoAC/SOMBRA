#include <cmath>
#include <numeric>
#include "point.h"

//! Represents the edge of a Polygon. Used in the scan-line algorithm
class Edge {
   public:
    int minY;
    int maxY;
    int x;
    int x_remains;

    int inv_m_whole;
    int inv_m_remains;
    int inv_m_denominator;

    Edge(const Point &p1, const Point &p2) {
        const Point &minYP = (p1.getY() < p2.getY()) ? p1 : p2;
        const Point &maxYP = (p1.getY() < p2.getY()) ? p2 : p1;

        minY = minYP.getY();
        maxY = maxYP.getY();
        x = minYP.getX();
        x_remains = 0;

        int deltaX = maxYP.getX() - minYP.getX();
        int deltaY = maxYP.getY() - minYP.getY();

        if (deltaY != 0 && deltaX != 0) {
            int gcd = std::gcd(deltaX, deltaY);
            inv_m_denominator = std::abs(deltaY / gcd);
            inv_m_whole = deltaX / deltaY;
            inv_m_remains = (deltaX % deltaY) / gcd;
        } else {
            inv_m_denominator = 0;
            inv_m_whole = 0;
            inv_m_remains = 0;
        }
    }

    //! Updates X to a new point as if the Y was increased by 1
    void updateX() {
        if (inv_m_whole == 0 && inv_m_remains == 0) return;

        x += inv_m_whole;
        x_remains += inv_m_remains;
        if (std::abs(x_remains) >= inv_m_denominator) {
            if (x_remains > 0) {
                x_remains -= inv_m_denominator;
                x++;
            } else {
                x_remains += inv_m_denominator;
                x--;
            }
        }
    }
};
