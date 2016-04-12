#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include <string>
using namespace std;

struct Coordenadas{
	float x, y;
};

class Intersection {
	int id;
	Coordenadas coord;
public:
	Intersection();
	Intersection (int ident, float x, float y);
	int getID() const;
	Coordenadas getCoord() const;
	bool operator == (const Intersection &p2) const;
	friend ostream & operator << (ostream &os, Intersection &p);
};



#endif /* NETWORK_H_ */
