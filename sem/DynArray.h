#ifndef _DYNARRAY_H
#define _DYNARRAY_H

#include <string>
#include "interfaces.h"

template<typename T>
struct DynArray : IDynArray<T> {
public:
	DynArray();
	DynArray(int velikost);
	~DynArray();

	// P�id� prvek do kolekce (na prvn� voln� m�sto)
	virtual void add(T element) override;

	// Vr�t� prvek z kolekce
	// P��stup k neexistuj�c�mu indexu o�et�ete pomoc� v�jimky
	virtual T& get(int index) override;

	// Vrac� po�et prvk� v kolekci (ITEMCOUNT)
	virtual int count() const override;

	int getVelikost();

	//T* getPole();

private:
	// atributy:
	// - velikost pole (ASIZE)
	int velikostPole;
	// - po�et vlo�en�ch prvk� v poli (ITEMCOUNT)
	int pocetVlozenychPrvku;
	// - pole prvk� (ARRAY)
	T* pole;
	const static int ALOKACE = 10;

	void realokuj();
};

template<typename T>
inline DynArray<T>::DynArray()
{
	pole = new T[ALOKACE];
	/*for (int i = 0; i < ALOKACE; i++) {
		pole[i] = 0;
	}*/
	velikostPole = ALOKACE;
	pocetVlozenychPrvku = 0;
}

template<typename T>
inline DynArray<T>::DynArray(int velikost)
{
	pole = new T[velikost];
	velikostPole = velikost;
	pocetVlozenychPrvku = 0;
}

template<typename T>
DynArray<T>::~DynArray()
{
	/*for (int i = 0; i < velikostPole; i++) {
		delete pole[i];
	}*/
	delete[] pole;
}

template<typename T>
inline void DynArray<T>::add(T element)
{
	if (velikostPole <= pocetVlozenychPrvku) {
		realokuj();
	}
	pole[pocetVlozenychPrvku] = element;
	pocetVlozenychPrvku++;
}

template<typename T>
inline T & DynArray<T>::get(int index)
{
	if (pocetVlozenychPrvku > 0) {
		if (index < pocetVlozenychPrvku && index >= 0) {
			return pole[index];
		}
		else {
			throw std::out_of_range("Mimo rozsah pole"); //IndexMimoRozsahException();	// TODO vyjimka DONE
		}
	}
}

template<typename T>
inline int DynArray<T>::count() const
{
	return pocetVlozenychPrvku;
}

template<typename T>
inline int DynArray<T>::getVelikost()
{
	return velikostPole;
}

/*template<typename T>
inline T * DynArray<T>::getPole()
{
	return pole;
}*/

template<typename T>
inline void DynArray<T>::realokuj()
{
	velikostPole += ALOKACE;
	T* tempPole = new T[velikostPole];
	for (int i = 0; i < pocetVlozenychPrvku; i++) {
		tempPole[i] = pole[i];
	}
	delete[] pole;
	pole = tempPole;
}
#endif // !_DYNARRAY_H