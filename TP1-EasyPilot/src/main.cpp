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

Graph<Intersection> porto;


template <class T>
void readDataBase(Graph<T> &map){

	//Graph<Intersection> porto;

	ifstream dataBase("res/Data.txt"); //ou "/res/Data.txt"
	string line;
	string args[10];		//0-id	1-nome	2-source	3-target	4-km	5-kmh	6-x1	7-y1	8-x2	9-y2
	std::string::size_type sz;


	while(getline(dataBase,line)){

		stringstream linestream(line);
	    string value;
	    args->clear();
	    int i=0;

	    while(getline(linestream, value, ';')){
	    	args[i]=value;
	    	//cout << args[i] << endl;
	    	i++;
	    }


	    //cout << args[0] << endl;

	    Intersection i1(atoi(args[2].c_str()), atof(args[6].c_str()), atof(args[7].c_str()));
	    Intersection i2(atoi(args[3].c_str()), atof(args[8].c_str()), atof(args[9].c_str()));

	    map.addVertex(i1);
	    map.addVertex(i2);

	    map.addEdge(i1, i2, args[1], atof(args[4].c_str()));


	    //cout << map.getVertexSet()[i]->getIntersection().getID() << endl;


	    //std::cout << "Line Finished" << std::endl;

	}

	cout << map.getNumVertex() << endl;

	//cout << porto.getVertexSet().size() << endl;

}


int main(){

	readDataBase(porto);

	/*

	Graph<Intersection> net1;
	Intersection i1("Esquina do Alexandre", 1);
	Intersection i2("Esquina do Luis", 2);
	Intersection i3("Estadio da Luz", 35);

	net1.addVertex(i1);
	net1.addVertex(i2);
	net1.addVertex(i3);

	cout << "No Vertex: " << net1.getNumVertex() << endl;


	if(net1.addEdge(i1, i2,"rua x", 10))
		cout << "can add edge between " << i1.getName() << " and " << i2.getName() << endl;
	else cout << "can't add edge between " << i1.getName() << " and " << i2.getName() << endl;

	if(net1.addEdge(i1, i3, "Esquina do 35", 35))
		cout << "can add edge between " << i1.getName() << " and " << i3.getName() << endl;
	else cout << "can't add edge between " << i1.getName() << " and " << i3.getName() << endl;

	cout << net1.getVertexSet()[0]->findEdge(*net1.getVertexSet()[1]) << endl;			//primeiro vertice do grafo tem aresta para o segundo vertice do grafo, em adj[0]
	cout << net1.getVertexSet()[1]->findEdge(*net1.getVertexSet()[0]) << endl;			//segundo vertice do grafo tem aresta para o primeiro vertice do grafo, em adj[0]

	cout << net1.getVertexSet()[0]->findEdge(*net1.getVertexSet()[2]) << endl;			//primeiro vertice do grafo tem aresta para o terceiro vertice do grafo, em adj[1]
	cout << net1.getVertexSet()[1]->findEdge(*net1.getVertexSet()[2]) << endl;			//segundo vertice do grafo nao tem aresta para o terceiro vertice do grafo, -1

	 */

	return 0;

}
