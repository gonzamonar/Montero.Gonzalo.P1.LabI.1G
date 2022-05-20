/*
 * color.c
 *
 *  Created on: May 13, 2022
 *      Author: GM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "lib_io.h"

#define HARDCODE_TAM 5

int initColores(eColor* array, int len){
	int outcome = 0;
	if(array != NULL && len > 0){
		outcome = 1;
		for(int i=0; i<len; i++){
			array[i].isEmpty = 1;
		}
	}
	return outcome;
}

int harcodeColores(eColor* array, int size){
	int outcome = 0;
	int id = 5000;
	eColor listaColores[HARDCODE_TAM] =
			{{0, "Negro", 0},
			{0, "Blanco", 0},
			{0, "Rojo", 0},
			{0, "Gris", 0},
			{0, "Azul", 0}};

	if(array != NULL && size>0){
		outcome = 1;
		for(int i=0; i<HARDCODE_TAM; i++, id++){
			listaColores[i].id = id;
			array[i] = listaColores[i];
		}
	}
	return outcome;
}


int listarColores(eColor* array, int size){
	int outcome = 0;
	if(array != NULL && size>0){
		outcome = 1;
		system("cls");
		printf("\n\n");
		printf(" +------------------------------------------------------------------------------------------------------+\n");
		printf(" |------------------------------------  *** LISTADO DE COLORES ***  ------------------------------------|\n");
		printf(" |------------------------------------------------------------------------------------------------------|\n");
		printf(" |         %5s | %-25s                                                            |\n", "ID ", " Descripción");
		printf(" +------------------------------------------------------------------------------------------------------+\n");
		for(int i=0;i<size;i++){
			if(!array[i].isEmpty){
				printf(" |         %5d | %-25s                                                            |\n", array[i].id, array[i].nombreColor);
			}
		}
		printf(" +------------------------------------------------------------------------------------------------------+\n");
	}
	return outcome;
}


int cargarDescripcionColor(char* descripcion, int idColor, eColor* colores, int tam){
	int outcome = 0;
	if(descripcion != NULL && idColor>=5000 && colores != NULL && tam>0){
		for(int i=0; i<tam; i++){
			if(colores[i].id == idColor){
				outcome = 1;
				strcpy(descripcion, colores[i].nombreColor);
				break;
			}
		}
	}
	return outcome;
}


int seleccionarColor(eColor* colores, int tam, int* id){
	int outcome = 0;
	int choice;
	int index[tam];
	int max = 0;
	if(colores != NULL && tam > 0 && id != NULL){
		printf("\n\n    -----------------------------------  * COLORES DISPONIBLES *  ------------------------------------\n");
		printf("    --------------------------------------------------------------------------------------------------\n");
		for(int i=0; i<tam; i++){
			if(!colores[i].isEmpty){
				printf("       %d. %-25s\n", i+1, colores[i].nombreColor);
				index[max] = i;
				max++;
			}
		}
		printf("    --------------------------------------------------------------------------------------------------\n\n");
		if(getInteger(&choice, "\n    Seleccione el color de la mascota: ", "\n  Opción inválida. ", 1, max, 3)){
			outcome = 1;
			*id = colores[index[choice-1]].id;
		}
	}
	return outcome;
}

