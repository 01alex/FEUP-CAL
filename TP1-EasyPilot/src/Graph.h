/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <string>
#include <climits>
#include <list>
#include <iostream>
#include <queue>
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
	int indegree;		//numero arestas que apontam para este no
	bool processing;

public:
	Vertex *path;

	Vertex(T in);

	T getIntersection() const;
	vector<Edge<T> > getAdj() const;

	bool getVisited() const;
	void setVisited(bool v);

	float getDistance() const;
	void setDistance(float d);

	int getIndegree() const;
	void setIndegree(int i);

	bool addEdge(Edge<T> &edge);
	int findEdge(Vertex<T> v);		//retorna posicao no vetor adj se existir, se nao -1

	int findSmallestAdj(); 			//retorna posicao no vetor adj da aresta mais pequena ligada a este nó
	friend class Graph<T>;
};

template <class T>
struct vertex_greater_than {
	bool operator()(Vertex<T> * a, Vertex<T> * b) const {
		return a->getDistance() > b->getDistance();
	}
};

template <class T>
Vertex<T>::Vertex(T in): intersect(in), visited(false), indegree(0), processing(false){}


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
inline int Vertex<T>::getIndegree() const {
	return indegree;
}

template<class T>
inline void Vertex<T>::setIndegree(int i) {
	this->indegree = i;
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

	int addVertex(const T &in);		//devolve posicao do vetor em que se encontra o vertice, push_back se nao existia e devolve vector.size();
	bool addEdge(const T &sourc, const T &dest, string name, float length);

	bool removeVertex(const T &in);							//TODO
	bool removeEdge(const T &source, const T &dest);		//TODO

	void Dijkstra(const T &start);
	vector<int> getPath(const T &source, const T &dest);
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
		if(vertexSet[i]->getIntersection() == in)
			return i;
	}

	Vertex<T> *v = new Vertex<T>(in);
	vertexSet.push_back(v);

	return vertexSet.size();
}

template<class T>
inline bool Graph<T>::addEdge(const T& sourc, const T& dest, string name, float length) {		//adiciona aos adj do vsrc o edge(vdest) e incrementa o indegree do vdest

	bool foundS = false, foundD = false;
	int posSource = -1, posDest = -1;

	for(unsigned int i = 0; i < vertexSet.size(); i++){			//verifica se vertices existem no grafo

		if(foundS && foundD)
			break;

		if(vertexSet[i]->getIntersection() == sourc){
			posSource = i;
			foundS = true;
		}
		if(vertexSet[i]->getIntersection() == dest){
			posDest = i;
			foundD = true;
		}

	}

	if(foundS && foundD){
		Edge<T> *edg = new Edge<T>(vertexSet[posDest], name, length);

		vertexSet[posSource]->addEdge(*edg);
		vertexSet[posDest]->indegree++;

	}

	return (foundS && foundD);
}


template<class T>
bool Graph<T>::removeVertex(const T& in) {

	bool res = false;
	int pos;

	for(unsigned i=0; i<vertexSet.size(); i++){
		if(vertexSet[i].getIntersection() == in){
			pos = i;
			res = true;
		}
	}

	if(!res)
		return res;

}

template<class T>
bool Graph<T>::removeEdge(const T &source, const T &dest){

}


template<class T>
void Graph<T>::Dijkstra(const T &start){		//baseado teorica 06.grafos2_a

	for(unsigned i=0; i<getNumVertex(); i++){
		vertexSet[i]->path = NULL;
		vertexSet[i]->setDistance(INFINITY);
		vertexSet[i]->processing = false;
	}

	Vertex<T> *s = vertexSet[addVertex(start)];
	s->setDistance(0);

	vector<Vertex<T>*> pq;

	pq.push_back(s);

	make_heap(pq.begin(), pq.end());

	while(!pq.empty()){

		Vertex<T> *v = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		for(unsigned i=0; i<v->adj.size(); i++){

			Vertex<T> *w = v->adj[i].dest;

			if( (v->distance + v->adj[i].length) < w->distance){

				w->setDistance(v->distance + v->adj[i].length);
				w->path = v;

				if(!w->processing){
					w->processing = true;
					pq.push_back(w);
				}

				make_heap(pq.begin(), pq.end(), vertex_greater_than<T>());
			}
		}
	}

	cout << pq[0]->getDistance() << endl;				//a apagar\

}

template<class T>
vector<int> Graph<T>::getPath(const T &source, const T &dest){

	Vertex<T> *v = vertexSet[addVertex(dest)];
	list<T> aux;

	aux.push_front(v->getIntersection());

	while(v->path != NULL && v->path->getIntersection() != source){
		v = v->path;
		aux.push_back(v->getIntersection());
	}

	if( v->path != NULL )
		aux.push_front(v->path->getIntersection());


	vector<int> paths;
	while( !aux.empty() ) {
		paths.push_back( aux.front().getID() );
		aux.pop_front();
	}

	return paths;
}


#endif /* GRAPH_H_ */
