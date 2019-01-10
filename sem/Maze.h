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

	// Vrací true, pokud jsou souøadnice platné
	bool isValidPoint(Point pt) const override;

	// Vrací znak podle souøadnic (neplatné souøadnice vyvolají výjimku)
	char getPoint(Point pt) const override;

	// Vrací poèet øádkù bludištì
	int getR() const override;

	// Vrací poèet sloupcù bludištì
	int getC() const override;

	// Vrací polohu poèátku bludištì
	Point getStart() const override;

	// Vrací polohu konce bludištì
	Point getEnd() const override;

	// Naète bludištì ze souboru
	static Maze* fromFile(string filename);

	char** getMaze();
	void vykresliBludiste();

private:
	// atributy:
	// - pro uložení stavu bludištì
	int vstupDoBludisteX;
	int vstupDoBludisteY;
	int vychodZBludisteX;
	int vychodZBludisteY;
	char** bludiste;
	int pocetRadku;
	int pocetSloupcu;
};
#endif // !_MAZE_H_