/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <string>
#include <climits>
#include <iostream>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;

const int INFINITY = INT_MAX;


// VERTEX
template <class T>
class Vertex { //cruzamentos

	T intersect;
	vector<Edge<T> > adj;
	bool visited;
	float distance;

public:
	Vertex(T in);

	T getIntersection() const;
	vector<Edge<T> > getAdj() const;

	bool getVisited() const;
	void setVisited(bool v);

	float getDistance() const;
	void setDistance(float d);

	bool addEdge(Edge<T> &edge);
	int findEdge(Vertex<T> v);		//retorna posicao no vetor adj se existir, se nao -1

	int findSmallestAdj(); 			//retorna posicao no vetor adj da aresta mais pequena ligada a este nó
	friend class Graph<T>;
};

template <class T>
Vertex<T>::Vertex(T in): intersect(in), visited(false), distance(INFINITY){}


template<class T>
inline T Vertex<T>::getIntersection() const {
	return intersect;
}

template<class T>
inline vector<Edge<T> > Vertex<T>::getAdj() const {
	return adj;
}


template<class T>
inline bool Vertex<T>::getVisited() const {
	return visited;
}

template<class T>
inline void Vertex<T>::setVisited(bool v) {
	this->visited = v;
}


template<class T>
inline float Vertex<T>::getDistance() const {
	return distance;
}

template<class T>
inline void Vertex<T>::setDistance(float d) {
	this->distance = d;
}


template<class T>
inline bool Vertex<T>::addEdge(Edge<T> &edge) {

	adj.push_back(edge);
	return true;

}

template<class T>
inline int Vertex<T>::findEdge(Vertex<T> v) {

	for(unsigned int i = 0; i < adj.size(); i++){
		if(adj[i].dest->getIntersection() == v.getIntersection())
			return i;
	}

	return -1;
}


template<class T>
inline int Vertex<T>::findSmallestAdj() {

	int result = 999999;

	if (adj.size() == 0)
		result = -1;

	for (unsigned int i = 0; i < adj.size(); i++){
		if (adj[i]->getDistance() < result)
			result = i;
	}

	return result;
}





// EDGE
template <class T>
class Edge { // ruas

	Vertex<T> * dest;
	string name;
	float length;

public:
	Edge(Vertex<T> *d, string n, float l);

	Vertex<T> getDest() const;
	float getLength() const;

	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, string n, float l): dest(d), name(n), length(l){}


template<class T>
inline Vertex<T> Edge<T>::getDest() const {
	return dest;
}

template<class T>
inline float Edge<T>::getLength() const {
	return length;
}





// GRAPH
template <class T>
class Graph {

	vector<Vertex<T> *> vertexSet;

public:
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;

	int addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, string name, float length);

	bool removeVertex(const T &in);							//TODO
	bool removeEdge(const T &source, const T &dest);		//TODO
};

template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}


template<class T>
inline int Graph<T>::addVertex(const T& in) {

	for(unsigned int i = 0; i < vertexSet.size(); i++){
		if (vertexSet[i]->getIntersection() == in)
			return i;
	}

	Vertex<T> *v = new Vertex<T>(in);
	vertexSet.push_back(v);

	return vertexSet.size();
}

template<class T>
inline bool Graph<T>::addEdge(const T& sourc, const T& dest, string name, float length) {

	bool foundS = false;
	bool foundD = false;
	int posSource = -1, posDest = -1;

	for(unsigned int i = 0; i < vertexSet.size(); i++){

		if(vertexSet[i]->getIntersection() == sourc){
			foundS = true;
			posSource = i;
		}

		if(vertexSet[i]->getIntersection() == dest){
			posDest = i;
			foundD = true;
		}

		if(foundS && foundD)
			break;

	}

	if(foundS && foundD){
		//Vertex<T> *v = new Vertex<T>(dest);
		Edge<T> *eDest = new Edge<T>(vertexSet[posDest],name, length);
		Edge<T> *eSource = new Edge<T>(vertexSet[posSource], name, length);

		vertexSet[posSource]->addEdge(*eDest);
		vertexSet[posDest]->addEdge(*eSource);
	}

	return (foundS && foundD);
}



template<class T>
bool Graph<T>::removeVertex(const T& in) {

}

template<class T>
bool removeEdge(const T &source, const T &dest){

}


#endif /* GRAPH_H_ */
