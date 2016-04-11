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
	float weight; //para o algoritmo dijkstra
public:
	Vertex(T in);
	vector<Edge<T>  > getAdj();
	int findSmallestAdj(); //retorna posicao no vetor adj da aresta mais pequena ligada a este nó
	float getWeight();
	bool getVisited();
	void setVisited(bool visited);
	void setNewWeight(float nWeight);
	bool addEdge(Edge<T> &edge);
	int findEdge(Vertex<T> v);
	friend class Graph<T>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false), weight(9999999.0){}


template <class T>
class Edge { // ruas
	Vertex<T> * dest;
	string streetName;
	float distance;

public:
	Edge(Vertex<T> *d, string sName,float dis);

	Vertex<T> getDest();
	float getDistance();
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, string sName, float dis): dest(d), streetName(sName),distance(dis){}

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
public:
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;
	int addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, string streetName, float distance);
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
inline int Graph<T>::addVertex(const T& in) {

	for(unsigned int i = 0; i < vertexSet.size(); i++){

		if (vertexSet[i]->info == in)
			return i;

	}

	Vertex<T> *v = new Vertex<T>(in);
	vertexSet.push_back(v);

	return vertexSet.size();

}

template<class T>
inline bool Graph<T>::addEdge(const T& sourc, const T& dest, string streetName, float distance) {

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
		Edge<T> *eDest = new Edge<T>(vertexSet[posDest],streetName, distance);
		Edge<T> *eSource = new Edge<T>(vertexSet[posSource],streetName,distance);

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
inline void Vertex<T>::setVisited(bool visited) {

	this->visited = visited;
}

template<class T>
inline void Vertex<T>::setNewWeight(float nWeight) {

	this->weight = nWeight;

}

template<class T>
inline vector<Edge<T> > Vertex<T>::getAdj() {

	return adj;

}

template<class T>
inline float Vertex<T>::getWeight() {

	return weight;

}

template<class T>
inline int Vertex<T>::findSmallestAdj() {

	int result = 999999;

	if (adj.size() == 0)
		result = -1;

	for (unsigned int i = 0; i < adj.size(); i++){

		if (adj[i]->getDistance < result)
			result = i;

	}

	return result;

}

template<class T>
inline bool Vertex<T>::getVisited() {

	return this->visited;

}

template<class T>
inline int Vertex<T>::findEdge(Vertex<T> v) {

	for(unsigned int i = 0; i < adj.size(); i++){

		if(adj[i].dest->info == v.info)
			return i;
	}

	return -1;
}

template<class T>
inline Vertex<T> Edge<T>::getDest() {

	return dest;
}

template<class T>
inline float Edge<T>::getDistance() {

	return distance;

}

#endif /* GRAPH_H_ */
