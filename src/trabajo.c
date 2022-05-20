/*
 * trabajo.c
 *
 *  Created on: May 13, 2022
 *      Author: GM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fecha.h"
#include "lib_io.h"
#include "trabajo.h"
#include "mascota.h"
#include "servicio.h"

//define block Servicios
#define CORTE 20000
#define DESPARASITADO 20001
#define CASTRADO 20002

#define HARDCODE_TAM 15

int initTrabajos(eTrabajo* array, int len){
	int outcome = 0;
	if(array != NULL && len > 0){
		outcome = 1;
		for(int i=0; i<len; i++){
			array[i].isEmpty = 1;
		}
	}
	return outcome;
}


int harcodeTrabajos(eTrabajo* array, int len, int* nextId, int* qTrabajos){
	int outcome = 0;
	int id = *nextId;
	eTrabajo listaTrabajos[HARDCODE_TAM] =
			{{0, 5, CASTRADO, 		{28,6,2020}, 0},
			 {0, 2, DESPARASITADO, 	{1,7,2020}, 0},
			 {0, 9, DESPARASITADO, 	{8,8,2020}, 0},
			 {0, 5, CORTE, 			{8,8,2020}, 0},
			 {0, 8, CORTE, 			{4,11,2020}, 0},
			 {0, 4, DESPARASITADO, 	{1,10,2021}, 0},
			 {0, 7, CORTE, 			{4,11,2021}, 0},
			 {0, 2, CORTE, 			{9,12,2021}, 0},
			 {0, 1, CASTRADO, 		{23,12,2021}, 0},
			 {0, 6, CORTE, 			{1,2,2022}, 0},
			 {0, 9, CORTE, 			{3,2,2022}, 0},
		  	 {0, 3, DESPARASITADO,	{15,4,2022}, 0},
			 {0, 3, CASTRADO, 		{27,4,2022}, 0},
			 {0, 10, DESPARASITADO, {14,7,2022}, 0},
			 {0, 7, CASTRADO, 		{17,9,2022}, 0}};

	if(array != NULL && len>0){
		outcome = 1;
		for(int i=0; i<HARDCODE_TAM; i++, id++){
			listaTrabajos[i].id = id;
			array[i] = listaTrabajos[i];
			*nextId += 1;
			*qTrabajos += 1;
		}
	}
	return outcome;
}



int listarTrabajos(eTrabajo* array, int tam, eMascota* mascotas, int tam_mascotas, eServicio* servicios, int tam_servicios, eTipo* tipos, int tam_tipos){
	int outcome = 0;
	int indexMascota;
	int indexServicio;
	char descripcionMascota[20];

	if(array!=NULL && tam>0 && mascotas!=NULL && tam_mascotas>0 && servicios!=NULL && tam_servicios>0 && tipos!=NULL && tam_tipos>0){
		outcome = 1;
		system("cls");
		printf("\n\n");
		printf(" +------------------------------------------------------------------------------------------------------+\n");
		printf(" |-----------------------------------  *** LISTADO DE TRABAJOS ***  ------------------------------------|\n");
		printf(" |------------------------------------------------------------------------------------------------------|\n");
		printf("      ID |                   MASCOTA                      |           SERVICIO           |   FECHA  \n");
		printf("         |    id              nombre                 tipo |    servicio           precio | dd/mm/aaaa\n");
		printf(" +------------------------------------------------------------------------------------------------------+\n");
		for(int i=0;i<tam;i++){
			if(!array[i].isEmpty){
				indexMascota = obtenerIndexMascota(mascotas, tam_mascotas, array[i].idMascota);
				indexServicio = obtenerIndexServicio(servicios, tam_servicios, array[i].idServicio);
				cargarDescripcionTipo(descripcionMascota, mascotas[indexMascota].idTipo, tipos, tam_tipos);
				printf("  %6d | %4d %20s %20s |  %-20s %5.2f | %02d/%02d/%4d \n", array[i].id, mascotas[indexMascota].id, mascotas[indexMascota].nombre, descripcionMascota,
							servicios[indexServicio].descripcion, servicios[indexServicio].precio, array[i].fecha.dia, array[i].fecha.mes, array[i].fecha.anio);
			}
		}
		printf(" +------------------------------------------------------------------------------------------------------+\n");
	}
	return outcome;
}



int obtenerIndexMascota(eMascota* mascotas, int tam_mascotas, int idMascota){
	int index = -1;
	if(mascotas != NULL && tam_mascotas>0){
		for(int i=0; i<tam_mascotas; i++){
			if(!mascotas[i].isEmpty && mascotas[i].id == idMascota){
				index = i;
				break;
			}
		}
	}
	return index;
}


int obtenerIndexServicio(eServicio* servicios, int tam_servicios, int idServicio){
	int outcome = -1;
	if(servicios != NULL && tam_servicios>0){
		for(int i=0; i<tam_servicios; i++){
			if(!servicios[i].isEmpty && servicios[i].id == idServicio){
				outcome = i;
				break;
			}
		}
	}
	return outcome;
}



void menuAltaTrabajos(int* flag, int id, int idMascota, int idServicio, eMascota* mascotas, int tam_mascotas, eServicio* servicios, int tam_servicios, eTipo* tipos, int tam_tipos, eFecha fecha){
	system("cls");

	printf("\n\n");
	printf(" +------------------------------------------------------------------------------------------------------+\n");
	printf(" |----------------------------------  *** ALTA DEL TRABAJO Nº%02d ***  -----------------------------------|\n", id);
	printf(" |------------------------------------------------------------------------------------------------------|\n");
	printf(" |                                                                                                      |\n");
	if(flag[0]){
		int indexMascota;
		char descripcionMascota[20];
		char displayMascota[128];
		indexMascota = obtenerIndexMascota(mascotas, tam_mascotas, idMascota);
		cargarDescripcionTipo(descripcionMascota, mascotas[indexMascota].idTipo, tipos, tam_tipos);
		sprintf(displayMascota, "ID: %d | Nombre: %s | Tipo: %s.", idMascota, mascotas[indexMascota].nombre, descripcionMascota);
		printf(" |  - MASCOTA:           %-75s    |\n", displayMascota);
	}else{
		printf(" |  - MASCOTA:           %-75s    |\n", "Sin Ingresar");
	}

	if(flag[1]){
		int indexServicio;
		char displayServicio[128];
		indexServicio = obtenerIndexServicio(servicios, tam_servicios, idServicio);
		sprintf(displayServicio, "ID: %d, Descripción: %s, Precio: $ %.2f.", idServicio, servicios[indexServicio].descripcion, servicios[indexServicio].precio);
		printf(" |  - SERVICIO:          %-75s    |\n", displayServicio);
	}else{
		printf(" |  - SERVICIO:          %-75s    |\n", "Sin Ingresar");
	}
	if(flag[2]){
		printf(" |  - FECHA:             %02d/%02d/%4d                                                                     |\n", fecha.dia, fecha.mes, fecha.anio);
	}else{
		printf(" |  - FECHA:             %-20s                                                           |\n", "Sin Ingresar");
	}
	printf(" |                                                                                                      |\n");
	printf(" |------------------------------------------------------------------------------------------------------|\n");
	printf(" +------------------------------------------------------------------------------------------------------+\n");
}



void crearTrabajo(eTrabajo* trabajos, int tam, eMascota* mascotas, int tam_mascotas, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores,
					eServicio* servicios, int tam_servicios, int* pNextId, int* qTrabajos){
	int stage = 1;
	int flags[3] = {0,0,0}; //Flags: mascota, servicio, fecha
	int idMascota;
	int idServicio;
	eFecha fecha;
	char confirm;

	do{
		fflush(stdin);
		menuAltaTrabajos(flags, *pNextId, idMascota, idServicio, mascotas, tam_mascotas, servicios, tam_servicios, tipos, tam_tipos, fecha);
		switch (stage){
			case 1:	//seleccionar mascota
					if(seleccionarMascota(mascotas, tam_mascotas, tipos, tam_tipos, colores, tam_colores, &idMascota)){
						flags[0] = 1;
						stage++;
					}else{
						printf("\n  Intentos de selección de mascota agotados. El proceso de alta ha sido cancelado.");
						stage = 5;
					}
					break;

			case 2:	//seleccionar servicio
					if(seleccionarServicio(servicios, tam_servicios, &idServicio)){
						flags[1] = 1;
						stage++;
					}else{
						printf("\n  Intentos de selección de servicio agotados. El proceso de alta ha sido cancelado.");
						stage = 5;
					}
					break;

			case 3:	//ingresar fecha
					if(getDate(&fecha, "\n  Ingrese la fecha del trabajo (dd/mm/aaaa): ", "  Error, ingrese una fecha válida. ", 3)){
						flags[2] = 1;
						stage++;
					}else{
						printf("\n  Intentos de carga de fecha agotados. El proceso de alta ha sido cancelado.");
						stage = 5;
					}
					break;

			case 4:	//solicitar confirmación -> agregar / cancelar
					getConfirm(&confirm, "\n  ¿Desea confirmar el alta en el sistema? (S/N): ", "  Error, ingrese una respuesta válida. ", 3);
					if(confirm == 's'){
						agregarTrabajo(trabajos, tam, *pNextId, idMascota, idServicio, fecha);
						*pNextId += 1;
						*qTrabajos += 1;
						printf("\n  Trabajo cargado correctamente.");
					}else{
						printf("\n  La carga ha sido cancelada.");
					}
					stage++;
					break;
		}
	}while(stage != 5);
}


int agregarTrabajo(eTrabajo* array, int len, int id, int idMascota, int idServicio, eFecha fecha){
    int outcome = 0;
    int index;
    eTrabajo buffer;
    if(array != NULL && len>0){
    	if(getFreeSpace_Trabajo(array, len, &index)){
    		outcome = 1;
    		buffer.id = id;
    		buffer.idMascota = idMascota;
    		buffer.idServicio = idServicio;
    		buffer.fecha = fecha;
    		buffer.isEmpty = 0;

			array[index] = buffer;
    	}else{
			printf("\n  Espacio insuficiente en el sistema para realizar una nueva alta.");
    	}
    }
    return outcome;
}


int getFreeSpace_Trabajo(eTrabajo* array, int len, int* pIndex){
	int outcome = 0;
	if(array != NULL && len > 0 && pIndex != NULL){
		for(int i=0;i<len;i++){
			if(array[i].isEmpty){
				outcome = 1;
				*pIndex = i;
				break;
			}
		}
	}
	return outcome;
}


