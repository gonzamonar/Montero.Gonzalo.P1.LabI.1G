/*
 * tipo.c
 *
 *  Created on: May 13, 2022
 *      Author: GM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipo.h"
#include "lib_io.h"

#define HARDCODE_TAM 5

int initTipos(eTipo* array, int len){
	int outcome = 0;
	if(array != NULL && len > 0){
		outcome = 1;
		for(int i=0; i<len; i++){
			array[i].isEmpty = 1;
		}
	}
	return outcome;
}

int harcodeTipos(eTipo* array, int size){
	int outcome = 0;
	int id = 1000;
	eTipo listaTipos[HARDCODE_TAM] =
			{{0, "Ave", 0},
			{0, "Perro", 0},
			{0, "Roedor", 0},
			{0, "Gato", 0},
			{0, "Pez", 0}};

	if(array != NULL && size>0){
		outcome = 1;
		for(int i=0; i<HARDCODE_TAM; i++, id++){
			listaTipos[i].id = id;
			array[i] = listaTipos[i];
		}
	}
	return outcome;
}


int listarTipos(eTipo* array, int size){
	int outcome = 0;
	if(array != NULL && size>0){
		outcome = 1;
		system("cls");
		printf("\n\n");
		printf(" +------------------------------------------------------------------------------------------------------+\n");
		printf(" |-------------------------------------  *** LISTADO DE TIPOS ***  -------------------------------------|\n");
		printf(" |------------------------------------------------------------------------------------------------------|\n");
		printf(" |         %5s | %-25s                                                            |\n", "ID ", " Descripción");
		printf(" +------------------------------------------------------------------------------------------------------+\n");
		for(int i=0;i<size;i++){
			if(!array[i].isEmpty){
				printf(" |         %5d | %-25s                                                            |\n", array[i].id, array[i].descripcion);
			}
		}
		printf(" +------------------------------------------------------------------------------------------------------+\n");
	}
	return outcome;
}



int cargarDescripcionTipo(char* descripcion, int idTipo, eTipo* tipos, int tam){
	int outcome = 0;
	if(descripcion != NULL && idTipo>=1000 && tipos != NULL && tam>0){
		for(int i=0; i<tam; i++){
			if(tipos[i].id == idTipo){
				outcome = 1;
				strcpy(descripcion, tipos[i].descripcion);
				break;
			}
		}
	}
	return outcome;
}


int seleccionarTipo(eTipo* tipos, int tam, int* id){
	int outcome = 0;
	int choice;
	int index[tam];
	int max = 0;
	if(tipos != NULL && tam > 0 && id != NULL){
		printf("\n\n    ------------------------------------  * TIPOS DISPONIBLES *  -------------------------------------\n");
		printf("    --------------------------------------------------------------------------------------------------\n");
		for(int i=0; i<tam; i++){
			if(!tipos[i].isEmpty){
				printf("       %d. %-25s\n", i+1, tipos[i].descripcion);
				index[max] = i;
				max++;
			}
		}
		printf("    --------------------------------------------------------------------------------------------------\n");
		if(getInteger(&choice, "\n    Seleccione un tipo de mascota: ", "\n  Opción inválida. ", 1, max, 3)){
			outcome = 1;
			*id = tipos[index[choice-1]].id;
		}
	}
	return outcome;
}



