#ifndef __INTERFACES_H
#define __INTERFACES_H
#include <string>

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


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "point.h"

// Typy prvkù v bludišti
enum struct MazeTile {
	// Zeï
	Wall = '#',
	// Volné pole
	Empty = '.'
};

///////////////////////////////////////////////////////////////////////////////

// Šablona funkce na výpoèet hashe z datového prvku
template<typename T>
using HashFunction = int(*) (const T&);

// Uvedený kód definuje nový datový typ HashFunction<T> reprezentující (ukazatel na) generickou funkci.

///////////////////////////////////////////////////////////////////////////////

// Šablona funkce na test shody dvou datových prvkù
template<typename T>
using EqualFunction = bool(*) (const T&, const T&);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Množina realizovaná pomocí hashovací tabulky
// !!! Realizujte bez využití kontejnerù STL !!!
// Vyžadovaná prùmìrná složitost operací: add - O(1), isPresent - O(1)
// Oèekávána realizace: hashování s zøetìzením
template<typename T, HashFunction<T> HF, EqualFunction<T> EF>
struct IHashSet {

	// Parametrický konstruktor - umožòuje nastavit velikost vnitøního pole 
	// IHashSet(int internalArraySize)

	// Destruktor - uvolòuje všechny prvky ze všech spojových seznamù a alokované pole
	virtual ~IHashSet() { }

	// Pøidá element do množiny (pokud v ní již není)
	// - vypoèítejte pozici prvku pomocí funkce HF (i = HF(element) % ASIZE)
	// - vložte prvek na zaèátek spojového seznamu (vytvoøte HASHNODE{element, AHASH[i]} a nastavte ukazatel na adrese AHASH[i] na vytvoøený prvek)
	// -- element je vkládán na zaèátek seznamu - konstatní složitost operace
	// - pseudokód:
	// --- calculate index i
	// --- test if element is not present in hashset
	// --- new_node = allocate HASHNODE structure
	// --- new_node->element = element
	// --- new_node->next = AHASH[i] 
	// --- AHASH[i] = new_node 
	virtual void add(T element) = 0;

	// Otestuje, jestli je element v množinì
	// - vypoèítejte pozici prvku pomocí funkce HF (viz metoda add())
	// - projdìte spojový seznam na daném indexu v poli a zjistìtì, jestli zde existuje stejný prvek pomocí funkce EF
	// -- pseudokód: 
	// ---- foreach (hashnode in AHASH[index]) 
	// ------ if EF(element, hashnode.data) 
	// -------- return true
	// ---- end foreach
	// ---- return false
	virtual bool isPresent(T element) const = 0;

	// atributy:
	// - velikost pole (ASIZE)
	// - dynamicky alokované pole ukazatelù na spojové seznamy prvkù hash tabulky (AHASH)
	// -- na pozici [i] se nachází všechny prvky pro které platí: HF(element) % ASIZE == i 
	// -- na pozici [i] mùže být nullptr, jeden prvek (resp. jednoprvkový spojový seznam) nebo spojový seznam obsahující více prvkù

	// vnoøené typy:
	// - prvek hash tabulky (realizující spojový seznam) (HASHNODE)
	// -- obsahuje: T element a ukazatel na další HASHNODE ve spojovém seznamu
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Bludištì - pøedstavuje naètené a parsované bludištì ze souboru
struct IMaze {

	virtual ~IMaze() { }

	// Naète bludištì ze souboru
	// static IMaze* fromFile(string filename)
	// Bludištì je uloženo v jednoduchém textovém (ASCII) souboru
	// Na zaèátku je uloženo 6 èísel - rozmìry bludištì a poloha vstupu a výstupu
	// x_vstupu a x_vystupu je hodnota v rozsahu 0 -- (pocet_sloupcu - 1)
	// y_vstupu a y_vystupu je hodnota v rozsahu 0 -- (pocet_radku - 1)
	//
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

	// Vrací true, pokud jsou souøadnice platné
	virtual bool isValidPoint(Point pt) const = 0;

	// Vrací znak podle souøadnic (neplatné souøadnice vyvolají výjimku)
	virtual char getPoint(Point pt) const = 0;

	// Vrací poèet øádkù bludištì
	virtual int getR() const = 0;

	// Vrací poèet sloupcù bludištì
	virtual int getC() const = 0;

	// Vrací polohu poèátku bludištì
	virtual Point getStart() const = 0;

	// Vrací polohu konce bludištì
	virtual Point getEnd() const = 0;

	// atributy:
	// - pro uložení stavu bludištì

};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Kolekce prvkù T, realizovaná jako dynamicky alokované pole.
// Na poèátku alokujte pole na velikost 10 prvkù. Pokud pøi pøidávání je pole naplnìno,
// automaticky jej realokujte a zvìtšete o dalších 10 prvkù.
template<typename T>
struct IDynArray {

	virtual ~IDynArray() {}

	// Pøidá prvek do kolekce (na první volné místo)
	virtual void add(T element) = 0;

	// Vrátí prvek z kolekce
	// Pøístup k neexistujícímu indexu ošetøete pomocí výjimky
	virtual T& get(int index) = 0;

	// Vrací poèet prvkù v kolekci (ITEMCOUNT)
	virtual int count() const = 0;

	// atributy:
	// - velikost pole (ASIZE)
	// - poèet vložených prvkù v poli (ITEMCOUNT)
	// - pole prvkù (ARRAY)
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Øešitel bludištì využívající techniky backtrackingu
struct IMazeSolver {

	virtual ~IMazeSolver() { }

	// Vyøeš bludištì
	// - vrací true pokud má bludištì øešení, false pokud bludištì není øešitelné
	// - prohledávání zaèíná v bodì maze::getStart, prohledávání je ukonèeno, pokud není možné
	//   dále pokraèovat nebo bylo dosaženo cíle (maze::getEnd)
	// - v bludišti je možné se pohybovat 4 smìry: NAHORU (y-1), DOLÙ (y+1), DOLEVA (x-1) nebo DOPRAVA (x+1)
	// - v prùbìhu hledání cíle nemá smysl vstupovat na pole, která již byla navštívena
	//
	// - doporuèená strategie pro prohledávání je prohledávání do hloubky, cyklus:
	// -- zaznamenám aktuální polohu hledaèe do spojového seznamu (zároveò je bod zaznamenán do tabulky IHashSet)
	// -- vyberu jeden dostupný smìr a udìlám krok
	// -- pokud jsem na konci chodby a není možné dále pokraèovat - provedu odrolování
	// 
	// - odrolování - je použito, pokud není možné pokraèovat v další cestì
	// -- pro odrolování je použit v pøedchozím kroku vytváøený spojový seznam
	// -- cyklus: postupnì jsou odebírány jednotlivé prvky (od konce) ze spojového seznamu
	// ---- každý prvek seznamu obsahuje zaznamenanou polohu bodu
	// ---- pro každý prvek je otestováno, jestli existuje z daného bodu dostupná (dosud nenavštívená) cesta
	// ------ pokud je cesta pøítomna, je odrolování ukonèeno a algoritmus pokraèuje nalezenou cestou
	// ------ pokud není cesta dostupná, prvek je odebrán ze spojového seznamu
	// ---- pokud je spojový seznam vyprázdnìn a není nalezena další cesta -> bludištì nemá øešení
	virtual bool solve() = 0;

	// Uloží bludištì a jeho øešení do textového souboru
	virtual void saveMazeAndSolution(std::string filename) const = 0;

	// Funkce vrací pole všech dostupných krokù z daného výchozího místa
	// - krokem se rozumí pohyb NAHORU, DOLÙ, DOLEVA nebo DOPRAVA
	// - dané místo nesmí pøedstavovat zeï v bludišti a nesmí být mimo rozsah bludištì
	// - funkce neøeší, jestli místo bylo navštíveno nebo ne. 
	virtual IDynArray<Point>* getPossibleMoves(Point pt) const = 0;
	
	// Funkce vymaže ze zadaného pole veškeré body, které již byly v rámci øešení bludištì navštíveny (využívá IHashSet)
	// - metoda vrací novì vytvoøený objekt IDynArray, pùvodní objekt je smazán
	virtual IDynArray<Point>* dropMovesInAllPaths(IDynArray<Point>* moves) const = 0;

	// Vrací true, pokud je daný bod v aktuální cestì
	// -- využívá spojový seznam sloužící pro proces odrolování
	virtual bool isInCurrentHistory(Point pt) const = 0;
	
	// Vrací true, pokud byl daný bod navštíven
	// -- využívá hashovací tabulku založenou na IHashSet
	virtual bool isInAllHistory(Point pt) const = 0;
	
	// Uloží aktuální polohu jako dosažený stav do spojového seznamu
	// - spojový seznam mùže být pouze jednosmìrný
	// - každý prvek ukazuje na svého "pøedchùdce"
	// - IMazeSolver si musí pamatovat vrchol spojového seznamu (prvek, který ukazuje na všechny platné pøedchùdce)
	virtual void saveState(Point pt) = 0;

	// Vrací øešené bludištì
	virtual IMaze* getMaze() const = 0;

	/////////////////////////////////////////////////

	// Zobrazí stav do konzole
	void show();

private:
	char* createVisualisation();
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#endif