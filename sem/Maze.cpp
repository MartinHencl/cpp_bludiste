#include "Maze.h"

Maze::Maze()
{
	vstupDoBludisteX = 0;
	vstupDoBludisteY = 0;
	vychodZBludisteX = 0;
	vychodZBludisteY = 0;
	pocetRadku = 0;
	pocetSloupcu = 0;
}

Maze::~Maze()
{
	for (int i = 0; i < pocetRadku; i++) {
		delete[] bludiste[i];
	}
	delete[] bludiste;
}

bool Maze::isValidPoint(Point pt) const
{
	if ((pt.x < pocetSloupcu) && (pt.x >= 0)){
		if ((pt.y < pocetRadku) && (pt.y >= 0)){
			return true;
		}
		return false;
	}
	return false;
}

char Maze::getPoint(Point pt) const
{
	if (isValidPoint(pt)) {
		return bludiste[pt.x][pt.y];
	}
	else {
		throw IndexMimoRozsahException();
	}
}

int Maze::getR() const
{
	return pocetRadku;
}

int Maze::getC() const
{
	return pocetSloupcu;
}

Point Maze::getStart() const
{
	Point tempPoint{vstupDoBludisteX, vstupDoBludisteY};
	return tempPoint;
}

Point Maze::getEnd() const
{
	Point tempPoint{ vychodZBludisteX, vychodZBludisteY };
	return tempPoint;
}

Maze * Maze::fromFile(string filename)
{
	try {
		// Formát souboru:
		// 7 7        <-- poèet øádkù a sloupcù v bludišti
		// 2 0        <-- èíslo øádku a sloupce vstupu do bludištì
		// 3 6        <-- èíslo øádku a sloupce výstupu z bludištì
		// #######
		// ##.##.#
		// ....#.#
		// ###.#..    <-- bludištì uložené jako jednotlivé znaky
		// #...#.#        každý øádek je ukonèen znaky odøádkování
		// #.#...#
		// #######
		Maze* tempMaze = new Maze{};
		int radky = 0;
		int sloupce = 0;
		int vstupX = 0;
		int vstupY = 0;
		int vychodX = 0;
		int vychodY = 0;
		char** tempBludiste;

		ifstream soubor(filename);
		if (soubor.is_open()) {
		string strNumber1;
		string strNumber2;
		getline(soubor, strNumber1, ' ');
		getline(soubor, strNumber2);
		radky = stoi(strNumber1);
		sloupce = stoi(strNumber2);
		tempMaze->pocetRadku = radky;
		tempMaze->pocetSloupcu = sloupce;

		getline(soubor, strNumber1, ' ');
		getline(soubor, strNumber2);
		vstupX = stoi(strNumber1);
		vstupY = stoi(strNumber2);
		tempMaze->vstupDoBludisteX = vstupX;
		tempMaze->vstupDoBludisteY = vstupY;

		getline(soubor, strNumber1, ' ');
		getline(soubor, strNumber2);
		vychodX = stoi(strNumber1);
		vychodY = stoi(strNumber2);
		tempMaze->vychodZBludisteX = vychodX;
		tempMaze->vychodZBludisteY = vychodY;

		tempBludiste = new char*[radky];
		for (int i = 0; i < radky; i++) {
			string jedenRadek;
			getline(soubor, jedenRadek);
			tempBludiste[i] = new char[sloupce];
			for (int j = 0; j < sloupce; j++) {
				tempBludiste[i][j] = jedenRadek.at(j);
			}
		}
		soubor.close();
		tempMaze->bludiste = tempBludiste;
		return tempMaze;
		}
		else {
			throw SouborNenalezenException();
		}
	}
	catch (SouborNenalezenException ex) {
		cout << ex.what() << endl;
	}
}

char ** Maze::getMaze()
{
	return this->bludiste;
}

void Maze::vykresliBludiste()
{
	for (int i = 0; i < pocetRadku; i++) {
		for (int j = 0; j < pocetSloupcu; j++) {
			cout << bludiste[i][j];
		}
		cout << endl;
	}
}
