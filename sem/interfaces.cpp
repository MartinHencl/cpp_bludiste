#include "framework.h"
#include "interfaces.h"

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//                       !!!!!!!!!!!!!!!!!!!!!!!!!!
//                       !!! NEM�NITELN� SOUBOR !!!
//                       !!!!!!!!!!!!!!!!!!!!!!!!!!
//
// Tento soubor obsahuje zad�n� a rozhan�, kter� nen� dovoleno m�nit !
// Jednotliv� implementace realizujte v nov�ch souborech.
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Metoda show() slou�� k vykreslen� aktu�ln�ho stavu prohled�v�n� bludi�t� do konzole.
void IMazeSolver::show() {
	char* p = createVisualisation();
	Framework::vypisProstredi(p, getMaze()->getR(), getMaze()->getC());
	delete[] p;

	Framework::waitFor(0.02);
}

// Intern� metoda createvisualisation() p�ipravuje pole pro vykreslen� metodou show().
char* IMazeSolver::createVisualisation() {
	char* p = new char[getMaze()->getC() * getMaze()->getR()];

	for (int i = 0; i < getMaze()->getR(); i++) {
		for (int j = 0; j < getMaze()->getC(); j++) {
			Point pt{ j,i };
			char ch = 'n';
			char maze = getMaze()->getPoint(pt);

			if (maze == '#')
				ch = 'N';
			else if (isInCurrentHistory(pt))
				ch = 'R';
			else if (isInAllHistory(pt))
				ch = 'B';

			p[i*getMaze()->getC() + j] = ch;
		}
	}

	return p;
}