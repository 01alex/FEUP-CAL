#include "Intersection.h"

Intersection::Intersection() {

}

Intersection::Intersection(int ident, float x, float y){
	this->id=ident;
	this->coord.x=x;
	this->coord.y=y;
}

int Intersection::getID() const{
	return this->id;
}

Coordenadas Intersection::getCoord() const{
	return this->coord;
}

bool Intersection::operator ==(const Intersection& p2) const {

	if(this->id == p2.getID())
		return true;
	return false;

}
