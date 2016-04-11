#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include <string>
using namespace std;

class Intersection {
	static int ID;
	const int thisID;
	string name;
	int pesoOuOCrl;
public:
	Intersection();
	Intersection (string n, int w);
	int getID() const;
	string getName() const;
	bool operator == (const Intersection &p2) const;
	friend ostream & operator << (ostream &os, Intersection &p);
};



#endif /* NETWORK_H_ */
