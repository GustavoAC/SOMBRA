#pragma once

class Point {
private:
	int points[2];
public:
	Point() {}

	Point(int x, int y) {
		points[0] = x;
		points[1] = y;
	}

	void setX(int x) {
		points[0] = x;
	}

	int getX() const {
		return points[0];
	}

	void setY(int y) {
		points[1] = y;
	}

	int getY() const {
		return points[1];
	}
};