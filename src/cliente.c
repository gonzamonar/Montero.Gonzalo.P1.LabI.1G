/*
 * cliente.c
 *
 *  Created on: May 20, 2022
 *      Author: GM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "lib_io.h"
#include "lib_ui.h"

#define HARCODE_CLIENTES 10

int initClientes(eCliente* array, int len){
	int outcome = 0;
	if(array != NULL && len > 0){
		outcome = 1;
		for(int i=0; i<len; i++){
			array[i].isEmpty = 1;
		}
	}
	return outcome;
}


int harcodeClientes(eCliente* array, int size, int* nextId){
	int outcome = 0;
	int id = *nextId;
	eCliente listaClientes[HARCODE_CLIENTES] =
			{{0, "Victoria", 'f', 0},
			{0, "Freya", 'f', 0},
			{0, "Beren", 'm', 0},
			{0, "Osiris", 'm', 0},
			{0, "Brunilda", 'f', 0},
			{0, "Alfredo", 'm', 0},
			{0, "Paquita", 'f', 0},
			{0, "Mordecai", 'm', 0},
			{0, "Edgar", 'm', 0},
			{0, "Atenas", 'f', 0}};

	if(array != NULL && size>0){
		outcome = 1;
		for(int i=0; i<HARCODE_CLIENTES; i++, id++){
			listaClientes[i].id = id;
			array[i] = listaClientes[i];
			*nextId += 1;
		}
	}
	return outcome;
}


int cargarDescripcionCliente(char* descripcion, int idCliente, eCliente* clientes, int tam){
	int outcome = 0;
	if(descripcion != NULL && idCliente>=2000 && clientes != NULL && tam>0){
		for(int i=0; i<tam; i++){
			if(clientes[i].id == idCliente){
				outcome = 1;
				strcpy(descripcion, clientes[i].nombre);
				break;
			}
		}
	}
	return outcome;
}


int seleccionarCliente(eCliente* clientes, int tam, int* id){
	int outcome = 0;
	int choice;
	int index[tam];
	int max = 0;
	if(clientes != NULL && tam > 0 && id != NULL){
		printf("\n\n    ----------------------------------  * CLIENTES DISPONIBLES *  ------------------------------------\n");
		printf("    --------------------------------------------------------------------------------------------------\n");
		for(int i=0; i<tam; i++){
			if(!clientes[i].isEmpty){
				printf("       %d. %-25s\n", i+1, clientes[i].nombre);
				index[max] = i;
				max++;
			}
		}
		printf("    --------------------------------------------------------------------------------------------------\n");
		if(getInteger(&choice, "\n    Seleccione un cliente: ", "\n  Opción inválida. ", 1, max, 3)){
			outcome = 1;
			*id = clientes[index[choice-1]].id;
		}
	}
	return outcome;
}


int obtenerIndexCliente(eCliente* clientes, int tam_clientes, int idCliente){
	int index = -1;
	if(clientes != NULL && tam_clientes>0){
		for(int i=0; i<tam_clientes; i++){
			if(!clientes[i].isEmpty && clientes[i].id == idCliente){
				index = i;
				break;
			}
		}
	}
	return index;
}


int agregarCliente(eCliente* array, int tam, int id, char nombre[], char sexo){
    int outcome = 0;
    int index;
    eCliente buffer;
    if(array != NULL && tam>0){
    	if(getFreeSpace_Clientes(array, tam, &index)){
    		outcome = 1;
    		buffer.id = id;
    		strcpy(buffer.nombre, nombre);
    		buffer.sexo = sexo;
    		buffer.isEmpty = 0;

			array[index] = buffer;
    	}else{
			printf("\n  Espacio insuficiente en el sistema para realizar una nueva alta.");
    	}
    }
    return outcome;
}


int getFreeSpace_Clientes(eCliente* array, int tam, int* pIndex){
	int outcome = 0;
	if(array != NULL && tam > 0 && pIndex != NULL){
		for(int i=0;i<tam;i++){
			if(array[i].isEmpty){
				outcome = 1;
				*pIndex = i;
				break;
			}
		}
	}
	return outcome;
}
