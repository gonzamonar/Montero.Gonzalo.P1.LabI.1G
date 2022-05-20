/*
 * color.h
 *
 *  Created on: May 13, 2022
 *      Author: GM
 */

#ifndef COLOR_H_
#define COLOR_H_

	typedef struct{
		int id;		//comienza en 5000
		char nombreColor[20];
		int isEmpty;
	}eColor;

#endif /* COLOR_H_ */


	int initColores(eColor* array, int len);
	int harcodeColores(eColor* array, int size);
	int listarColores(eColor* array, int size);
	int cargarDescripcionColor(char* descripcion, int idColor, eColor* colores, int tam);
	int seleccionarColor(eColor* colores, int tam, int* id);


