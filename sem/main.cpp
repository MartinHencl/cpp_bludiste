// Chci zkompilovat testy? (pokud ano - odkomentuji n�sleduj�c� ��dek)
//#define COMPILE_TESTS
#ifdef COMPILE_TESTS
// Chci spustit testy? (pokud ano - odkomentuji n�sleduj�c� ��dek)
#define RUN_TESTS

// Kter� testy chci kompilovat a spustit?
#define TEST_POINT
#define TEST_HASHSET
#define TEST_DYNARRAY
#endif

#include <iostream>
#include "framework.h"
#include "interfaces.h"

//#include "HashSet.h"
//#include "DynArray.h"
#include "Maze.h"
#include "MazeSolver.h"

#include <windows.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

/*
================================== ZAD�N� - SEMESTR�LN� PR�CE C++ I. ======================================

Z�kladn�m po�adavkem je dokon�it implementaci pomoc� jazyka C++ dle standardu 14882:2017 (�C++17�). 
Nen� p��pustn� vyu��vat nestandardizovan� roz���en� jazyka (nap�. C++/CLI). Pou�it� jak�koliv knihovny 
(mimo standard jazyka/STL) je t�eba dop�edu konzultovat, jinak nem��e b�t k�d akceptov�n.

* Struktury, kter� je t�eba realizovat jsou pops�ny pomoc� rozhran� v souboru point.h a interfaces.h. 
  Implementaci vytvo�te ve V�mi nov� vytvo�en�ch souborech. Dopl�te do main.cpp pot�ebn� direktivy #include.
* P�ipraven� rozhran� je nutn� zcela dodr�et. Detaily vizte p�ilo�en� soubory. ��ste�n� implementace 
  je ji� navr�ena�
* Ve�ker� dynamick� pam� mus� b�t korektn� dealokov�na. Nen� p��pustn� nechat pam� alokovanou d�le 
  ne� je to nutn�.
* Struktury IHashSet a IDynArray nen� mo�n� nahradit ekvivalentem z STL nebo jin� knihovny, ani pro jeho 
  realizaci pou��t knihovny.
* Pro struktury Point, HashSet a DynArray jsou p�ipraveny z�kladn� sady test�, kter� ov��uj� z�kladn� 
  funkcionalitu.
* Nen� dovoleno vyu��vat glob�ln� a statick� prom�nn�. Program vypracovan� pro platformu Windows mus� 
  obsahovat projektov� soubory pro Visual Studio 2013 nebo nov�j��, pomoc� kter�ch jde program p�elo�it. 
  Pro unixov� platformy mus� b�t p�ilo�en makefile. Zdrojov� k�dy, kter� nen� mo�n� p�elo�it (chyb�j�c� 
  projektov�/zdrojov� soubory, syntaktick� chyby v k�du), nebudou akceptov�ny.

P�ed odevzd�n�m mus� b�t projekt uklizen od ve�ker�ch bin�rn�ch soubor� (spustiteln�ch, tmp, cache, 
objektov�ch � pomoc� Build � Clean solution | make clean). Vy�i�t�n� zdrojov� k�dy v�etn� soubor� projektu 
odevzd�vejte ve form�tu ZIP.

Nejzaz�� term�n odevzd�n� semestr�ln� pr�ce je 31. 12. 2018 23:59.

Semestr�ln� pr�ce mus� b�t vypracov�na samostatn�, nen� p��pustn� ��dn� shoda s jinou prac�. Student mus� 
b�t schopen vytvo�enou pr�ci okomentovat a vysv�tlit p�i �stn� obhajob�.

================================== ZAD�N� - SEMESTR�LN� PR�CE C++ I. ======================================
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef COMPILE_TESTS
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "tests.hpp"
#endif

int main() {
#ifdef RUN_TESTS
	Catch::Session().run();
	cin.get();
	exit(0);
#else
	Framework::System::init();

	//for (int level = 0; level <= 2; level++) {
	int level = 1;
	COORD newSize = { 100,9000 };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), newSize);

		string levelfile = "level0" + to_string(level) + ".dat";
		string solutionfile = "solution0" + to_string(level) + ".txt";

		Maze* m = Maze::fromFile(levelfile);
		MazeSolver* mz = new MazeSolver(m);
		/*if (mz->solve())
			mz->saveMazeAndSolution(solutionfile);*/
		if (mz->solve()) {
			mz->show();
		}
		else {
			cout << "Bludiste level0" + to_string(level) + ".dat nema reseni" << endl;
		}

		delete mz;
		delete m;
	//}

#endif
	return 0;
}