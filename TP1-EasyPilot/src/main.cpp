#include "GPS.h"

int main(){

	string dbpath = "res/DataFull.txt";

	readDataBase(dbpath);

	menu();

	//testEff();

	getchar();

	return 0;
}
