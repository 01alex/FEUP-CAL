#include "Intersection.h"

int Intersection::ID = 0;

Intersection::Intersection(): thisID(ID++) {

}

Intersection::Intersection(string n, int w): thisID(ID++) {
	this->name = n;
	this->pesoOuOCrl = w;
}

int Intersection::getID() const{
	return this->thisID;
}

string Intersection::getName() const {
	return this->name;
}

bool Intersection::operator ==(const Intersection& p2) const {

	if(this->thisID == p2.getID())
		return true;
	return false;

}
