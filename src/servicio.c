/*
 * servicio.c
 *
 *  Created on: May 13, 2022
 *      Author: GM
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "servicio.h"
#include "lib_io.h"

#define HARDCODE_TAM 3

int initServicios(eServicio* array, int len){
	int outcome = 0;
	if(array != NULL && len > 0){
		outcome = 1;
		for(int i=0; i<len; i++){
			array[i].isEmpty = 1;
		}
	}
	return outcome;
}

int harcodeServicios(eServicio* array, int size){
	int outcome = 0;
	int id = 20000;
	eServicio listaServicios[HARDCODE_TAM] =
			{{0, "Corte", 450, 0},
			{0, "Desparasitado", 800, 0},
			{0, "Castrado", 600, 0}};

	if(array != NULL && size>0){
		outcome = 1;
		for(int i=0; i<HARDCODE_TAM; i++, id++){
			listaServicios[i].id = id;
			array[i] = listaServicios[i];
		}
	}
	return outcome;
}


int listarServicios(eServicio* array, int size){
	int outcome = 0;
	if(array != NULL && size>0){
		outcome = 1;
		system("cls");
		printf("\n\n");
		printf(" +------------------------------------------------------------------------------------------------------+\n");
		printf(" |-----------------------------------  *** LISTADO DE SERVICIOS *** ------------------------------------|\n");
		printf(" |------------------------------------------------------------------------------------------------------|\n");
		printf(" |         %5s | %-25s         | %-25s                        |\n", "ID ", "Descripción       ", "Precio");
		printf(" +------------------------------------------------------------------------------------------------------+\n");
		for(int i=0;i<size;i++){
			if(!array[i].isEmpty){
				printf(" |         %5d | %-25s         | $ %-10.2f                                     |\n", array[i].id, array[i].descripcion, array[i].precio);
			}
		}
		printf(" +------------------------------------------------------------------------------------------------------+\n");
	}
	return outcome;
}

int seleccionarServicio(eServicio* servicios, int tam, int* id){
		int outcome = 0;
		int choice;
		int index[tam];
		int max = 0;
		if(servicios != NULL && tam > 0 && id != NULL){
			printf("\n\n    ----------------------------------  * SERVICIOS DISPONIBLES *  -----------------------------------\n");
			printf("    --------------------------------------------------------------------------------------------------\n");
			for(int i=0; i<tam; i++){
				if(!servicios[i].isEmpty){
					printf("       %d. %-25s /  $ %.2f\n", i+1, servicios[i].descripcion, servicios[i].precio);
					index[max] = i;
					max++;
				}
			}
			printf("    --------------------------------------------------------------------------------------------------\n");
			if(getInteger(&choice, "\n    Seleccione un servicio: ", "\n  Opción inválida. ", 1, max, 3)){
				outcome = 1;
				*id = servicios[index[choice-1]].id;
			}
		}
		return outcome;
	}
