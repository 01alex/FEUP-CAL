#include "GPS.h"

Graph<Intersection> *map;
GraphViewer *gv;

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

Vertex<Intersection> findVertexByEdge(string name) {

	Vertex<Intersection> *v;
	Vertex<Intersection> *BM;
	vector <Vertex<Intersection>* > vertexs;

	int counter;
	int BestMatch = 9999;

	vertexs=map->getVertexSet();

	typename vector <Vertex<Intersection>* >::iterator it = vertexs.begin();
	typename vector <Vertex<Intersection>* >::iterator ite = vertexs.end();

	for(;it!=ite;it++)
	{
		v=*it;
		if(v->getAdj().size() > 0){
			string tmpName=v->getAdj()[0].getName();
			if(kmp_matcher(tmpName,name) !=0 && tmpName.size()==name.size()){
				cout << "found it" << endl;
				return *v;

			}
			tmpName=v->getAdj()[0].getName();
			counter = editDistance(tmpName,name);
			if(counter < BestMatch)
			{
				BestMatch = counter;
				BM = v;
			}


		}
	}

	cout << "Did you mean " << BM->getAdj()[0].getName() << " ?" <<endl;

	//return vector<Intersection>();
}


void pesquisaStringMenu(){
	int escolha;
	string nRua;
	vector<string> res;

	cout << endl << "Pesquisa Localidade!" << endl;

	cout << "1: Pesquisa Exata" << endl;
	cout << "2: Pesquisa Aproximada" << endl;

	cin >> escolha;

	if(escolha != 1 && escolha != 2){
		cout << "Escolha uma opcao valida!" << endl;
		pesquisaStringMenu();
	}

	cout << "Nome da rua a pesquisar: " << endl;
	cin.ignore();
	getline(cin, nRua);
	if(escolha == 1){
		findVertexByEdge(nRua);
			}



	if(escolha == 2){
		for(unsigned i=0; i<map->getNumVertex(); i++){
			for(unsigned j=0; j<map->getVertexSet()[i]->getAdj().size(); j++){
				if(editDistance(nRua, map->getVertexSet()[i]->getAdj()[j].getName()) == 0)
					res.push_back(map->getVertexSet()[i]->getAdj()[j].getName());
			}
		}
	}

	for(unsigned k=0; k<res.size(); k++)
		cout << res[k] << endl;

}

void GPSMenu(){

	string origem;
	string destino;
	int escolha;
	int algorithm;
	loadMap();


	cout << endl << "Mapa carregado!" << endl;

	cout << "1: Pesquisa Localidade" << endl;
	cout << "2: A-Star" << endl;
	cout << "3: Dijkstra" << endl;
	cin >> escolha;

	if(escolha != 1 && escolha != 2 && escolha != 3){
		cout << "Escolha uma opcao valida!" << endl;
		GPSMenu();
	}

	if(escolha == 1)
		pesquisaStringMenu();
	else{

		cout << endl << "Vertice de origem: " << endl;
		cin.ignore();
		getline(cin, origem);
		Vertex<Intersection> o = findVertexByEdge(origem);
		int origemNum =o.getIntersection().getID();


		cout << "Vertice de destino: " << endl;
		//cin.ignore();
		getline(cin, destino);
		Vertex<Intersection> d = findVertexByEdge(destino);

		int destinoNum = d.getIntersection().getID();

		gv->closeWindow();

		if(destino == origem) {
			cout << "A rua que pretende ir e invalida: " << endl;
			return;
		}

		clock_t t;
		t = clock();


		if(escolha == 2)
			map->DijkstraShortestPath(map->getVertexSet()[map->getVertexByID(origemNum)]->getIntersection());

		else
			map->aStar(map->getVertexSet()[map->getVertexByID(origemNum)]->getIntersection(), map->getVertexSet()[map->getVertexByID(destinoNum)]->getIntersection(),1);


		//cout << "Algorithm complete" << endl;
		drawPathGV(map->getVertexSet()[map->getVertexByID(origemNum)]->getIntersection(), map->getVertexSet()[map->getVertexByID(destinoNum)]->getIntersection());
		cout << "Mapa desenhado!" << endl;

		t = clock() - t;

		float r = (float)t / CLOCKS_PER_SEC;


		cout << " TEMPO: " << setprecision(10) << r << endl;
		cout << fixed;


		char exit;
		do {
			cout <<endl<< "Enter para continuar (fecha o mapa)" << endl;

			cin.clear();
			cin.ignore();
			exit=getchar();
			//putchar (c);
		} while (exit != '\n');

		gv->closeWindow();

	}


	return;

}


void menu() {
	//system("CLS");

	int escolha;
	bool loop = true;


	cout << endl;

	do{

		cout << setw(20) << "Menu Principal" << endl << endl;

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

		cout << "Voltar ao menu principal (n termina programa)(S/N)? ";
		char inp;
		cin >>inp;

		if(inp =='S')
			loop = true;
		else
			loop = false;


	}while(loop);

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

unsigned editDistance(string name1, string name2) {

	unsigned int l1 = name1.size();
		unsigned int l2 = name2.size();
		vector<vector<int> > D(l1 + 1, vector<int>(l2 + 1));

		for (unsigned int i = 0; i <= l1; i++) {
			D[i][0] = i;
		}

		for (unsigned int j = 0; j <= l2; j++) {
			D[0][j] = j;
		}

		for (unsigned int i = 1; i <= l1; i++) {
			for (unsigned int j = 1; j <= l2; j++) {
				if (name1[i-1] == name2[j-1]) {
					D[i][j] = D[i - 1][j - 1];
				} else {
					D[i][j] = 1
							+ min(min(D[i - 1][j - 1], D[i - 1][j]), D[i][j - 1]);
				}
			}
		}

		return D[l1][l2];
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

