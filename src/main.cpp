#include "Graph.h"
#include "Intersection.h"
#include <iostream>

using namespace std;

int main(){

	Graph<Intersection> net1;
	Intersection i1("Esquina do Alexandre", 1);
	Intersection i2("Esquina do Luis", 2);

	net1.addVertex(i1);
	net1.addVertex(i2);
	net1.addEdge(i1,i2,3);

	cout << net1.getNumVertex() << endl;


}
