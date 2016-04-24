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
#include "graphviewer.h"
#include "Intersection.h"
#include "Graph.h"
#include "GraphicData.h"

#define DEFAULT_COLOR "black"

#define PI 3.14159265
#define WIDTH 1280
#define HEIGHT 1080





/*
 * Le os dados de Data.txt, cria o graph, todos os seus vertices e arestas.
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
 * Converte Latitudes e Longitudes extraidas de Data.txt para
 * posicoes na janela do graphviewer usando a formula:
 *
 *
 * ADICIONAR FORMULA AQUI
 *
 *
 */


vector<float> convertGeoCordToPixel(float lon, float lat);


/*
 *
 * desenha
 *
 *
 */

void drawPathGV(Intersection source, Intersection target);


void loadMap();

int getEdgeID(int a, int b);

void addInterestPointsMenu();


void menu();


