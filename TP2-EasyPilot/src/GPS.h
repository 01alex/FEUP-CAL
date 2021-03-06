#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <string>
#include <math.h>
#include <iomanip>
#include <time.h>
#include <algorithm>
#include "graphviewer.h"
#include "Intersection.h"
#include "Graph.h"

#define DEFAULT_COLOR "black"

#define PI 3.14159265
#define WIDTH 781
#define HEIGHT 523

#define longitudeMin -8.6275
#define longitudeMax -8.5939

#define latitudeMin 41.1398
#define latitudeMax 41.1568



/*
 * Ler os dados de Data.txt, cria o graph, todos os seus vertices e arestas.
 *
 *
 *	O Data.txt contem a informacao da seguinte forma:
 *
 *  id;nome;source;target;km;kmh;x1;y1;x2;y2
 *
 */

void readDataBase(string path);


/*
 *
 * Converter Latitudes e Longitudes extraidas de Data.txt para
 * posicoes na janela do graphviewer
 *
 *
 */

vector<float> convertGeoCordToPixel(float lon, float lat);


/*
 *
 * Desenhar caminho
 *
 *
 */

void drawPathGV(Intersection source, Intersection target);


/*
 *
 * Carregar Dados
 *
 */

void loadMap();


/*
 *
 * Pesquisa Exacta Strings (baseado 13.strings1.pdf)
 *
 */

void pre_kmp(string toSearch, vector<int> & prefix);
int kmp_matcher(string text, string toSearch);


/*
 *
 * Pesquisa Aproximada Strings	(baseado 13.strings1.pdf)
 *
 */

unsigned editDistance(string pattern, string text);


/*
 *
 * Corresponder nomes de arestas a vertices
 *
 */

Vertex<Intersection> * findVertexByEdge(string name);


/*
 *
 * Interface
 *
 */

void menu();

void GPSMenu();

void planTravelMenu();

void addInterestPointsMenu();


/*
 *
 * Teste Algoritmos
 *
 */

int testEff();
