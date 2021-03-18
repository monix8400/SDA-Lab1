#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

//Komplexitat: 
//best case: Θ(1)
//worst case: Θ(1)
//avg case: Θ(1)

BagIterator::BagIterator(const Bag& c): bag(c)
{//TODO - Representation
	i = 0;
}

//Komplexitat: 
//best case: Θ(1)
//worst case: Θ(1)
//avg case: Θ(1)

void BagIterator::first() {
	//TODO - Representation
	i = 0;							//gibt das erste Element zuruck
}

//Komplexitat: 
//best case: Θ(1)
//worst case: Θ(1)
//avg case: Θ(1)

void BagIterator::next() {
	//TODO - Representation
	if (i < bag.lengthP) {		//gibt das nachste Elem., aber nur wenn man nicht am Ende ist
		i += 1;
	}
	else {
		exception e;	
		throw e;
	}
}

//Komplexitat: 
//best case: Θ(1)
//worst case: Θ(1)
//avg case: Θ(1)

bool BagIterator::valid() const {
	//TODO - Representation
	if (i < bag.lengthP) {		//bestimmt ob man noch im Array ist
		return true;
	}
	return false;
}

//Komplexitat: 
//best case: Θ(1)
//worst case: Θ(1)
//avg case: Θ(1)

TElem BagIterator::getCurrent() const
{//TODO - Representation
	if (valid() == true) {				//gibt das Elem. zuruck, wenn man noch im Array ist
		return bag.U[bag.P[i]];
	}
	else {
		exception e;
		throw e;
	}
	return NULL_TELEM 
}
