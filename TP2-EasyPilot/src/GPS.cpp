#include "GPS.h"

Graph<Intersection> *map;
GraphViewer *gv;
bool running = true;
int algorithm;			//1-AStar	2-Dijkstra
vector<string> bestMatch;

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

		if(atof(args[6].c_str()) > longitudeMin && atof(args[6].c_str()) < longitudeMax && atof(args[7].c_str()) > latitudeMin && atof(args[7].c_str() ) < latitudeMax )
		{
			if(atof(args[8].c_str()) > longitudeMin && atof(args[8].c_str()) < longitudeMax && atof(args[9].c_str()) > latitudeMin && atof(args[9].c_str() ) < latitudeMax )
			{
				map->addVertex(source);
				map->addVertex(target);

				map->addEdge(source, target, args[1], atof(args[4].c_str()), atof(args[5].c_str()));
			}
		}
	}

	cout << "Nodes: " << map->getNumVertex() << endl;

}


vector<float> convertGeoCordToPixel(float lon, float lat){

	vector<float> res;

	float deltaLong = longitudeMax - longitudeMin;
	float bottomDegree = latitudeMin * PI / 180;

	float worldMapWidth = ((WIDTH / deltaLong) * 360) / (2 * PI);
	float windowOffsetY = (worldMapWidth / 2 * log((1 + sin(bottomDegree)) / (1 - sin(bottomDegree))));

	res.push_back( ((lon - longitudeMin) * (WIDTH / deltaLong)));		//res[0] = x

	res.push_back( (HEIGHT -((worldMapWidth / 2 * log((1 + sin(lat * PI / 180) ) / (1 - sin(lat * PI / 180) ))) - windowOffsetY)) );		//res[1] = y

	return res;
}


void drawPathGV(Intersection source, Intersection target){

	gv = new GraphViewer(WIDTH, HEIGHT, false);
	gv->setBackground("res/background2.png");
	gv->createWindow(WIDTH, HEIGHT);

	if(map->findVertex(source) > -1 && map->findVertex(target) > -1){

		if(map->getPath(source, target).size() < 1){
			cout << "Nao existe caminho entre " << source.getID() << " e " << target.getID() << ". \n";
			return;
		}

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

			//cout << "index: " << indexS << " id: " << map->getPath(source, target)[i].getID() << " distance: " << map->getVertexSet()[map->findVertex(map->getPath(source, target)[i])]->getDistance() << "km" << endl;					//if DijkstraShortestPath
			//cout << "index: " << indexS << " id: " << map->getPath(source, target)[i].getID() << " time: " << map->getVertexSet()[map->findVertex(map->getPath(source, target)[i])]->getTime() << "h" << endl;						//if DijkstraFastestPath

			if(indexN > -1){

				//cout << "index next: " << indexN << " id next: " << map->getPath(source, target)[i+1].getID() << endl;

				int idEdge;

				idEdge = map->getVertexSet()[indexS]->getAdj()[map->getVertexSet()[indexS]->findEdgeByID(map->getVertexSet()[indexN]->getIntersection().getID())].getID();

				gv->addEdge(idEdge, map->getPath(source, target)[i].getID(), map->getPath(source, target)[i+1].getID(), EdgeType::DIRECTED); //id edge, id source, id destino, type

			}

			if(i == 0){
				gv->setVertexColor(map->getPath(source, target)[i].getID(), BLUE);
			}
			else if(i == map->getPath(source, target).size()-1)
				gv->setVertexColor(map->getPath(source, target)[i].getID(),GREEN);

			else
				gv->setVertexColor(map->getPath(source, target)[i].getID(), YELLOW);

		}

	}

	gv->rearrange();
}


void loadMap() {

	gv = new GraphViewer(WIDTH, HEIGHT, false);
	gv->setBackground("res/background2.png");
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


void pre_kmp(string toSearch, vector<int> & prefix) {

	int m = toSearch.size();
	prefix[0] = -1;
	int k = -1;
	for (int q = 1; q < m; q++) {
		while (k > -1 && toSearch[k + 1] != toSearch[q])
			k = prefix[k];
		if (toSearch[k + 1] == toSearch[q])
			k = k + 1;
		prefix[q] = k;
	}
}

int kmp_matcher(string text, string toSearch) {

	int num = 0;
	int m = toSearch.size();
	vector<int> prefix(m);

	pre_kmp(toSearch, prefix);

	int size = text.size();

	int k = -1;
	for (int i = 0; i < size; i++) {
		while (k > -1 && toSearch[k + 1] != text[i])
			k = prefix[k];
		if (toSearch[k + 1] == text[i])
			k++;
		if (k == m - 1) {
			num++;
			k = prefix[k];
		}
	}
	return num;
}


unsigned editDistance(string pattern, string text) {

	unsigned pl = pattern.length();
	unsigned tl = text.length();

	vector<vector<int> > D(pl + 1, vector<int>(tl + 1));

	//inicializacao
	for(unsigned i=0; i<=pl; i++)
		D[i][0] = i;

	for(unsigned j=0; j<=tl; j++)
		D[0][j] = j;

	//recorrencia
	for(unsigned i=1; i<=pl; i++){
		for(unsigned j=1; j<=tl; j++){

			if(pattern[i] == text[j])
				D[i][j] = D[i-1][j-1];
			else {
				int aux = min( min(D[i-1][j-1], D[i-1][j]), D[i][j-1] );
				D[i][j] = 1 + aux;
			}
		}
	}

	//finalizacao
	return D[pl][tl];
}


Vertex<Intersection> * findVertexByEdge(string name) {

	Vertex<Intersection> *v, *BM;
	vector <Vertex<Intersection>* > vertexs;
	bestMatch.clear();

	int counter;
	int best = 9999;

	vertexs=map->getVertexSet();

	typename vector <Vertex<Intersection>* >::iterator it = vertexs.begin();
	typename vector <Vertex<Intersection>* >::iterator ite = vertexs.end();

	for(;it!=ite;it++)
	{
		v=*it;
		if(v->getAdj().size() > 0){
			string tmpName=v->getAdj()[0].getName();

			//to erase blank spaces
			//stringstream ss;
			//std::string::iterator end_pos = std::remove(tmpName.begin(), tmpName.end(), ' ');
			//tmpName.erase(end_pos, tmpName.end());

			if(tmpName.length() != 0){

				if(kmp_matcher(tmpName, name) != 0 && tmpName.length()==name.length()){
					cout << "found it" << endl;
					return v;
				}

				tmpName=v->getAdj()[0].getName();

				counter = editDistance(name,tmpName);
				if(counter < best){

					best = counter;
					BM = v;
					bestMatch.push_back(tmpName);
				}
			}
		}
	}

	return BM;
}

void menu() {

	do{
		cout << endl << setw(20) << "Menu Principal" << endl << endl;

		int escolha;

		cout << "1: Usar GPS" << endl;
		cout << "2: Sair" << endl;
		cin >> escolha;

		switch(escolha){

		case 1: loadMap();
		cout << endl << "Mapa carregado!" << endl;
		GPSMenu();
		break;

		case 2: gv->closeWindow();
				cout << setw(25) << "GPS: CAL P2 15/16" << endl << setw(15) << "FIM" << endl;
				running = false;

		break;

		default: cout << "Escolha uma opcao valida.\n"; break;
		}

	}while(running);

	return;
}


void GPSMenu(){

	string origem, destino;
	int escolha;

	cout << endl;

	cout << "1: A-Star" << endl;
	cout << "2: Dijkstra" << endl;
	cout << "3: Voltar Menu Principal" << endl;
	cin >> escolha;

	switch (escolha)
	{
	case 1:
		algorithm = 1;
		planTravelMenu();
		break;

	case 2:
		algorithm = 2;
		planTravelMenu();
		break;

	case 3:
		gv->closeWindow();
		menu();
		break;

	default:
		cout << "Escolha uma opcao valida.\n"; GPSMenu();	break;
	}

}


void planTravelMenu(){
	string origem, destino;
	unsigned origemID, destinoID;

	int inp;
	char input;

	cout << endl << "Ponto de Origem: " << endl;	//Largo da Paz
	cin.ignore();
	getline(cin, origem);

	Vertex<Intersection> *src, *dst;

	src = findVertexByEdge(origem);
	origemID = src->getIntersection().getID();

	if(src->getAdj()[0].getName().compare(origem) == 0)
		cout << "Found Road" << endl;
	else{
		do{
			cout << "Quis dizer " << src->getAdj()[0].getName() << " ? (S/N)" << endl;
			cin >> input;
			if(input == 'S' || input == 's')
				break;

			for(unsigned i=0; i<bestMatch.size(); i++){
				cout << "Quis dizer " << bestMatch[i] << " ? (S/N)" << endl;
				cin >> input;
				if(input == 'S' || input == 's')
					break;
			}

		}while(input != 'S' || input != 's');

		origem = src->getAdj()[0].getName();
	}

	cout << endl << "Ponto de Destino: " << endl;	//Rua da Firmeza
	cin.ignore();
	getline(cin, destino);

	dst = findVertexByEdge(destino);
	destinoID = dst->getIntersection().getID();

	if(dst->getAdj()[0].getName().compare(destino) == 0)
		cout << "Found Road" << endl;
	else{
		do{
			cout << "Quis dizer " << dst->getAdj()[0].getName() << " ? (S/N)" << endl;
			cin >> input;
			if(input == 'S' || input == 's')
				break;

			for(unsigned i=0; i<bestMatch.size(); i++){
				cout << "Quis dizer " << bestMatch[i] << " ? (S/N)" << endl;
				cin >> input;
				if(input == 'S' || input == 's')
					break;
			}

		}while(input != 'S' || input != 's');

		destino = dst->getAdj()[0].getName();
	}

	clock_t t;
	if(algorithm == 1){

		t = clock();
		map->aStar(map->getVertexSet()[map->getVertexByID(origemID)]->getIntersection(), map->getVertexSet()[map->getVertexByID(destinoID)]->getIntersection(),1);
		t = clock() - t;

	}
	else{

		t = clock();
		map->DijkstraShortestPath(map->getVertexSet()[map->getVertexByID(origemID)]->getIntersection());
		t = clock() - t;

	}

	drawPathGV(map->getVertexSet()[map->getVertexByID(origemID)]->getIntersection(), map->getVertexSet()[map->getVertexByID(destinoID)]->getIntersection());
	cout << "Mapa desenhado!" << endl;

	float r = (float)t / CLOCKS_PER_SEC;

	cout << " Tempo Algoritmo: " << setprecision(10) << r << endl << fixed;

	cout << endl << "1: Voltar Menu Principal" << endl;
	cin >> inp;

	if(inp == 1){
		gv->closeWindow();
		menu();
	}

}


void addInterestPointsMenu(){ //funcao a chamar no menu para adicionar PI's pi's so ficam de cor diferente

	if (map->getNumVertex() == 0){

		cout << "Graph is empty " << endl;
		return;
	}
	int ind;

	bool add = true;

	while(add){

		cout << "ID do vertice a acrescentar um ponto de interesse(-1 to exit): ";
		cin >> ind;

		if(ind == -1){
			add = false;
			break;
		}

		if(map->getVertexByID(ind) == -1)
			cout << "Vertice nao encontrado" << endl;
		else{
			map->getVertexSet()[ind]->getIntersection().setIP(true);
			cout << "PI adicionado!" << endl;
		}

	}
	gv->rearrange();

}


int testEff(){

	unsigned sample_size = 10000;
	unsigned rdm1, rdm2;

	ofstream teste;
	teste.open("teste.csv");

	srand (time(NULL));

	for(unsigned i=0; i<sample_size; i++){
		rdm1 = rand() % 100;
		rdm2 = rand() % 100;

		if(map->findVertex(map->getVertexSet()[rdm1]->getIntersection()) > -1 && map->findVertex(map->getVertexSet()[rdm2]->getIntersection()) > -1){

			clock_t t;
			t = clock();
			//map->aStar(map->getVertexSet()[rdm1]->getIntersection(), map->getVertexSet()[rdm2]->getIntersection(), true);
			//map->DijkstraShortestPath(map->getVertexSet()[rdm1]->getIntersection());
			t = clock() - t;

			float r = (float)t / CLOCKS_PER_SEC;

			cout << "TEMPO: " << setprecision(10) << r << endl;
			cout << fixed;

			teste << r << endl;
		}
	}

	teste.close();

	return 0;
}
