#ifndef __POINT_H
#define __POINT_H

// EDITOVATELN� SOUBOR
#include "Vyjimky.h"

struct Point {
public:
	// ve�ejn� p��stupn� atributy:
	// - celo��seln� datov� slo�ky x, y
	int x;
	int y;

	// statick� metoda Hash, vyhovuj�c� typu HashFunction<Point>
	// - metoda pou�ita pro hash mno�inu
	// - vypo��t� hash jako: h(point) = 11 * point[x] + point[y]
	// static int Hash();
	static int Hash(const Point& p);

	// statick� metoda Equals, vyhovuj�c� typu EqualFunction<Point>
	// - metoda pou�ita pro hash mno�inu
	// - vrac� true, pokud dva body maj� shodn� ob� sou�adnice
	// static bool Equals(Point point2);
	static bool Point::Equal(const Point & p1, const  Point & p2);

	Point();
	Point(int x, int y);

private:

};

#endif