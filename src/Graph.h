/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <string>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;

template <class T>
class Vertex { //cruzamentos
	T info;
	vector<Edge<T>  > adj;
	bool visited;
public:
	Vertex(T in);
	bool addEdge(Edge<T> &edge);
	int findEdge(Vertex<T> v);
	friend class Graph<T>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false){}


template <class T>
class Edge { // ruas
	Vertex<T> * dest;
	string streetName;
public:
	Edge(Vertex<T> *d, string sName);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, string sName): dest(d), streetName(sName){}

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
public:
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest,string streetName);
	bool removeVertex(const T &in);
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template<class T>
inline bool Graph<T>::addVertex(const T& in) {
	Vertex<T> *v = new Vertex<T>(in);

	bool accept = true;
	for(unsigned int i = 0; i < vertexSet.size(); i++){

		if (vertexSet[i]->info == in){
			accept = false;
			break;
		}

	}

	if (accept){
		vertexSet.push_back(v);
	}
	return accept;

}

template<class T>
inline bool Graph<T>::addEdge(const T& sourc, const T& dest, string streetName) {

	bool foundS = false;
	bool foundD = false;
	int posSource = -1, posDest = -1;



	for(unsigned int i = 0; i < vertexSet.size(); i++){

		if(vertexSet[i]->info == sourc){

			foundS = true;
			posSource = i;

		}

		if(vertexSet[i]->info == dest){
			posDest = i;
			foundD = true;
		}

		if(foundS && foundD)
			break;

	}
	if(foundS && foundD){
		//Vertex<T> *v = new Vertex<T>(dest);
		Edge<T> *eDest = new Edge<T>(vertexSet[posDest],streetName);
		Edge<T> *eSource = new Edge<T>(vertexSet[posSource],streetName);

		vertexSet[posSource]->addEdge(*eDest);
		vertexSet[posDest]->addEdge(*eSource);
	}

	return (foundS && foundD);


}

template<class T>
inline bool Vertex<T>::addEdge(Edge<T> &edge) {

	adj.push_back(edge);
	return true;

}

template<class T>
bool Graph<T>::removeVertex(const T& in) {




}

template<class T>
inline int Vertex<T>::findEdge(Vertex<T> v) {

	bool found = false;
	int result;

	for(unsigned int i = 0; i < adj.size(); i++){

		if(adj[i].dest->info ==
				v.info){
			result = i;
			found = true;
			break;
		}

	}
	if(!found)
		result = -1;


	return result;

}

#endif /* GRAPH_H_ */
