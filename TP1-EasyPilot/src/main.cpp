#include "Graph.h"
#include "Intersection.h"
#include <iostream>

using namespace std;

int main(){

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

}
