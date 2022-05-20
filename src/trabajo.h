/*
 * trabajo.h
 *
 *  Created on: May 13, 2022
 *      Author: GM
 */


#ifndef TRABAJO_H_
#define TRABAJO_H_

#include "mascota.h"
#include "servicio.h"
#include "tipo.h"
#include "fecha.h"

	typedef struct{
		int id; //autoincremental
		int idMascota;
		int idServicio;
		eFecha fecha;
		int isEmpty;
	}eTrabajo;

#endif /* TRABAJO_H_ */


	int initTrabajos(eTrabajo* array, int len);
	int harcodeTrabajos(eTrabajo* array, int len, int* nextId, int* qTrabajos);
	int listarTrabajos(eTrabajo* array, int tam, eMascota* mascotas, int tam_mascotas, eServicio* servicios, int tam_servicios, eTipo* tipos, int tam_tipos);
	int obtenerIndexMascota(eMascota* mascotas, int tam_mascotas, int idMascota);
	int obtenerIndexServicio(eServicio* servicios, int tam_servicios, int idServicio);
	void menuAltaTrabajos(int* flag, int id, int idMascota, int idServicio, eMascota* mascotas, int tam_mascotas, eServicio* servicios, int tam_servicios, eTipo* tipos, int tam_tipos, eFecha fecha);
	int getFreeSpace_Trabajo(eTrabajo* array, int len, int* pIndex);
	int agregarTrabajo(eTrabajo* array, int len, int id, int idMascota, int idServicio, eFecha fecha);
	void crearTrabajo(eTrabajo* trabajos, int tam, eMascota* mascotas, int tam_mascotas, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores,
						eServicio* servicios, int tam_servicios, int* pNextId, int* qTrabajos);

