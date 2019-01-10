#ifndef _HASHSET_H
#define _HASHSET_H

#include "interfaces.h"

template<typename T, HashFunction<T> HF, EqualFunction<T> EF>
struct HashSet : IHashSet<T, HF, EF> {
private:
	struct PrvekHashListu {
	private:
		T data;
		PrvekHashListu *dalsiPrvek;
	public:
		PrvekHashListu(T data, PrvekHashListu *dalsiPrvek);
		~PrvekHashListu() {};
		PrvekHashListu* getDalsiPrvek() { return this->dalsiPrvek; }
		T getData() { return this->data; }
	};
	int velikostPole;
	PrvekHashListu** hashPole;
public:
	HashSet(int velikost);
	~HashSet();

	virtual void add(T element) override;
	virtual bool isPresent(T element) const override;
};

#endif // !_HASHSET_H

template<typename T, HashFunction<T> HF, EqualFunction<T> EF>
inline HashSet<T, HF, EF>::PrvekHashListu::PrvekHashListu(T data, PrvekHashListu * dalsiPrvek)
{
	this->data = data;
	this->dalsiPrvek = dalsiPrvek;
}

template<typename T, HashFunction<T> HF, EqualFunction<T> EF>
inline HashSet<T, HF, EF>::HashSet(int velikost)
{
	this->velikostPole = velikost;
	this->hashPole = new PrvekHashListu*[velikostPole];
	for (int i = 0; i < velikostPole; i++) {
		hashPole[i] = nullptr;
	}
}

template<typename T, HashFunction<T> HF, EqualFunction<T> EF>
inline HashSet<T, HF, EF>::~HashSet()
{
	for (int i = 0; i < velikostPole; i++) {
		//delete hashPole[i];		// pres destruktor Prvku dela neplechu, nejde, strcit sem
		PrvekHashListu* prvekMazani = hashPole[i];
		while (prvekMazani != nullptr) {
			PrvekHashListu* tempPrvek = prvekMazani->getDalsiPrvek();
			delete prvekMazani;
			prvekMazani = tempPrvek;
		}
	}
	delete[] hashPole;
}

template<typename T, HashFunction<T> HF, EqualFunction<T> EF>
inline void HashSet<T, HF, EF>::add(T element)
{
	int index = HF(element) % velikostPole;
	if (!isPresent(element)) {
		PrvekHashListu* tempPrvek = new PrvekHashListu(element, hashPole[index]);
		hashPole[index] = tempPrvek;
	}
}

template<typename T, HashFunction<T> HF, EqualFunction<T> EF>
inline bool HashSet<T, HF, EF>::isPresent(T element) const
{
	int index = HF(element) % velikostPole;
	PrvekHashListu* tempPrvek = hashPole[index];
	while (tempPrvek != nullptr) {
		if (EF(tempPrvek->getData(), element)) {
			return true;
		}
		tempPrvek = tempPrvek->getDalsiPrvek();
	}
	return false;
}
