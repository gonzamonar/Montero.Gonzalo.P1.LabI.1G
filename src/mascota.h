/*
 * mascota.h
 *
 *  Created on: May 13, 2022
 *      Author: GM
 */

#ifndef MASCOTA_H_
#define MASCOTA_H_

	typedef struct{
		int id;
		char nombre[20];
		int idTipo;
		int idColor;
		int edad;
		char vacunado; //s o n
		int idCliente;
		int isEmpty;
	}eMascota;

#endif /* MASCOTA_H_ */

#include "lib_io.h"
#include "tipo.h"
#include "color.h"
#include "cliente.h"

	int initMascotas(eMascota* array, int len);
	int harcodeMascotas(eMascota* array, int len, int* nextId, int* qMascotas);
	int listarMascotas(eMascota* array, int tam, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores, eCliente* clientes, int tam_clientes);
	void menuCreacionMascota(int* flag, int id, char nombre[], char descripcionTipo[], char descripcionColor[], int edad, char vacunado, char cliente[]);
	void crearMascota(eMascota* array, int tam, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores, eCliente* clientes, int tam_clientes, int* pNextId, int* qMascotas, int* pNextCliente);
	int agregarMascota(eMascota* array, int len, int id, char nombre[], int idTipo, int idColor, int edad, char vacunado, int idCliente);
	int getFreeSpace_Mascota(eMascota* array, int len, int* pIndex);
	void bajaMascota(eMascota* array, int tam,  eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores, eCliente* clientes, int tam_clientes, int* pNextId, int* qMascotas);
	void mostrarFichaMascota(eMascota mascota, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores);
	int getIdMascota(int* id, int* index, eMascota* mascotas, int len, int lastId, char* requestMsg, char* errorMsg);
	int buscarMascotaPorId(eMascota* list, int len, int id);
	void modificarMascota(eMascota* array, int tam, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores, eCliente* clientes, int tam_clientes, int* pNextId);
	int seleccionarMascota(eMascota* mascotas, int tam, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores, int* id);
	int ordenarMascotasTipoNombre(eMascota* array, int tam);
