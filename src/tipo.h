/*
 * tipo.h
 *
 *  Created on: May 13, 2022
 *      Author: GM
 */

#ifndef TIPO_H_
#define TIPO_H_

	typedef struct{
		int id;		//comienza en 1000
		char descripcion[20];
		int isEmpty;
	}eTipo;

#endif /* TIPO_H_ */


	int initTipos(eTipo* array, int len);
	int harcodeTipos(eTipo* array, int size);
	int listarTipos(eTipo* array, int size);
	int cargarDescripcionTipo(char* descripcion, int idTipo, eTipo* tipos, int tam);
	int seleccionarTipo(eTipo* tipos, int tam, int* id);

