/*
 * GraphicData.h
 *
 *  Created on: Apr 16, 2016
 *      Author: luiscosta
 */

#ifndef TP1_EASYPILOT_SRC_GRAPHICDATA_H_
#define TP1_EASYPILOT_SRC_GRAPHICDATA_H_


class graphicData {
public:
	int id_aresta;
	int id_origem;
	int id_destino;

	graphicData(int a, int b, int c) {
		id_aresta = a;
		id_origem = b;
		id_destino = c;
	}
};


#endif /* TP1_EASYPILOT_SRC_GRAPHICDATA_H_ */
