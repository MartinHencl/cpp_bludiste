#ifndef __POINT_H
#define __POINT_H

// EDITOVATELNÝ SOUBOR
#include "Vyjimky.h"

struct Point {
public:
	// veøejnì pøístupné atributy:
	// - celoèíselné datové složky x, y
	int x;
	int y;

	// statická metoda Hash, vyhovující typu HashFunction<Point>
	// - metoda použita pro hash množinu
	// - vypoèítá hash jako: h(point) = 11 * point[x] + point[y]
	// static int Hash();
	static int Hash(const Point& p);

	// statická metoda Equals, vyhovující typu EqualFunction<Point>
	// - metoda použita pro hash množinu
	// - vrací true, pokud dva body mají shodné obì souøadnice
	// static bool Equals(Point point2);
	static bool Point::Equal(const Point & p1, const  Point & p2);

	Point();
	Point(int x, int y);

private:

};

#endif