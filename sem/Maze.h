#ifndef _MAZE_H_
#define _MAZE_H_

#include <iostream>
#include <fstream>
#include <string>
#include "interfaces.h"
#include "point.h"
#include "Vyjimky.h"

using namespace std;

struct Maze : IMaze {
public:
	Maze();
	~Maze();

	// Vrac� true, pokud jsou sou�adnice platn�
	bool isValidPoint(Point pt) const override;

	// Vrac� znak podle sou�adnic (neplatn� sou�adnice vyvolaj� v�jimku)
	char getPoint(Point pt) const override;

	// Vrac� po�et ��dk� bludi�t�
	int getR() const override;

	// Vrac� po�et sloupc� bludi�t�
	int getC() const override;

	// Vrac� polohu po��tku bludi�t�
	Point getStart() const override;

	// Vrac� polohu konce bludi�t�
	Point getEnd() const override;

	// Na�te bludi�t� ze souboru
	static Maze* fromFile(string filename);

	char** getMaze();
	void vykresliBludiste();

private:
	// atributy:
	// - pro ulo�en� stavu bludi�t�
	int vstupDoBludisteX;
	int vstupDoBludisteY;
	int vychodZBludisteX;
	int vychodZBludisteY;
	char** bludiste;
	int pocetRadku;
	int pocetSloupcu;
};
#endif // !_MAZE_H_