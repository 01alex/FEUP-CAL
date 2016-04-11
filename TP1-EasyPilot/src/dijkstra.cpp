#include <iostream>

#include <string>
#include <climits>
#include "Graph.h"

#define INF INT_MAX //Infinity
using namespace std;

template <class T>
vector<int> algorithmTest(Graph<T> x, int src){

	Graph<T> test;
	vector <int> result;


	vector<Vertex<T> *> vertexSet = x.getVertexSet();

	vertexSet[src].setNewWeight(0); //sera o nó source, os outros devem estar em inf


	for(unsigned int i = 0; i < vertexSet.size(); i++){

		if(i == src)
			continue;

		vertexSet[i].setNewWeight(INF);

	}

	bool destination = false;

	// if !visited, src = novo vertex ?? ate chegar a destino?


	//percorre adj a um vertex e calcula novos weights
	for(unsigned int i = 0; i < vertexSet[src].getAdj().size(); i++){

		int min_val = INF;
		int min_val_pos = INF;

		//peso da src + rua < peso desse adj
		if(vertexSet[src].getWeight() +  vertexSet[src].getAdj()[i].getDistance() <  vertexSet[src].getAdj()[i].getWeight()  ){

			if(vertexSet[src].getWeight() +  vertexSet[src].getAdj()[i].getDistance() < min_val){
				min_val = vertexSet[src].getWeight() +  vertexSet[src].getAdj()[i].getDistance();
				min_val_pos = i;
			}

			vertexSet[src].getAdj()[i].setNewWeight(vertexSet[src].getWeight() +  vertexSet[src].getAdj()[i].getDistance() );

		}

	}





	return result;


}
