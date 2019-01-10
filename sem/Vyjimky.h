#ifndef _VYJIMKY_H
#define _VYJIMKY_H

#include <string>

struct IndexMimoRozsahException : public std::exception {
public:
	virtual const char* what() const throw () {
		return "Index je mimo rozsah naalokovaneho pole";
	}
};

struct BodNemaZnakException : public std::exception {
public:
	virtual const char* what() const throw () {
		return "Bod jeste nema zadny znak";
	}
};

struct SouborNenalezenException : public std::exception {
public:
	virtual const char* what() const throw () {
		return "Zadany soubor nelze otevrit";
	}
};
#endif // !_VYJIMKY_H

/* testy, kdyz ty hlavni delaji kraviny */
	/* TEST DynArray bez testu pameti memleak */
	/*DynArray<int> da{};

	if (da.count() == 0) { cout << "0 OK" << endl; };

	da.add(1);

	if (da.count() == 1) { cout << "1 OK" << endl; };
	if (da.get(0) == 1) { cout << "1 OK" << endl; };

	da.add(2);

	if (da.count() == 2) { cout << "2 OK" << endl; };
	if (da.get(0) == 1) { cout << "1 OK" << endl; };
	if (da.get(1) == 2) { cout << "2 OK" << endl; };

	try {
		da.get(3);
	}
	catch (IndexMimoRozsahException& ex) {
		cout << ex.what() << endl;
	}

	da.add(3);
	da.add(4);
	da.add(5);
	da.add(6);
	da.add(7);
	da.add(8);
	da.add(9);
	da.add(10);
	da.add(11);
	da.add(12);*/

/* test MAZE */
/*string levelfile = "level0" + to_string(0) + ".dat";
	Maze* m = Maze::fromFile(levelfile);
	m->vykresliBludiste();*/