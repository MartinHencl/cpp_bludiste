// Chci zkompilovat testy? (pokud ano - odkomentuji následující øádek)
//#define COMPILE_TESTS
#ifdef COMPILE_TESTS
// Chci spustit testy? (pokud ano - odkomentuji následující øádek)
#define RUN_TESTS

// Které testy chci kompilovat a spustit?
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
================================== ZADÁNÍ - SEMESTRÁLNÍ PRÁCE C++ I. ======================================

Základním poadavkem je dokonèit implementaci pomocí jazyka C++ dle standardu 14882:2017 („C++17“). 
Není pøípustné vyuívat nestandardizovaná rozšíøení jazyka (napø. C++/CLI). Pouití jakékoliv knihovny 
(mimo standard jazyka/STL) je tøeba dopøedu konzultovat, jinak nemùe bıt kód akceptován.

* Struktury, které je tøeba realizovat jsou popsány pomocí rozhraní v souboru point.h a interfaces.h. 
  Implementaci vytvoøte ve Vámi novì vytvoøenıch souborech. Doplòte do main.cpp potøebné direktivy #include.
* Pøipravené rozhraní je nutné zcela dodret. Detaily vizte pøiloené soubory. Èásteèná implementace 
  je ji navrena…
* Veškerá dynamická pamì musí bıt korektnì dealokována. Není pøípustné nechat pamì alokovanou déle 
  ne je to nutné.
* Struktury IHashSet a IDynArray není moné nahradit ekvivalentem z STL nebo jiné knihovny, ani pro jeho 
  realizaci pouít knihovny.
* Pro struktury Point, HashSet a DynArray jsou pøipraveny základní sady testù, které ovìøují základní 
  funkcionalitu.
* Není dovoleno vyuívat globální a statické promìnné. Program vypracovanı pro platformu Windows musí 
  obsahovat projektové soubory pro Visual Studio 2013 nebo novìjší, pomocí kterıch jde program pøeloit. 
  Pro unixové platformy musí bıt pøiloen makefile. Zdrojové kódy, které není moné pøeloit (chybìjící 
  projektové/zdrojové soubory, syntaktické chyby v kódu), nebudou akceptovány.

Pøed odevzdáním musí bıt projekt uklizen od veškerıch binárních souborù (spustitelnıch, tmp, cache, 
objektovıch – pomocí Build – Clean solution | make clean). Vyèištìné zdrojové kódy vèetnì souborù projektu 
odevzdávejte ve formátu ZIP.

Nejzazší termín odevzdání semestrální práce je 31. 12. 2018 23:59.

Semestrální práce musí bıt vypracována samostatnì, není pøípustná ádná shoda s jinou prací. Student musí 
bıt schopen vytvoøenou práci okomentovat a vysvìtlit pøi ústní obhajobì.

================================== ZADÁNÍ - SEMESTRÁLNÍ PRÁCE C++ I. ======================================
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