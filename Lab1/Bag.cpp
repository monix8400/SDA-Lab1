#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

//Komplexitat: 
//best case: Θ(1)
//worst case: Θ(1)
//avg case: Θ(1)

Bag::Bag() {
	//TODO - Implementation
	capacityU = 100;  
	capacityP = 200;
	lengthP = 0;
	lengthU = 0;
	P = new TElem[capacityP];	//man allokiert Speicherplatz fir P und U
	U = new TElem[capacityU];
	//constructor
}

//Komplexitat: 
//best case: Θ(1)
//worst case: O(n)
//avg case: O(n)

void Bag::add(TElem elem) {
	//TODO - Implementation
	if (lengthU == capacityU)				//wenn Lange=Kapazitat, dann wird die Kapazitat verdoppelt, also es wird einen neunen Speicherplatz allokiert fur U
	{
		if (capacityU != 0) capacityU *= 2;	
		else capacityU = capacityU + 1;
		TElem* U2 = new TElem[capacityU];
		for (int i = 0; i < lengthU; ++i)
			{
			U2[i] = U[i];
			}
		delete U;
		U = U2;
	}
	if (lengthP == capacityP)	//wenn Lange=Kapazitat, dann wird die Kapazitat verdoppelt, also es wird einen neunen Speicherplatz allokiert fur P
	{
		if (capacityP != 0) capacityP *= 2;
		else capacityP = capacityP + 1;
		capacityP *= 2;
		TElem* P2 = new TElem[capacityP];
		for (int i = 0; i < lengthP; ++i)
		{
			P2[i] = P[i];
		}
		delete P;
		P = P2;
	}

	if (search(elem) == false) {	//wenn Elem nicht schon in U ist, werden sowohl P als auch U vergrossert
		U[lengthU] = elem;
		P[lengthP] = lengthU++;;
		lengthP++;
	}
	else {
		for (int i = 0; i < lengthU;++i) {	//sonst wird nur P vergrossert
			if (U[i] == elem) {
				P[lengthP] = i;
				lengthP++;
			}
		}
	}
}

/*
bool Bag::remove(TElem elem) {
	//TODO - Implementation
	if (isEmpty() == true) return false; //untersucht ob der array leer ist
	if (search(elem) == true) {			//sucht ob der Elem im Array ist
		if (U[P[lengthP-1]] == elem) {		//wenn der Elem gefundet ist
			if (nrOccurrences(U[P[lengthP-1]]) == 1)	//und er nur ein Mal vorkommt verkleinert man beide Arrays,sonst nur P
				lengthU = lengthU - 1;
			lengthP = lengthP - 1;
		}									//wenn der Elem mehrere male vorkommt wird die erste Erscheinung geloscht
		int i = 0;
		bool first = false;
		while ((i < lengthP - 1) && !first){	
			if (U[P[i]] == elem) {
				first = true;
				if (nrOccurrences(U[P[i]]) == 1) {	//wenn Elem nur ein Mal vorkommt verkleinert man beide Arrays
					for (int j = i; j < lengthU - 1; j++)
						U[j] = U[j + 1];
					lengthU--;

					for (int k = i; k < lengthP - 1; k++)
						P[k] = P[k + 1];
					lengthP--;

					for (int pos = 0; pos < lengthP; pos++)
						if (P[pos] >= index)
							P[pos] = P[pos] - 1;
				}
				else {								//sonst nur P
					for (int k = i; k < lengthP - 1; k++)
						P[k] = P[k + 1];
					lengthP--;
				}
			}
			i = i + 1;
		}
		return true;
	}
	return false;		//wenn Elem nicht gefunden wird, bleibt die Funk false
}
*/


//Komplexitat: 
//best case: Θ(n)
//worst case: Θ(n)
//avg case: Θ(n)

bool Bag::remove(TElem elem) {
	int iElem=-1 ;
	for (int i = 0; i < lengthU; i++)		//wenn Elem gefunden wird, wird man die Pozition gespeicher
		if (U[i] == elem)  iElem= i;
	if (iElem != -1) {					//man untersucht ob der Elem existiert
		int anz = 0, last = -1;
		for (int i = 0; i <= lengthP; i++) {
			if (P[i] == iElem) {
				anz++;					//man bestimmt die Anzahl von elem in P
				last = i;				//last speichert die letzte Vorscheinung von elem
			}
		}
		if (last != -1) {
			if (anz == 1) {				//wenn Anzahl=1(koom nu ein Mal vor)
				for (int i = iElem; i < lengthU; i++)	//loscht man es aus U
					U[i] = U[i + 1];	
				lengthU--;
				if (iElem == lengthU)		//und untersucht man ob es der lezte Elem aus P ist
					for (int i = last; i < lengthP; i++) {	//in diesem Fall loscht man es auch aus P
						P[i] = P[i + 1];		
					}
				else
				{
					for (int i = last; i < lengthP; i++) {	//sonst loscht man es aus P
						P[i] = P[i + 1];
					}
					for (int i = 0; i < lengthP; i++) {		//und weil die Positionen sich verandert haben nach der Loschung,
						if (P[i] >= iElem)					//muss man sie wiederherstellen
							P[i]--;							
					}
				}
				lengthP--;
				return true;
			}
			else {					//wenn Elem mehrmals vorkommt wird es nur aus P geloscht
				for (int i = last; i < lengthP; i++)
					P[i] = P[i + 1];
				lengthP--;
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	return false;
}

//Komplexitat: 
//best case: O(n)
//worst case: O(n)
//avg case: O(n)

bool Bag::search(TElem elem) const {
	//TODO - Implementation
	for (int i = 0; i < lengthU; ++i) {		//sucht elem
		if (U[i] == elem) return true;
	}
	return false; 
}

//Komplexitat: 
//best case: O(n)
//worst case: Θ(n)
//avg case: Θ(n)

int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
	if (search(elem) == true) {					//wenn elem existiert,
		int nr = 0;								//wird die Anzahl der Vorscheinungen gemacht
		for (int i = 0; i < lengthP; ++i) { 
			if (U[P[i]] == elem) nr = nr + 1;
		}
		if (nr != 0)return nr;
	}
	return 0; 
}

//Komplexitat: 
//best case: Θ(1)
//worst case: Θ(1)
//avg case: Θ(1)

int Bag::size() const {
	//TODO - Implementation
	if (lengthP > 0) return lengthP;		//wenn die Lange grosser als 0 ist wird sie returniert, sonst nicht
	return 0;
}

//Komplexitat: 
//best case: Θ(1)
//worst case: Θ(1)
//avg case: Θ(1)

bool Bag::isEmpty() const {
	//TODO - Implementation
	if (lengthP == 0) return true;			//bestimmt ob der Array leer ist oder nicht
	return false;
}

//Komplexitat: 
//best case: Θ(1)
//worst case: Θ(1)
//avg case: Θ(1)

BagIterator Bag::iterator() const {
	//TODO - Implementation
	return BagIterator(*this);
}

//Komplexitat: 
//best case: Θ(1)
//worst case: Θ(1)
//avg case: Θ(1)

Bag::~Bag() {
	//TODO - Implementation
	delete[] U;					//dealokiert der Speicherplatz fur U und P
	delete[] P;
	//destructor
}
