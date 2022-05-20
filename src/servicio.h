/*
 * servicio.h
 *
 *  Created on: May 13, 2022
 *      Author: GM
 */

#ifndef SERVICIO_H_
#define SERVICIO_H_

	typedef struct{
		int id; 	//comienza en 20000
		char descripcion[25];
		float precio;
		int isEmpty;
	}eServicio;

#endif /* SERVICIO_H_ */

	int initServicios(eServicio* array, int len);
	int harcodeServicios(eServicio* array, int size);
	int listarServicios(eServicio* array, int size);
	int seleccionarServicio(eServicio* servicios, int tam, int* id);
