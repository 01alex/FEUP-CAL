#include "GPS.h"

Graph<Intersection> *map;
GraphViewer *gv;
vector<graphicData> dg;

void readDataBase(string path){

	ofstream teste("teste.csv");

	teste << "ITERACAO / TEMPO" << endl;



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

		if(atof(args[6].c_str()) > longitudeMin && atof(args[6].c_str()) < longitudeMax && atof(args[7].c_str()) > latitudeMin && atof(args[7].c_str() ) < latitudeMax )
		{

			if(atof(args[8].c_str()) > longitudeMin && atof(args[8].c_str()) < longitudeMax && atof(args[9].c_str()) > latitudeMin && atof(args[9].c_str() ) < latitudeMax )
			{

				map->addVertex(source);
				map->addVertex(target);

				map->addEdge(source, target, args[1], atof(args[4].c_str()), atof(args[5].c_str()));

			}

		}

		/*map->addVertex(source);
		map->addVertex(target);

		map->addEdge(source, target, args[1], atof(args[4].c_str()), atof(args[5].c_str()));*/

	}


	cout << "Nodes: " << map->getNumVertex() << endl;

	clock_t t;
	t = clock();

	//map->DijkstraShortestPath(map->getVertexSet()[map->getVertexByID(4750)]->getIntersection());
	//map->DijkstraFastestPath(map->getVertexSet()[map->getVertexByID(1012)]->getIntersection());

	map->aStar(map->getVertexSet()[map->getVertexByID(4750)]->getIntersection(), map->getVertexSet()[map->getVertexByID(2755)]->getIntersection(), false);

	//for(int i = 0; i < 20; i++){
	//map->DijkstraShortestPath(map->getVertexSet()[map->getVertexByID(13257)]->getIntersection());
	//drawPathGV(map->getVertexSet()[map->getVertexByID(17358)]->getIntersection(), map->getVertexSet()[map->getVertexByID(2755)]->getIntersection());		//map->aStar(map->getVertexSet()[map->getVertexByID(13257)]->getIntersection(), map->getVertexSet()[map->getVertexByID(1786)]->getIntersection(), true);


	t = clock() - t;

	float r = (float)t / CLOCKS_PER_SEC;


	cout << "TEMPO: " << setprecision(10) << r << endl;
	cout << fixed;




	/* TESTS
	int counteradj=0, counterindeg=0;
		for(unsigned int i=0; i<map->getNumVertex(); i++){
			counteradj += map->getVertexSet()[i]->getAdj().size();
			counterindeg += map->getVertexSet()[i]->getIndegree();
			//cout << "Adj: " << map->getVertexSet()[i]->getAdj().size() << endl;			//com origem no no
			//cout << "Indegree: " << map->getVertexSet()[i]->getIndegree() << endl;		//apontam para o no
	}
	cout << "Edges: " << counteradj << endl;
	cout << "Indegrees: " << counterindeg << endl; */

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






void drawPathGV(Intersection source, Intersection target){
	/*cout << "aqui no inicio" << endl;
	gv = new GraphViewer(WIDTH, HEIGHT, false);
	gv->setBackground("res/background.png");
	gv->createWindow(WIDTH, HEIGHT);*/

	cout <<endl<< "aqui!" << endl;

	if(map->findVertex(source) > -1 && map->findVertex(target) > -1){



		cout << "Tamanho Path: " << map->getPath(source, target).size() << endl;

		cout << "Source index: " << map->findVertex(source) << " Source id: " << map->getVertexSet()[map->findVertex(source)]->getIntersection().getID() << endl;

		cout << "Target index: " << map->findVertex(target) << " Target id: " << map->getVertexSet()[map->findVertex(target)]->getIntersection().getID() << endl;

		for(unsigned i=0; i<map->getPath(source, target).size(); i++){

			//gv->addNode(map->getPath(source, target)[i].getID(), convertGeoCordToPixel(map->getPath(source, target)[i].getCoord().x, map->getPath(source, target)[i].getCoord().y)[0], convertGeoCordToPixel(map->getPath(source, target)[i].getCoord().x, map->getPath(source, target)[i].getCoord().y)[1]);

			ostringstream id;
			id << map->getPath(source, target)[i].getID();

			//gv->setVertexLabel(map->getPath(source, target)[i].getID(), id.str());
			//gv->setVertexColor(map->getPath(source, target)[i].getID(), id.str());

			int indexS, indexN;

			indexS = map->findVertex(map->getPath(source, target)[i]);

			indexN = map->findVertex(map->getPath(source, target)[i+1]);

			cout << "index: " << indexS << " id: " << map->getPath(source, target)[i].getID() << " distance: " << map->getVertexSet()[map->findVertex(map->getPath(source, target)[i])]->getDistance() << "km" << endl;					//if DijkstraShortestPath

			//cout << "index: " << indexS << " id: " << map->getPath(source, target)[i].getID() << " time: " << map->getVertexSet()[map->findVertex(map->getPath(source, target)[i])]->getTime() << "h" << endl;						//if DijkstraFastestPath

			if(indexN > -1){

				cout << "index next: " << indexN << " id next: " << map->getPath(source, target)[i+1].getID() << endl;

				int idEdge;

				idEdge = map->getVertexSet()[indexS]->getAdj()[map->getVertexSet()[indexS]->findEdgeByID(map->getVertexSet()[indexN]->getIntersection().getID())].getID();

				//gv->addEdge(idEdge, map->getPath(source, target)[i].getID(), map->getPath(source, target)[i+1].getID(), EdgeType::DIRECTED); //id edge, id source, id destino, type

			}

		}

	}

	//gv->rearrange();
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

		if(source.getIP()){ //interest points a azul

			gv->setVertexColor(ids, "blue");
		}

		else // outros a vermelho
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


void addInterestPointsMenu(){ //funcao a chamar no menu para adicionar PI's pi's so ficam de cor diferente

	if (map->getNumVertex() == 0){

		cout << "Graph is empty " << endl;
		return;
	}
	int ind;

	bool add = true;

	while (add){

		cout << "ID do vertice a acrescentar um ponto de interesse(-1 to exit): ";
		cin >> ind;
		if(ind == -1){

			add = false;
			break;

		}
		if(map->getVertexByID(ind) == -1){

			cout << "Vertice nao encontrado" << endl;
		}

		else{

			map->getVertexSet()[ind]->getIntersection().setIP(true);
			cout << "PI adicionado!" << endl;

		}
	}
	gv->rearrange();

	return;

}

void GPSMenu(){


	int origem;
	int destino;
	int algorithm;
	loadMap();


	cout << endl << "Mapa carregado!" << endl;

	cout << "A-star(0) ou dijkstra(1)? "; //devia garantir que é 0 ou 1
	cin >> algorithm;

	cout << endl << "Rua de origem(vertice)(1012 pa testar): ";
	cin >>origem;

	cout << "Qual e a rua de destino(28566 p testar): " << endl;
	cin >> destino;

	gv->closeWindow();

	if(destino == origem) {
		cout << "A rua que pretende ir e invalida: " << endl;
		return;
	}

	clock_t t;
	t = clock();




	if(algorithm == 1){
		map->DijkstraShortestPath(map->getVertexSet()[map->getVertexByID(origem)]->getIntersection());
	}

	else{
		map->aStar(map->getVertexSet()[map->getVertexByID(origem)]->getIntersection(), map->getVertexSet()[map->getVertexByID(destino)]->getIntersection(),1);
	}



	cout << "Algorithm complete" << endl;
	drawPathGV(map->getVertexSet()[map->getVertexByID(origem)]->getIntersection(), map->getVertexSet()[map->getVertexByID(destino)]->getIntersection());
	cout << "Mapa desenhado!" << endl;

	t = clock() - t;

	float r = (float)t / CLOCKS_PER_SEC;


	cout << " TEMPO: " << setprecision(10) << r << endl;
	cout << fixed;

	/*vector <Intersection> path = map->getPath(map->getVertexSet()[origem]->getIntersection(), map->getVertexSet()[destino]->getIntersection());
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
		}*/



	//gv->rearrange();
	//getchar();



	//cin.clear();
	//char exit = getchar();
	//gv->closeWindow();
	char exit;
	do {
		cout <<endl<< "Enter para continuar (fecha o mapa)" << endl;

		cin.clear();
		cin.ignore();
		exit=getchar();
		//putchar (c);
	} while (exit != '\n');

	gv->closeWindow();



	return;

}


void menu() {
	//system("CLS");

	int escolha;
	bool loop = true;


	cout << endl;

	do{


		cout <<setw(20)<< "Menu Principal" << endl << endl;

		cout << "1: Usar GPS" << endl;
		cout << "2: Adicionar Ponte de Interesse" << endl;
		cout << "3: Adicionar obras (FALTA IMPLEMENTAR)" << endl;
		cin >> escolha;


		switch(escolha)
		{
		case 1: GPSMenu();
		break;


		case 2: addInterestPointsMenu();
		break;



		default: break;
		}

		cout << "Voltar ao menu principal(S/N)? ";
		char inp;
		cin >>inp;

		if(inp =='S')
			loop = true;
		else
			loop = false;



	}while(loop);



}

