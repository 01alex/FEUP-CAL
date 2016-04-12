#include "Graph.h"
#include "Intersection.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

Graph<Intersection> map;

void readDataBase(){

	ifstream dataBase("res/Data.txt");		//**pode variar
	string line;
	string args[10];		//0-id	1-nome	2-source	3-target	4-km	5-kmh	6-x1	7-y1	8-x2	9-y2

	while(getline(dataBase,line)){

		stringstream linestream(line);
		string value;
		args->clear();
		int i=0;

		while(getline(linestream, value, ';')){
			args[i]=value;
			i++;
		}

		Intersection i1(atoi(args[2].c_str()), atof(args[6].c_str()), atof(args[7].c_str()));
		Intersection i2(atoi(args[3].c_str()), atof(args[8].c_str()), atof(args[9].c_str()));

		map.addVertex(i1);
		map.addVertex(i2);

		map.addEdge(i1, i2, args[1], atof(args[4].c_str()));

	}

	// tests
	int counter=0;
	for(unsigned i=0; i<map.getNumVertex(); i++){
		counter += map.getVertexSet()[i]->getAdj().size();
	}

	cout << "Nodes: " << map.getNumVertex() << endl;
	cout << "Edges: " << counter/2 << endl;
	//

}


int main(){

	readDataBase();

	return 0;

}
