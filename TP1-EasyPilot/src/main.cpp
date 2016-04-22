#include "Graph.h"
#include "Intersection.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <math.h>
#include "graphviewer.h"
#include "GraphicData.h"


Graph<Intersection> *map;
GraphViewer *gv;
vector<graphicData> dg;

#define DEFAULT_COLOR "black"

#define PI 3.14159265
#define WIDTH 995
#define HEIGHT 829


void drawPathGV(Intersection source, Intersection target);

void readDataBase(string path){

	map = new Graph<Intersection>();

	ifstream dataBase(path.c_str());		//**pode variar
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

		map->addVertex(source);
		map->addVertex(target);

		map->addEdge(source, target, args[1], atof(args[4].c_str()));

	}


	// tests
	/*int counteradj=0, counterindeg=0;
	for(unsigned int i=0; i<map->getNumVertex(); i++){

		counteradj += map->getVertexSet()[i]->getAdj().size();
		counterindeg += map->getVertexSet()[i]->getIndegree();
		//cout << "Adj: " << map->getVertexSet()[i]->getAdj().size() << endl;			//com origem no no
		//cout << "Indegree: " << map->getVertexSet()[i]->getIndegree() << endl;		//apontam para o no
	}*/

	cout << "Nodes: " << map->getNumVertex() << endl;


	map->Dijkstra(map->getVertexSet()[map->getVertexByID(1012)]->getIntersection());
	drawPathGV(map->getVertexSet()[map->getVertexByID(1012)]->getIntersection(), map->getVertexSet()[map->getVertexByID(28566)]->getIntersection());


	//cout << "Edges: " << counteradj << endl;
	//cout << "Indegrees: " << counterindeg << endl;

}


vector<float> convertGeoCordToPixel(float lon, float lat){

	vector<float> res;

	float longLeft = -8.647, longRight = -8.55;
	float latBottom = 41.065, latTop = 41.185;

	float deltaLong = longRight - longLeft;
	float bottomDegree = latBottom * PI / 180;

	float worldMapWidth = ((WIDTH / deltaLong) * 360) / (2 * PI);
	float windowOffsetY = (worldMapWidth / 2 * log((1 + sin(bottomDegree)) / (1 - sin(bottomDegree))));

	res.push_back( ((lon - longLeft) * (WIDTH / deltaLong)));		//res[0] = x

	res.push_back( (HEIGHT -((worldMapWidth / 2 * log((1 + sin(lat * PI / 180) ) / (1 - sin(lat * PI / 180) ))) - windowOffsetY)) );		//res[1] = y

	return res;
}


void loadMap() {

	gv = new GraphViewer(WIDTH, HEIGHT, false);
	gv->setBackground("res/background.png");
	gv->createWindow(WIDTH, HEIGHT);
	gv->setVertexSize(0.1, 0.1);

	//gv->defineVertexColor(DEFAULT_COLOR);
	//gv->defineEdgeColor(DEFAULT_COLOR);

	float x, y;
	int ids, idd;

	for(unsigned i=0; i<map->getNumVertex(); i++){

		Intersection source = map->getVertexSet()[i]->getIntersection();
		ids = source.getID();

		x = convertGeoCordToPixel(source.getCoord().x, source.getCoord().y)[0];
		y = convertGeoCordToPixel(source.getCoord().x, source.getCoord().y)[1];

		gv->addNode(ids, x, y);

		ostringstream convert;
		convert << ids;

		gv->setVertexLabel(ids, convert.str());
		gv->setVertexColor(ids, "red");


		for(unsigned j=0; j<map->getVertexSet()[i]->getAdj().size(); j++){

			Intersection dest = map->getVertexSet()[i]->getAdj()[j].getDest()->getIntersection();
			idd = dest.getID();

			x = convertGeoCordToPixel(dest.getCoord().x, dest.getCoord().y)[0];
			y = convertGeoCordToPixel(dest.getCoord().x, dest.getCoord().y)[1];

			gv->addNode(idd, x, y);

			ostringstream convert2;
			convert2 << idd;

			gv->setVertexLabel(idd, convert2.str());
			gv->setVertexColor(idd, "green");

			gv->addEdge(map->getVertexSet()[i]->getAdj()[j].getID(), ids, idd, EdgeType::DIRECTED);
			gv->setEdgeLabel(map->getVertexSet()[i]->getAdj()[j].getID(), map->getVertexSet()[i]->getAdj()[j].getName());

			//cout << map->getVertexSet()[i]->getAdj()[j].getID() << endl;

		}

	}

	gv->rearrange();

	return;

}


int getEdgeID(int a, int b) {
	for(int i = 0; i < dg.size(); i++) {
		if(dg[i].id_origem == a && dg[i].id_destino == b) {
			return dg[i].id_aresta;
		}
	}
	return -1;
}


void menu() {
	system("CLS");

	int origem;
	int destino;

	cout << endl;
	cout << "Onde se encontra?";
	cin >> origem;
	destino = origem;
	while(destino == origem) {
		cout << "Qual e a rua de destino: " << endl;
		cin >> destino;
		if(destino == origem) {
			cout << "A rua que pretende ir e invalida: " << endl;
			return;
		}

		Intersection destInt = map->getVertexSet()[origem]->getIntersection();
		map->Dijkstra(map->getVertexSet()[origem]->getIntersection());
		vector <Intersection> path = map->getPath(map->getVertexSet()[origem]->getIntersection(), map->getVertexSet()[destino]->getIntersection());
		system("CLS");
		Intersection last;
		cout << "O caminho mais curto: " << endl;
		for(unsigned int i = 0; i < path.size(); i++){
			if(i > 0){
				int id1 = map->getFirstID(last.getID());
				int id2 = map->getFirstID(path[i].getID());
				gv->setEdgeColor(getEdgeID(id1,id2), "green");
				gv->setEdgeThickness(getEdgeID(id1,id2), 8);
			}
			stringstream ss;
			ss << path[i].getID() << " (linha " << path[i].getID() << ")";
			string str = ss.str();
			cout << str << endl;
			last = path[i];
		}

		gv->rearrange();
		getchar();
	}
}

void drawPathGV(Intersection source, Intersection target){

	gv = new GraphViewer(WIDTH, HEIGHT, false);
	gv->setBackground("res/background.png");
	gv->createWindow(WIDTH, HEIGHT);

	if(map->findVertex(source) > -1 && map->findVertex(target) > -1){

		cout << "Tamanho Path: " << map->getPath(source, target).size() << endl;

		cout << "Source index: " << map->findVertex(source) << " Source id: " << map->getVertexSet()[map->findVertex(source)]->getIntersection().getID() << endl;
		cout << "Target index: " << map->findVertex(target) << " Target id: " << map->getVertexSet()[map->findVertex(target)]->getIntersection().getID() << endl;

		for(unsigned i=0; i<map->getPath(source, target).size(); i++){

			gv->addNode(map->getPath(source, target)[i].getID(), convertGeoCordToPixel(map->getPath(source, target)[i].getCoord().x, map->getPath(source, target)[i].getCoord().y)[0], convertGeoCordToPixel(map->getPath(source, target)[i].getCoord().x, map->getPath(source, target)[i].getCoord().y)[1]);

			ostringstream id;
			id << map->getPath(source, target)[i].getID();

			gv->setVertexLabel(map->getPath(source, target)[i].getID(), id.str());
			gv->setVertexColor(map->getPath(source, target)[i].getID(), id.str());

			int indexS, indexN;

			indexS = map->findVertex(map->getPath(source, target)[i]);

			indexN = map->findVertex(map->getPath(source, target)[i+1]);

			cout << "index: " << indexS << " id: " << map->getPath(source, target)[i].getID() << endl;

			if(indexN > -1){

				cout << "index next: " << indexN << " id next: " << map->getPath(source, target)[i+1].getID() << endl;

				int idEdge;

				idEdge = map->getVertexSet()[indexS]->getAdj()[map->getVertexSet()[indexS]->findEdgeByID(map->getVertexSet()[indexN]->getIntersection().getID())].getID();

				gv->addEdge(idEdge, map->getPath(source, target)[i].getID(), map->getPath(source, target)[i+1].getID(), EdgeType::DIRECTED); //id edge, id source, id destino, type

			}

		}

	}

	gv->rearrange();
}

int main(){

	string dbpath = "res/Data.txt";

	readDataBase(dbpath);

	//loadMap();

	//menu();

	getchar();

	return 0;
}
