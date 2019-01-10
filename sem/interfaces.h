#ifndef __INTERFACES_H
#define __INTERFACES_H
#include <string>

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


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "point.h"

// Typy prvk� v bludi�ti
enum struct MazeTile {
	// Ze�
	Wall = '#',
	// Voln� pole
	Empty = '.'
};

///////////////////////////////////////////////////////////////////////////////

// �ablona funkce na v�po�et hashe z datov�ho prvku
template<typename T>
using HashFunction = int(*) (const T&);

// Uveden� k�d definuje nov� datov� typ HashFunction<T> reprezentuj�c� (ukazatel na) generickou funkci.

///////////////////////////////////////////////////////////////////////////////

// �ablona funkce na test shody dvou datov�ch prvk�
template<typename T>
using EqualFunction = bool(*) (const T&, const T&);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Mno�ina realizovan� pomoc� hashovac� tabulky
// !!! Realizujte bez vyu�it� kontejner� STL !!!
// Vy�adovan� pr�m�rn� slo�itost operac�: add - O(1), isPresent - O(1)
// O�ek�v�na realizace: hashov�n� s z�et�zen�m
template<typename T, HashFunction<T> HF, EqualFunction<T> EF>
struct IHashSet {

	// Parametrick� konstruktor - umo��uje nastavit velikost vnit�n�ho pole 
	// IHashSet(int internalArraySize)

	// Destruktor - uvol�uje v�echny prvky ze v�ech spojov�ch seznam� a alokovan� pole
	virtual ~IHashSet() { }

	// P�id� element do mno�iny (pokud v n� ji� nen�)
	// - vypo��tejte pozici prvku pomoc� funkce HF (i = HF(element) % ASIZE)
	// - vlo�te prvek na za��tek spojov�ho seznamu (vytvo�te HASHNODE{element, AHASH[i]} a nastavte ukazatel na adrese AHASH[i] na vytvo�en� prvek)
	// -- element je vkl�d�n na za��tek seznamu - konstatn� slo�itost operace
	// - pseudok�d:
	// --- calculate index i
	// --- test if element is not present in hashset
	// --- new_node = allocate HASHNODE structure
	// --- new_node->element = element
	// --- new_node->next = AHASH[i] 
	// --- AHASH[i] = new_node 
	virtual void add(T element) = 0;

	// Otestuje, jestli je element v mno�in�
	// - vypo��tejte pozici prvku pomoc� funkce HF (viz metoda add())
	// - projd�te spojov� seznam na dan�m indexu v poli a zjist�t�, jestli zde existuje stejn� prvek pomoc� funkce EF
	// -- pseudok�d: 
	// ---- foreach (hashnode in AHASH[index]) 
	// ------ if EF(element, hashnode.data) 
	// -------- return true
	// ---- end foreach
	// ---- return false
	virtual bool isPresent(T element) const = 0;

	// atributy:
	// - velikost pole (ASIZE)
	// - dynamicky alokovan� pole ukazatel� na spojov� seznamy prvk� hash tabulky (AHASH)
	// -- na pozici [i] se nach�z� v�echny prvky pro kter� plat�: HF(element) % ASIZE == i 
	// -- na pozici [i] m��e b�t nullptr, jeden prvek (resp. jednoprvkov� spojov� seznam) nebo spojov� seznam obsahuj�c� v�ce prvk�

	// vno�en� typy:
	// - prvek hash tabulky (realizuj�c� spojov� seznam) (HASHNODE)
	// -- obsahuje: T element a ukazatel na dal�� HASHNODE ve spojov�m seznamu
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Bludi�t� - p�edstavuje na�ten� a parsovan� bludi�t� ze souboru
struct IMaze {

	virtual ~IMaze() { }

	// Na�te bludi�t� ze souboru
	// static IMaze* fromFile(string filename)
	// Bludi�t� je ulo�eno v jednoduch�m textov�m (ASCII) souboru
	// Na za��tku je ulo�eno 6 ��sel - rozm�ry bludi�t� a poloha vstupu a v�stupu
	// x_vstupu a x_vystupu je hodnota v rozsahu 0 -- (pocet_sloupcu - 1)
	// y_vstupu a y_vystupu je hodnota v rozsahu 0 -- (pocet_radku - 1)
	//
	// Form�t souboru:
	// 7 7        <-- po�et ��dk� a sloupc� v bludi�ti
	// 2 0        <-- ��slo ��dku a sloupce vstupu do bludi�t�
	// 3 6        <-- ��slo ��dku a sloupce v�stupu z bludi�t�
	// #######
	// ##.##.#
	// ....#.#
	// ###.#..    <-- bludi�t� ulo�en� jako jednotliv� znaky
	// #...#.#        ka�d� ��dek je ukon�en znaky od��dkov�n�
	// #.#...#
	// #######

	// Vrac� true, pokud jsou sou�adnice platn�
	virtual bool isValidPoint(Point pt) const = 0;

	// Vrac� znak podle sou�adnic (neplatn� sou�adnice vyvolaj� v�jimku)
	virtual char getPoint(Point pt) const = 0;

	// Vrac� po�et ��dk� bludi�t�
	virtual int getR() const = 0;

	// Vrac� po�et sloupc� bludi�t�
	virtual int getC() const = 0;

	// Vrac� polohu po��tku bludi�t�
	virtual Point getStart() const = 0;

	// Vrac� polohu konce bludi�t�
	virtual Point getEnd() const = 0;

	// atributy:
	// - pro ulo�en� stavu bludi�t�

};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Kolekce prvk� T, realizovan� jako dynamicky alokovan� pole.
// Na po��tku alokujte pole na velikost 10 prvk�. Pokud p�i p�id�v�n� je pole napln�no,
// automaticky jej realokujte a zv�t�ete o dal��ch 10 prvk�.
template<typename T>
struct IDynArray {

	virtual ~IDynArray() {}

	// P�id� prvek do kolekce (na prvn� voln� m�sto)
	virtual void add(T element) = 0;

	// Vr�t� prvek z kolekce
	// P��stup k neexistuj�c�mu indexu o�et�ete pomoc� v�jimky
	virtual T& get(int index) = 0;

	// Vrac� po�et prvk� v kolekci (ITEMCOUNT)
	virtual int count() const = 0;

	// atributy:
	// - velikost pole (ASIZE)
	// - po�et vlo�en�ch prvk� v poli (ITEMCOUNT)
	// - pole prvk� (ARRAY)
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// �e�itel bludi�t� vyu��vaj�c� techniky backtrackingu
struct IMazeSolver {

	virtual ~IMazeSolver() { }

	// Vy�e� bludi�t�
	// - vrac� true pokud m� bludi�t� �e�en�, false pokud bludi�t� nen� �e�iteln�
	// - prohled�v�n� za��n� v bod� maze::getStart, prohled�v�n� je ukon�eno, pokud nen� mo�n�
	//   d�le pokra�ovat nebo bylo dosa�eno c�le (maze::getEnd)
	// - v bludi�ti je mo�n� se pohybovat 4 sm�ry: NAHORU (y-1), DOL� (y+1), DOLEVA (x-1) nebo DOPRAVA (x+1)
	// - v pr�b�hu hled�n� c�le nem� smysl vstupovat na pole, kter� ji� byla nav�t�vena
	//
	// - doporu�en� strategie pro prohled�v�n� je prohled�v�n� do hloubky, cyklus:
	// -- zaznamen�m aktu�ln� polohu hleda�e do spojov�ho seznamu (z�rove� je bod zaznamen�n do tabulky IHashSet)
	// -- vyberu jeden dostupn� sm�r a ud�l�m krok
	// -- pokud jsem na konci chodby a nen� mo�n� d�le pokra�ovat - provedu odrolov�n�
	// 
	// - odrolov�n� - je pou�ito, pokud nen� mo�n� pokra�ovat v dal�� cest�
	// -- pro odrolov�n� je pou�it v p�edchoz�m kroku vytv��en� spojov� seznam
	// -- cyklus: postupn� jsou odeb�r�ny jednotliv� prvky (od konce) ze spojov�ho seznamu
	// ---- ka�d� prvek seznamu obsahuje zaznamenanou polohu bodu
	// ---- pro ka�d� prvek je otestov�no, jestli existuje z dan�ho bodu dostupn� (dosud nenav�t�ven�) cesta
	// ------ pokud je cesta p��tomna, je odrolov�n� ukon�eno a algoritmus pokra�uje nalezenou cestou
	// ------ pokud nen� cesta dostupn�, prvek je odebr�n ze spojov�ho seznamu
	// ---- pokud je spojov� seznam vypr�zdn�n a nen� nalezena dal�� cesta -> bludi�t� nem� �e�en�
	virtual bool solve() = 0;

	// Ulo�� bludi�t� a jeho �e�en� do textov�ho souboru
	virtual void saveMazeAndSolution(std::string filename) const = 0;

	// Funkce vrac� pole v�ech dostupn�ch krok� z dan�ho v�choz�ho m�sta
	// - krokem se rozum� pohyb NAHORU, DOL�, DOLEVA nebo DOPRAVA
	// - dan� m�sto nesm� p�edstavovat ze� v bludi�ti a nesm� b�t mimo rozsah bludi�t�
	// - funkce ne�e��, jestli m�sto bylo nav�t�veno nebo ne. 
	virtual IDynArray<Point>* getPossibleMoves(Point pt) const = 0;
	
	// Funkce vyma�e ze zadan�ho pole ve�ker� body, kter� ji� byly v r�mci �e�en� bludi�t� nav�t�veny (vyu��v� IHashSet)
	// - metoda vrac� nov� vytvo�en� objekt IDynArray, p�vodn� objekt je smaz�n
	virtual IDynArray<Point>* dropMovesInAllPaths(IDynArray<Point>* moves) const = 0;

	// Vrac� true, pokud je dan� bod v aktu�ln� cest�
	// -- vyu��v� spojov� seznam slou��c� pro proces odrolov�n�
	virtual bool isInCurrentHistory(Point pt) const = 0;
	
	// Vrac� true, pokud byl dan� bod nav�t�ven
	// -- vyu��v� hashovac� tabulku zalo�enou na IHashSet
	virtual bool isInAllHistory(Point pt) const = 0;
	
	// Ulo�� aktu�ln� polohu jako dosa�en� stav do spojov�ho seznamu
	// - spojov� seznam m��e b�t pouze jednosm�rn�
	// - ka�d� prvek ukazuje na sv�ho "p�edch�dce"
	// - IMazeSolver si mus� pamatovat vrchol spojov�ho seznamu (prvek, kter� ukazuje na v�echny platn� p�edch�dce)
	virtual void saveState(Point pt) = 0;

	// Vrac� �e�en� bludi�t�
	virtual IMaze* getMaze() const = 0;

	/////////////////////////////////////////////////

	// Zobraz� stav do konzole
	void show();

private:
	char* createVisualisation();
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif