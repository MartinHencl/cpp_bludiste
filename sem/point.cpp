#include "point.h"


int Point::Hash(const Point & p)
{
	return 11 * p.x + p.y;
}

bool Point::Equal(const Point & p1, const Point & p2)
{
	if ((p1.x == p2.x) && (p1.y == p2.y)) {
		return true;
	}
	return false;
	}

Point::Point()
{
	x = 0;
	y = 0;
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}