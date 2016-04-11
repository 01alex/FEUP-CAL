#include "Intersection.h"

Intersection::Intersection() {
}

Intersection::Intersection(string n, int w) {

	this->name = n;
	this->pesoOuOCrl = w;

}

string Intersection::getName() const {

	return name;

}

bool Intersection::operator ==(const Intersection& p2) const {

	if(this->name == p2.name)
		return true;
	return false;

}
