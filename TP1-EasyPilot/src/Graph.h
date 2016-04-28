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

const int INF = INT_MAX;


// VERTEX
template <class T>
class Vertex { //cruzamentos

	T intersect;
	vector<Edge<T> > adj;
	bool visited;
	float distance;
	float time;
	int indegree;		//numero arestas que apontam para este no
	bool processing, closed, inQueue;

public:

	Vertex(T in);

	T getIntersection() const;
	vector<Edge<T> > getAdj() const;

	bool getVisited() const;
	void setVisited(bool v);

	float getDistance() const;
	void setDistance(float d);

	float getTime() const;
	void setTime(float t);

	int getIndegree() const;
	void setIndegree(int i);
	void updateFlood(Vertex<T> &vertex);

	bool addEdge(Edge<T> &edge);
	int findEdge(Vertex<T> &v);		//retorna posicao no vetor adj se existir, se nao -1
	int findEdgeByID(int id);

	Vertex *path;

	float fx;			//Astar

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
struct vertex_greater_than_time {
	bool operator()(Vertex<T> * a, Vertex<T> * b) const {
		return a->getTime() > b->getTime();
	}
};

template <class T>
struct vertex_greater_than_fx {
	bool operator()(Vertex<T> * a, Vertex<T> * b) const {
		return a->fx < b->fx;
	}
};

template <class T>
float heuristic_aStar(Vertex<T> *s, Vertex<T> *t, bool dt){
	return (sqrt(pow(s->getIntersection().getCoord().x - t->getIntersection().getCoord().x, 2) + pow(s->getIntersection().getCoord().y - t->getIntersection().getCoord().y, 2)));
}

template <class T>
Vertex<T>::Vertex(T in): intersect(in), visited(false), indegree(0), processing(false){path = NULL;}


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
inline float Vertex<T>::getTime() const{
	return time;
}

template<class T>
inline void Vertex<T>::setTime(float t){
	this->time = t;
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
inline int Vertex<T>::findEdge(Vertex<T> &v) {

	for(unsigned int i = 0; i < adj.size(); i++){
		if(adj[i].dest->getIntersection() == v.getIntersection())
			return i;
	}

	return -1;
}

template<class T>
inline int Vertex<T>::findEdgeByID(int id){

	for(unsigned int i = 0; i < adj.size(); i++){
		if(adj[i].dest->getIntersection().getID() == id)
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



/*template<class T>
void Vertex<T>::updateFlood(Vertex<T> &vertex) {
	if((vertex->closed != NULL) && (!(vertex->closed)))
		return;

	for(int i = 0; i < vertex->adj.size(); i++) {

		vertex->adj[i]->distance = vertex->distance + vertex->adj[i].length;
		vertex->adj[i]->fx = vertex->adj[i]->distance + heuristic_aStar(neighbour, vertexSet[addVertex(goal)], dist);
		updateFlood(vertex->adj[i].dest;

	}
}*/



// EDGE
template <class T>
class Edge { // ruas

	Vertex<T> * dest;
	string name;
	float length;
	float vMax;
	static int ID;
	int thisID;

public:
	Edge(Vertex<T> *d, string n, float l, float vm);
	Edge();

	Vertex<T>* getDest() const;
	string getName() const;
	float getLength() const;
	float getVMax() const;
	int getID() const;

	friend class Graph<T>;
	friend class Vertex<T>;
};

template<class T>
int Edge<T>::ID = 0;

template <class T>
Edge<T>::Edge(Vertex<T> *d, string n, float l, float vm): dest(d), name(n), length(l), vMax(vm), thisID(ID++){}

template <class T>
Edge<T>::Edge(): thisID(ID++){}

template<class T>
inline Vertex<T>* Edge<T>::getDest() const {
	return dest;
}

template<class T>
inline string Edge<T>::getName() const{
	return name;
}

template<class T>
inline float Edge<T>::getLength() const {
	return length;
}

template<class T>
inline float Edge<T>::getVMax() const{
	return vMax;
}

template<class T>
inline int Edge<T>::getID() const {
	return thisID;
}





// GRAPH
template <class T>
class Graph {

	vector<Vertex<T> *> vertexSet;

public:

	Graph();

	vector<Vertex<T> *> getVertexSet() const;
	unsigned int getNumVertex() const;

	int addVertex(const T &in);		//devolve posicao do vetor em que se encontra o vertice, push_back se nao existia e devolve vector.size();
	bool addEdge(const T &sourc, const T &dest, string name, float length, float vm);

	bool removeVertex(const T &in);							//TODO
	bool removeEdge(const T &source, const T &dest);		//TODO

	void DijkstraShortestPath(const T &start);
	void DijkstraFastestPath(const T &start);
	void updateFlood(Vertex<T>* vertex, T goal);

	void aStar(const T &start, const T &goal, bool dist);

	vector<T> getPath(const T &source, const T &dest);

	int findVertex(const T &f);			//pela interseccao
	int getVertexByID(int id);			//pelo id da interseccao

	int getFirstID(int id) {
		for(int i = 0; i < vertexSet.size(); i++) {
			if(vertexSet[i]->getIntersection().getID() == id && vertexSet[i]->getIntersection().getID() >= 0) {
				return vertexSet[i]->getIntersection().getID();
			}
		}
		return -1;
	}

	friend class Vertex<T>;

};

template<class T>
void removeFromQueue(vector<Vertex<T>*> pq, const T &v){
	for(unsigned i=0; i<pq.size(); i++){
		if(pq[i]->getIntersection() == v)
			pq.erase(pq.begin() + i);
	}
}

template<class T>
inline Graph<T>::Graph() {}

template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
unsigned int Graph<T>::getNumVertex() const {
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
inline bool Graph<T>::addEdge(const T& sourc, const T& dest, string name, float length, float vm) {		//adiciona aos adj do vsrc o edge(vdest) e incrementa o indegree do vdest

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

		Edge<T> edg(vertexSet[posDest], name, length, vm);

		vertexSet[posSource]->addEdge(edg);
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
void Graph<T>::DijkstraShortestPath(const T &start){		//baseado teorica 06.grafos2_a

	for(unsigned i=0; i<getNumVertex(); i++){
		vertexSet[i]->path = NULL;
		vertexSet[i]->setDistance(INF);
		vertexSet[i]->processing = false;
	}

	Vertex<T> *s = vertexSet[addVertex(start)];
	s->setDistance(0);

	vector<Vertex<T>*> pq;

	pq.push_back(s);

	make_heap(pq.begin(), pq.end());

	while(!pq.empty()){

		s = pq.front(); // diferente do git daquele gaj
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		for(unsigned i=0; i<s->adj.size(); i++){

			Vertex<T> *w = s->adj[i].dest;

			if( (s->distance + s->adj[i].length) < w->distance){

				w->setDistance(s->distance + s->adj[i].length);
				w->path = s;

				if(!w->processing){
					w->processing = true;
					pq.push_back(w);
				}

				make_heap(pq.begin(), pq.end(), vertex_greater_than<T>());
			}
		}
	}

	//cout << pq[0]->getDistance() << endl;				//a apagar
}

template<class T>
void Graph<T>::DijkstraFastestPath(const T &start){		//baseado teorica 06.grafos2_a

	for(unsigned i=0; i<getNumVertex(); i++){
		vertexSet[i]->path = NULL;
		vertexSet[i]->setTime(INF);
		vertexSet[i]->processing = false;
	}

	Vertex<T> *s = vertexSet[addVertex(start)];
	s->setTime(0);

	vector<Vertex<T>*> pq;

	pq.push_back(s);

	make_heap(pq.begin(), pq.end(), vertex_greater_than_time<T>());

	//make_heap(pq.begin(), pq.end());

	while(!pq.empty()){

		s = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		for(unsigned i=0; i<s->adj.size(); i++){

			Vertex<T> *w = s->adj[i].dest;

			if( (s->time + (s->adj[i].length / s->adj[i].getVMax())) < w->time){

				w->setTime(s->time + (s->adj[i].length / s->adj[i].getVMax()));
				w->path = s;

				if(!w->processing){
					w->processing = true;
					pq.push_back(w);
				}

				make_heap(pq.begin(), pq.end(), vertex_greater_than_time<T>());
			}
		}
	}
}


template<class T>
void Graph<T>::updateFlood(Vertex<T>* vertex, T goal) {
	if((vertex->closed != NULL) && (!(vertex->closed)))
		return;

	for(int i = 0; i < vertex->adj.size(); i++) {



		vertex->adj[i].getDest()->setDistance(vertex->adj[i].getDest()->getDistance()  + vertex->adj[i].getLength());
		vertex->adj[i].getDest()->fx = vertex->adj[i].getDest()->getDistance() + heuristic_aStar(vertex, vertexSet[addVertex(goal)],1);
		updateFlood(vertex->adj[i].getDest(), goal);
		//vertex->adj[i].getDest()->getDistance() = vertex->adj[i].getDest()->getDistance() + 2; //+ vertex->adj[i]->getLength();

		/*vertex->adj[i].getDest()->getDistance() = vertex->adj[i]->getDistance() + vertex->adj[i].getLength();
		vertex->adj[i]->fx = vertex->adj[i].getDest()->getDistance(); + heuristic_aStar(neighbour, vertexSet[addVertex(goal)], dist);
		updateFlood(vertex->adj[i].dest;*/

	}

	/* updateFlood(vertex) {
	 * if(vertex->closed != NULL && !vertex->closed)
	 * return;
	 *
	 * for(int i = 0; i < vertex->adj.size(); i++) {
	 *
	 * vertex->adj[i]->distance = vertex->distance + vertex->adj[i].length;
	 * vertex->adj[i]->fx = vertex->adj[i]->distance + heuristic_aStar(neighbour, vertexSet[addVertex(goal)], dist);
	 * updateFlood(vertex->adj[i].dest;
	 *
	 * }

	 */
}

template <class T>
void Graph<T>::aStar(const T &start, const T &goal, bool dist){ //MAKE THIS BOOL

	for(unsigned i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->distance = INF;
		vertexSet[i]->fx = INF;
		vertexSet[i]->closed = NULL;
		vertexSet[i]->inQueue = false;
	}


	Vertex<T> *s = vertexSet[addVertex(start)];

	s->setDistance(0);
	s->closed = false;
	s->fx = s->getDistance() + heuristic_aStar(s, vertexSet[addVertex(goal)], dist);

	//priority_queue< VertexPtr<T>, vector< VertexPtr<T> >, CompareVertex<T> > nextVertices;

	vector<Vertex<T>*> pq;		//nextVertices


	pq.push_back(s);
	s->inQueue = true;

	//cout << s->getIntersection().getID() << endl;

	make_heap(pq.begin(), pq.end(), vertex_greater_than_fx<T>());

	while (!pq.empty()) {
		Vertex<T> *current = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();


		current->inQueue = false; //extra(?)

		if (current == vertexSet[addVertex(goal)]){
			//current->path = vertexSet[addVertex(goal)];
			break;
		}

		current->closed = true;

		for(unsigned i = 0; i < current->adj.size(); i++) {
			Edge<T> edge = current->adj[i];
			Vertex<T> *neighbour = edge.dest;
			double weight = dist ? edge.length : neighbour->time;

			if(neighbour->closed == NULL) {
				cout << "Nem fechado nem aberto" << endl;
				neighbour->closed = false;
				neighbour->distance = current->distance + weight;
				neighbour->path = current;
				neighbour->fx = neighbour->distance + heuristic_aStar(neighbour, vertexSet[addVertex(goal)], dist);

				pq.push_back(vertexSet[addVertex(neighbour->getIntersection())]);

			}

			if (!neighbour->closed) {
				cout << "Nó aberto - aberto" << endl;//pertence à lista aberta
				if (neighbour->distance > current->distance + weight) {
					neighbour->distance = current->distance + weight;
					neighbour->path = current;
					neighbour->fx = neighbour->distance + heuristic_aStar(neighbour, vertexSet[addVertex(goal)], dist);
				}
			}


			if(neighbour->closed) {
				cout << "Nó fechado - processado" << endl;
				if(neighbour->distance > current->distance + weight) {
					neighbour->path = current;
					neighbour->distance = current->distance + weight;
					neighbour->fx = neighbour->distance + heuristic_aStar(neighbour, vertexSet[addVertex(goal)], dist);
					//updateFlood(neighbour, goal);
				}
			}

			make_heap(pq.begin(), pq.end(), vertex_greater_than_fx<T>());







			/*if (!neighbour->closed) {
				neighbour->distance = current->distance + weight;
				neighbour->path = current;
				neighbour->fx = neighbour->distance + heuristic_aStar(neighbour, vertexSet[addVertex(goal)], dist);


				if(neighbour->inQueue){
					removeFromQueue(pq, neighbour->getIntersection());
				}
				else neighbour->inQueue = true;

				pq.push_back(vertexSet[addVertex(neighbour->getIntersection())]);

			}

			else if (current->distance + weight + heuristic_aStar(neighbour, vertexSet[addVertex(goal)], dist) < neighbour->fx){

				neighbour->closed = false;
				neighbour->distance = current->distance + weight;
				neighbour->path = current;
				neighbour->fx = neighbour->distance + heuristic_aStar(neighbour, vertexSet[addVertex(goal)], dist);

				pq.push_back(vertexSet[addVertex(neighbour->getIntersection())]);

				neighbour->inQueue = true;

			}*/



		}
	}


	return;
}


template<class T>
vector<T> Graph<T>::getPath(const T &source, const T &dest){

	Vertex<T> *v = vertexSet[addVertex(dest)];
	list<T> aux;

	aux.push_front(v->getIntersection());

	while(v->path != NULL && v->path->getIntersection() != source){
		v = v->path;
		aux.push_front(v->getIntersection());
	}

	if( v->path != NULL )
		aux.push_front(v->path->getIntersection());


	vector<T> path;
	while( !aux.empty() ) {
		path.push_back( aux.front() );
		aux.pop_front();
	}

	return path;
}

template<class T>
inline int Graph<T>::findVertex(const T& f) {

	for(unsigned i=0; i<getNumVertex(); i++){
		if(vertexSet[i]->getIntersection() == f)
			return i;
	}

	return -1;		// se nao encontra

}

template<class T>
inline int Graph<T>::getVertexByID(int id) {

	for(unsigned i=0; i<getNumVertex(); i++){
		if(vertexSet[i]->getIntersection().getID() == id)
			return i;
	}

	return -1;		// se nao encontra
}

#endif /* GRAPH_H_ */
