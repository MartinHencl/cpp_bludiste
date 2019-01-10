#include "framework.h"
#include "interfaces.h"

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//                       !!!!!!!!!!!!!!!!!!!!!!!!!!
//                       !!! NEMÌNITELNÝ SOUBOR !!!
//                       !!!!!!!!!!!!!!!!!!!!!!!!!!
//
// Tento soubor obsahuje zadání a rozhaní, která není dovoleno mìnit !
// Jednotlivé implementace realizujte v nových souborech.
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Metoda show() slouží k vykreslení aktuálního stavu prohledávání bludištì do konzole.
void IMazeSolver::show() {
	char* p = createVisualisation();
	Framework::vypisProstredi(p, getMaze()->getR(), getMaze()->getC());
	delete[] p;

	Framework::waitFor(0.02);
}

// Interní metoda createvisualisation() pøipravuje pole pro vykreslení metodou show().
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