#include "Graph.h"
#include "Intersection.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

void readDataBase(){

	Graph<Intersection> porto;

	ifstream dataBase("res/Data.txt");
	string line;
	string args[10];		//0-id	1-nome	2-source	3-target	4-km	5-kmh	6-x1	7-y1	8-x2	9-y2
	int i;


	//cout << "Ahah" << endl;

	while(getline(dataBase,line))
	{
	    stringstream linestream(line);
	    string value;
	    args->clear();
	    i=0;
	    while(getline(linestream,value,';')){
	    	args[i]=value;
	    	//cout << args[i] << endl;
	    	i++;
	    }

	    cout << args[0] << endl;

	    /*Intersection i1("qq", 99999);
	    Intersection i2("qqlink", 99999);

	    porto.addVertex(i1);
	    porto.addVertex(i2);

	    porto.addEdge(i1, i2, args[1], atoi(args[4].c_str()));*/

	    //std::cout << "Line Finished" << std::endl;

	}

	cout << porto.getVertexSet().size() << endl;

}

int main(){

	readDataBase();

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
