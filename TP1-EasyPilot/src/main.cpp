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

		Intersection source(atoi(args[2].c_str()), atof(args[6].c_str()), atof(args[7].c_str()));
		Intersection target(atoi(args[3].c_str()), atof(args[8].c_str()), atof(args[9].c_str()));

		map.addVertex(source);
		map.addVertex(target);

		map.addEdge(source, target, args[1], atof(args[4].c_str()));

	}

	// tests
	int counteradj=0, counterindeg=0;
	for(unsigned i=0; i<map.getNumVertex(); i++){
		counteradj += map.getVertexSet()[i]->getAdj().size();
		counterindeg += map.getVertexSet()[i]->getIndegree();
		//cout << "Adj: " << map.getVertexSet()[i]->getAdj().size() << endl;			//com origem no no
		//cout << "Indegree: " << map.getVertexSet()[i]->getIndegree() << endl;		//apontam para o no
	}

	cout << "Nodes: " << map.getNumVertex() << endl;
	cout << "Edges: " << counteradj << endl;
	cout << "Indegrees: " << counterindeg << endl;
	//

}


int main(){

	//readDataBase();

	Intersection source(0, -2, 2);
	Intersection target(1, 3, 5);
	Intersection target2(2, 6, 8);

	map.addVertex(source);
	map.addVertex(target);
	map.addVertex(target2);

	map.addEdge(source, target, "belga", 35);
	map.addEdge(target, target2, "polsky", 15);

	map.Dijkstra(source);

	return 0;

}
