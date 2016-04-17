#include "Graph.h"
#include "Intersection.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "graphviewer.h"
#include "GraphicData.h"

Graph<Intersection> map;
GraphViewer *gv;
vector<graphicData> dg;
#define NOT_DYNAMIC false
#define DEFAULT_COLOR "black"

void readDataBase(){

	ifstream dataBase("TP1-EasyPilot/res/Data.txt");		//**pode variar
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

		/*Intersection source(atoi(args[2].c_str()), atof(args[6].c_str()), atof(args[7].c_str()));
		Intersection target(atoi(args[3].c_str()), atof(args[8].c_str()), atof(args[9].c_str()));

		map.addVertex(source);
		map.addVertex(target);

		map.addEdge(source, target, args[1], atof(args[4].c_str()));*/


		float x1 = atof(args[2].c_str());
		float y1 = atof(args[3].c_str());
		int id = atoi(args[2].c_str());

		/*float xf1 = (x1) * 600 / 180;
		float yf1 = y1 * 600 / 360;*/



		if((map.addVertex(Intersection (atoi(args[2].c_str()), atof(args[6].c_str()), atof(args[7].c_str()))) > 0))
		{

			gv->addNode(atoi(args[2].c_str()), x1, y1);
			gv->setVertexLabel(atoi(args[2].c_str()),"teste");
			gv->setVertexColor( atof(args[2].c_str()), "green");
		}
		else
		{
			gv->setVertexColor(id, "black");

		}


	}

	// tests
	int counteradj=0, counterindeg=0;
	for(unsigned int i=0; i<map.getNumVertex(); i++){
		counteradj += map.getVertexSet()[i]->getAdj().size();
		counterindeg += map.getVertexSet()[i]->getIndegree();
		//cout << "Adj: " << map.getVertexSet()[i]->getAdj().size() << endl;			//com origem no no
		//cout << "Indegree: " << map.getVertexSet()[i]->getIndegree() << endl;		//apontam para o no
	}

	cout << "Nodes: " << map.getNumVertex() << endl;
	cout << "Edges: " << counteradj << endl;
	cout << "Indegrees: " << counterindeg << endl;
	//

}

void loadMap() {

	gv = new GraphViewer(600, 600, NOT_DYNAMIC);
	gv->setBackground("TP1-EasyPilot/res/background.png");
	gv->createWindow(600, 600);
	gv->defineVertexColor(DEFAULT_COLOR);
	gv->defineEdgeColor(DEFAULT_COLOR);

	readDataBase();

	gv->rearrange();

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



		Intersection destInt = map.getVertexSet()[origem]->getIntersection();
		map.Dijkstra(map.getVertexSet()[origem]->getIntersection());
		vector <Intersection> path = map.getPath(map.getVertexSet()[origem]->getIntersection(), map.getVertexSet()[destino]->getIntersection());
		system("CLS");
		Intersection last;
		cout << "O caminho mais curto: " << endl;
		for(unsigned int i = 0; i < path.size(); i++){
			if(i > 0){
				int id1 = map.getFirstID(last.getID());
				int id2 = map.getFirstID(path[i].getID());
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

int main(){

	loadMap();
	menu();
	getchar();




	//tests
	/*Intersection source(0, -2, 2);
	Intersection target1(1, 3, 5);
	Intersection target2(2, 6, 8);
	Intersection target3(3, 4, 5);



	map.addVertex(source);
	cout << "x: " << rX << endl;
	cout << "y: " << rY << endl;
	gv->addNode(0, rX, rY);
	map.addVertex(target1);
	//gv->addNode(0,219, 25);
	map.addVertex(target2);
	map.addVertex(target3);


	map.addEdge(source, target1, "belga", 35);
	map.addEdge(source, target2, "polsky", 13);
	map.addEdge(target1, target3, "rinus", 20);
	map.addEdge(target2, target3, "aveia", 20);

	map.Dijkstra(source);

	vector<int> v = map.getPath(source, target3);

	cout << "v.size() " << v.size() << endl;

	for(unsigned i=0; i<map.getPath(source, target3).size(); i++)
		cout << map.getPath(source, target3)[i] << endl;*/
	//


	return 0;

}
