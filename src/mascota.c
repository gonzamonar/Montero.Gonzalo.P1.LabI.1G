/*
 * mascota.c
 *
 *  Created on: May 13, 2022
 *      Author: GM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib_io.h"
#include "lib_ui.h"
#include "mascota.h"
#include "cliente.h"
#include "tipo.h"
#include "color.h"

//define block Colores
#define NEGRO 5000
#define BLANCO 5001
#define ROJO 5002
#define GRIS 5003
#define AZUL 5004
//define block Tipos
#define AVE 1000
#define PERRO 1001
#define ROEDOR 1002
#define GATO 1003
#define PEZ 1004

#define HARDCODE_TAM 10

int initMascotas(eMascota* array, int len){
	int outcome = 0;
	if(array != NULL && len > 0){
		outcome = 1;
		for(int i=0; i<len; i++){
			array[i].isEmpty = 1;
		}
	}
	return outcome;
}

int harcodeMascotas(eMascota* array, int len, int* nextId, int* qMascotas){
	int outcome = 0;
	int id = *nextId;
	eMascota listaMascotas[HARDCODE_TAM] =
			{{0, "Rintintin", PERRO, NEGRO, 4, 's', 2000, 0},
			{0, "Jerry", ROEDOR, AZUL, 2, 'n', 2001,0},
			{0, "Tweety", AVE, BLANCO, 15, 'n', 2002,0},
			{0, "Tom", GATO, GRIS, 8, 's', 2003,0},
			{0, "Clifford", PERRO, ROJO, 10, 'n', 2004,0},
			{0, "Nemo", PEZ, ROJO, 9, 's', 2005,0},
			{0, "Speedy", ROEDOR, NEGRO, 4, 's', 2006,0},
			{0, "Bloodwing", AVE, ROJO, 2, 'n', 2007,0},
			{0, "Pluton", GATO, NEGRO, 12, 's', 2008,0},
			{0, "Dory", PEZ, AZUL, 4, 's', 2009,0}};

	if(array != NULL && len>0){
		outcome = 1;
		for(int i=0; i<HARDCODE_TAM; i++, id++){
			listaMascotas[i].id = id;
			array[i] = listaMascotas[i];
			*nextId += 1;
			*qMascotas += 1;
		}
	}
	return outcome;
}


int listarMascotas(eMascota* array, int tam, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores, eCliente* clientes, int tam_clientes){
	int outcome = 0;
	char descripcionTipo[20];
	char descripcionColor[20];
	char nombreCliente[20];

	ordenarMascotasTipoNombre(array, tam);

	if(array!=NULL && tam>0 && tipos!=NULL && tam_tipos>0 && colores!=NULL && tam_colores>0){
		outcome = 1;
		system("cls");
		printf("\n\n");
		printf(" +------------------------------------------------------------------------------------------------------+\n");
		printf(" |------------------------------------  *** LISTADO DE MASCOTAS ***  -----------------------------------|\n");
		printf(" |------------------------------------------------------------------------------------------------------|\n");
		printf("   %6s | %20s | %8s | %8s | %5s | %8s | %15s \n", "ID", "Nombre", "Tipo", "Color ", "Edad", "Vacunado", "Dueña/o");
		printf(" +------------------------------------------------------------------------------------------------------+\n");
		for(int i=0;i<tam;i++){
			if(!array[i].isEmpty){
				cargarDescripcionTipo(descripcionTipo, array[i].idTipo, tipos, tam_tipos);
				cargarDescripcionColor(descripcionColor, array[i].idColor, colores, tam_colores);
				cargarDescripcionCliente(nombreCliente, array[i].idCliente, clientes, tam_clientes);
				printf("   %6d | %20s | %8s | %8s | %5d | %8c | %-15s \n", array[i].id, array[i].nombre, descripcionTipo, descripcionColor, array[i].edad, array[i].vacunado, nombreCliente);
			}
		}
		printf(" +------------------------------------------------------------------------------------------------------+\n");
	}
	return outcome;
}


void menuCreacionMascota(int* flag, int id, char nombre[], char descripcionTipo[], char descripcionColor[], int edad, char vacunado, char cliente[]){
	system("cls");
	printf("\n\n");
	printf(" +------------------------------------------------------------------------------------------------------+\n");
	printf(" |-------------------------------------  *** SUBMENÚ DE ALTAS ***  -------------------------------------|\n");
	printf(" |------------------------------------------------------------------------------------------------------|\n");
	printf(" |                                                                                                      |\n");
	printf(" |  - ID: 	                 %-16d                                                       |\n", id);
	if(flag[0]){
		printf(" |  - NOMBRE:                    %-20s                                                   |\n", nombre);
	}else{
		printf(" |  - NOMBRE:                    %-20s                                                   |\n", "Sin Ingresar");
	}

	if(flag[1]){
		printf(" |  - TIPO:                      %-20s                                                   |\n", descripcionTipo);
	}else{
		printf(" |  - TIPO:                      %-20s                                                   |\n", "Sin Ingresar");
	}
	if(flag[2]){
		printf(" |  - COLOR:                     %-20s                                                   |\n", descripcionColor);
	}else{
		printf(" |  - COLOR:                     %-20s                                                   |\n", "Sin Ingresar");
	}
	if(flag[3]){
		printf(" |  - EDAD:                      %-20d                                                   |\n", edad);
	}else{
		printf(" |  - EDAD:                      %-20s                                                   |\n", "Sin Ingresar");
	}
	if(flag[4]){
		printf(" |  - VACUNADO:                  %-20c                                                   |\n", vacunado);
	}else{
		printf(" |  - VACUNADO:                  %-20s                                                   |\n", "Sin Ingresar");
	}
	if(flag[5]){
		printf(" |  - DUEÑA/O:                   %-20s                                                   |\n", cliente);
	}else{
		printf(" |  - DUEÑA/O:                   %-20s                                                   |\n", "Sin Ingresar");
	}
	printf(" |                                                                                                      |\n");
	printf(" |------------------------------------------------------------------------------------------------------|\n");
	printf(" +------------------------------------------------------------------------------------------------------+\n");
}



void crearMascota(eMascota* array, int tam, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores, eCliente* clientes, int tam_clientes, int* pNextId, int* qMascotas, int* pNextCliente){
	int stage = 1;
	int flags[6] = {0,0,0,0,0,0}; //Flags: nombre, idTipo, idColor, edad, vacunado, dueña/o
	int flagCliente = 0;
	int idTipo;
	int idColor;
	int idCliente = *pNextCliente;
	int indexCliente;
	int opcionCliente;
	int edad;
	char vacunado;
	char nombre[20];
	char descripcionTipo[20];
	char descripcionColor[20];
	char nombreCliente[20];
	char sexoCliente;
	char confirm;

	do{
		fflush(stdin);
		menuCreacionMascota(flags, *pNextId, nombre, descripcionTipo, descripcionColor, edad, vacunado, nombreCliente);
		switch (stage){
			case 1:	//ingresar nombre
					if(getProperName(nombre, 20, 20, 2, "\n  Ingrese nombre: ", "\n  Nombre no válido. ", 3, " ")){
						flags[0] = 1;
						stage++;
					}else{
						printf("\n  Intentos de carga de nombre agotados. El proceso de alta ha sido cancelado.");
						stage = 8;
					}
					break;

			case 2:	//seleccionar tipo
					if(seleccionarTipo(tipos, tam_tipos, &idTipo)){
						cargarDescripcionTipo(descripcionTipo, idTipo, tipos, tam_tipos);
						flags[1] = 1;
						stage++;
					}else{
						printf("\n  Intentos de selección de tipo agotados. El proceso de alta ha sido cancelado.");
						stage = 8;
					}
					break;

			case 3:	//seleccionar color
					if(seleccionarColor(colores, tam_colores, &idColor)){
						cargarDescripcionColor(descripcionColor, idColor, colores, tam_colores);
						flags[2] = 1;
						stage++;
					}else{
						printf("\n  Intentos de selección de color agotados. El proceso de alta ha sido cancelado.");
						stage = 8;
					}
					break;

			case 4:	//ingresar edad
					if(getInteger(&edad, "\n  Ingrese la edad en años de la mascota: ", "  Error, ingrese una capacidad válida (0 para menores a 1 año). ", 0, 100, 3)){
						flags[3] = 1;
						stage++;
					}else{
						printf("\n  Intentos de carga de edad agotados. El proceso de alta ha sido cancelado.");
						stage = 8;
					}
					break;

			case 5:	//ingresar vacunación
					if(getConfirm(&vacunado, "\n  ¿La mascota está vacunada? (s/n): ", "  Error, ingrese una respuesta válida. ", 3)){
						flags[4] = 1;
						stage++;
					}else{
						printf("\n  Intentos de carga de vacunación agotados. El proceso de alta ha sido cancelado.");
						stage = 8;
					}
					break;

			case 6:	//elegir cliente
					mostrarMenuClientes(&opcionCliente);
					if(opcionCliente==1){
						if(getProperName(nombreCliente, 20, 20, 2, "\n  Ingrese nombre: ", "\n  Nombre no válido. ", 3, " ")
							&& getSexo(&sexoCliente, "\n  Ingrese sexo del dueño/a (m/f): ", "  Error, ingrese una respuesta válida. ", 3)){
							flags[5] = 1;
							flagCliente = 1;
							stage++;
						}else{
							printf("\n  Intentos de carga de dueña/o agotados. El proceso de alta ha sido cancelado.");
							stage=8;
						}
					}else if(opcionCliente==2){
						if(seleccionarCliente(clientes, tam_clientes, &idCliente)){
							indexCliente = obtenerIndexCliente(clientes, tam_clientes, idCliente);
							strcpy(nombreCliente, clientes[indexCliente].nombre);
							sexoCliente = clientes[indexCliente].sexo;
							flags[5] = 1;
							stage++;
						}else{
							printf("\n  Intentos de selección de dueña/o agotados. El proceso de alta ha sido cancelado.");
							stage=8;
						}
					}
					break;

			case 7:	//solicitar confirmación -> agregar / cancelar
					getConfirm(&confirm, "\n  ¿Desea confirmar el alta en el sistema? (S/N): ", "  Error, ingrese una respuesta válida. ", 3);
					if(confirm == 's'){
						if(flagCliente){
							agregarCliente(clientes, tam_clientes, idCliente, nombreCliente, sexoCliente);
							*pNextCliente += 1;
						}
						agregarMascota(array, tam, *pNextId, nombre, idTipo, idColor, edad, vacunado, idCliente);
						*pNextId += 1;
						*qMascotas += 1;
						printf("\n  Mascota cargada correctamente.");
					}else{
						printf("\n  El alta ha sido cancelada.");
					}
					stage++;
					break;
		}
	}while(stage != 8);
}


int agregarMascota(eMascota* array, int len, int id, char nombre[], int idTipo, int idColor, int edad, char vacunado, int idCliente){
    int outcome = 0;
    int index;
    eMascota buffer;
    if(array != NULL && len>0){
    	if(getFreeSpace_Mascota(array, len, &index)){
    		outcome = 1;
    		buffer.id = id;
    		strcpy(buffer.nombre, nombre);
    		buffer.idTipo = idTipo;
    		buffer.idColor = idColor;
    		buffer.edad = edad;
    		buffer.vacunado = vacunado;
    		buffer.idCliente = idCliente;
    		buffer.isEmpty = 0;

			array[index] = buffer;
    	}else{
			printf("\n  Espacio insuficiente en el sistema para realizar una nueva alta.");
    	}
    }
    return outcome;
}


int getFreeSpace_Mascota(eMascota* array, int len, int* pIndex){
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


void bajaMascota(eMascota* array, int tam,  eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores, eCliente* clientes, int tam_clientes, int* pNextId, int* qMascotas){
	int id;
	int index;
	int lastId = *pNextId-1;
	char confirm;
	char errorMsg[64];
	char confirmMsg[64];
	char requestMsg[] = {"\n  Ingrese el ID de la mascota que desea dar de baja: "};

	sprintf(errorMsg, "  Error, ingrese un id válido (1 a %4d). ", lastId);

	system("cls");
	listarMascotas(array, tam, tipos, tam_tipos, colores, tam_colores, clientes, tam_clientes);
	if(getIdMascota(&id, &index, array, tam, lastId, requestMsg, errorMsg)){
		mostrarFichaMascota(array[index], tipos, tam_tipos, colores, tam_colores);
		sprintf(confirmMsg, "\n  ¿Desea confirmar la baja de la mascota Nº %d? (S/N): ", id);
		printf("\n                            IMPORTANTE: ESTA ACCIÓN NO SE PUEDE DESHACER.\n");
		getConfirm(&confirm, confirmMsg, "  Respuesta inválida. ", 3);
		if(confirm=='s'){
			printf("\n  Baja exitosa.");
			array[index].isEmpty = 1;
			*qMascotas -= 1;
		}else{
			printf("\n  Baja cancelada.");
		}
	}else{
		printf("\n\n  Intentos de carga de id agotados. El proceso de baja ha sido cancelado.");
	}
}


void mostrarFichaMascota(eMascota mascota, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores){
	system("cls");
	char descripcionTipo[20];
	char descripcionColor[20];
	cargarDescripcionTipo(descripcionTipo, mascota.idTipo, tipos, tam_tipos);
	cargarDescripcionColor(descripcionColor, mascota.idColor, colores, tam_colores);
	printf("\n\n");
	printf(" +------------------------------------------------------------------------------------------------------+\n");
	printf(" |----------------------------------  *** FICHA MASCOTA Nº %4d ***  -----------------------------------|\n", mascota.id);
	printf(" |------------------------------------------------------------------------------------------------------|\n");
	printf(" |                                                                                                      |\n");
	printf(" |  - NOMBRE:          %-50s                               |\n", mascota.nombre);
	printf(" |  - TIPO:            %-50s                               |\n", descripcionTipo);
	printf(" |  - COLOR:           %-50s                               |\n", descripcionColor);
	printf(" |  - EDAD:            %-20d                                                             |\n", mascota.edad);
	printf(" |  - VACUNADO:        %-20c                                                             |\n", mascota.vacunado);
	printf(" |                                                                                                      |\n");
	printf(" |------------------------------------------------------------------------------------------------------|\n");
	printf(" +------------------------------------------------------------------------------------------------------+\n");
}


int getIdMascota(int* id, int* index, eMascota* mascotas, int len, int lastId, char* requestMsg, char* errorMsg){
	int outcome = 3;
	int intentos = 3;

	do{
		if(getInteger(id, requestMsg, "", 1, lastId, 1)){
			*index = buscarMascotaPorId(mascotas, len, *id);
			if(*index > -1){
				outcome = 1;
				break;
			}else{
				printf("  El id que ud ingresó no corresponde a una mascota activa.");
			}
		}else{
			printf("%s", errorMsg);
		}
		outcome--;
		intentos--;
		if(intentos>0){
			printf(" (Intentos restantes: %d)\n", intentos);
		}
	}while(intentos>0);
	return outcome;
}


int buscarMascotaPorId(eMascota* list, int len, int id){
	int index = -1;
	if(list != NULL && len > 0){
		for(int i=0; i<len; i++){
			if(list[i].id == id && !list[i].isEmpty){
				index = i;
				break;
			}
		}
	}
	return index;
}



void modificarMascota(eMascota* array, int tam, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores, eCliente* clientes, int tam_clientes, int* pNextId){
	int id;
	int index;
	int option;
	int lastId = *pNextId-1;
	char confirm;
	char reconfirm;
	int idTipo;
	int idColor;
	int edad;
	char vacunado;
	char nombre[20];
	char viejaDescripcionTipo[20];
	char nuevaDescripcionTipo[20];
	char viejaDescripcionColor[20];
	char nuevaDescripcionColor[20];
	char errorMsg[64];
	char requestMsg[] = {"\n  Ingrese el ID de la mascota que desea modificar: "};
	char confirmMsg[256];



	sprintf(errorMsg, "  Error, ingrese un id válido (1 a %4d). ", lastId);

	system("cls");
	listarMascotas(array, tam, tipos, tam_tipos, colores, tam_colores, clientes, tam_clientes);
	if(getIdMascota(&id, &index, array, tam, lastId, requestMsg, errorMsg)){
		do{
			int editFlag = 0;
			fflush(stdin);
			mostrarFichaMascota(array[index], tipos, tam_tipos, colores, tam_colores);
			mostrarMenuModificacion(&option);
			switch(option){
				case 1:	//modificar nombre
						if(getProperName(nombre, 20, 20, 2, "\n  Ingrese nombre: ", "\n  Nombre no válido. ", 3, " ")){
							sprintf(confirmMsg, "\n  ¿Desea confirmar el cambio de nombre de %s a %s? (S/N): ", array[index].nombre, nombre);
							getConfirm(&confirm, confirmMsg, "  Respuesta inválida. ", 3);
							if(confirm=='s'){
								strcpy(array[index].nombre, nombre);
								editFlag = 1;
							}else{
								printf("\n  Modificación cancelada.");
							}
						}else{
							printf("\n  Intentos de carga de nombre agotados. Modificación cancelada.");
						}
						break;

				case 2:	//modificar tipo
						if(seleccionarTipo(tipos, tam_tipos, &idTipo)){
							cargarDescripcionTipo(nuevaDescripcionTipo, idTipo, tipos, tam_tipos);
							cargarDescripcionTipo(viejaDescripcionTipo, array[index].idTipo, tipos, tam_tipos);
							sprintf(confirmMsg, "\n  ¿Desea confirmar el cambio de tipo de %s a %s? (S/N): ", viejaDescripcionTipo, nuevaDescripcionTipo);
							getConfirm(&confirm, confirmMsg, "  Respuesta inválida. ", 3);
							if(confirm=='s'){
								array[index].idTipo = idTipo;
								editFlag = 1;
							}else{
								printf("\n  Modificación cancelada.");
							}
						}else{
							printf("\n  Intentos de selección de tipo agotados. Modificación cancelada.");
						}
						break;

				case 3:	//editar color
						if(seleccionarColor(colores, tam_colores, &idColor)){
							cargarDescripcionColor(viejaDescripcionColor, array[index].idColor, colores, tam_colores);
							cargarDescripcionColor(nuevaDescripcionColor, idColor, colores, tam_colores);
							sprintf(confirmMsg, "\n  ¿Desea confirmar el cambio de color de %s a %s? (S/N): ", viejaDescripcionColor, nuevaDescripcionColor);
							getConfirm(&confirm, confirmMsg, "  Respuesta inválida. ", 3);
							if(confirm=='s'){
								array[index].idColor = idColor;
								editFlag = 1;
							}else{
								printf("\n  Modificación cancelada.");
							}
						}else{
							printf("\n  Intentos de selección de color agotados. Modificación cancelada.");
						}
						break;

				case 4:	//modificar edad
						if(getInteger(&edad, "\n  Ingrese la edad en años de la mascota: ", "  Error, ingrese una capacidad válida (0 para menores a 1 año). ", 0, 100, 3)){
							sprintf(confirmMsg, "\n  ¿Desea confirmar el cambio de edad de %d a %d? (S/N): ", array[index].edad, edad);
							getConfirm(&confirm, confirmMsg, "  Respuesta inválida. ", 3);
							if(confirm=='s'){
								array[index].edad = edad;
								editFlag = 1;
							}else{
								printf("\n  Modificación cancelada.");
							}
						}else{
							printf("\n  Intentos de carga de edad agotados.  Modificación cancelada.");
						}
						break;

				case 5:	//edit flycode
						if(getConfirm(&vacunado, "\n  ¿La mascota está vacunada? (s/n): ", "  Error, ingrese una respuesta válida. ", 3)){
							sprintf(confirmMsg, "\n  ¿Desea confirmar el estado de vacunación de %c a %c? (s/n): ", array[index].vacunado, vacunado);
							getConfirm(&confirm, confirmMsg, "  Respuesta inválida. ", 3);
							if(confirm=='s'){
								array[index].vacunado = vacunado;
								editFlag = 1;
							}else{
								printf("\n  Modificación cancelada.");
							}
						}else{
							printf("\n  Intentos de selección de vuelo agotados. Modificación cancelada.");
						}
						break;
			}
			//new edit or exit
			if(editFlag){
				system("cls");
				mostrarFichaMascota(array[index], tipos, tam_tipos, colores, tam_colores);
				printf("\n  Modificación realizada exitosamente.");
				if(!getConfirm(&reconfirm, "  ¿Desea realizar otra modificación? (S/N): ", "\n  Error, ingrese una respuesta válida. ", 3) || reconfirm == 'n'){
					option = 6;
				}
			}else{
				option = 6;
			}
		}while(option != 6);
	}else{
		printf("\n\n  Intentos de carga de id agotados. El proceso de modificación ha sido cancelado.");
	}
}


int seleccionarMascota(eMascota* mascotas, int tam, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores, int* id){
	int outcome = 0;
	int choice;
	int index[tam];
	int max = 0;
	char descripcionTipo[20];
	char descripcionColor[20];

	if(mascotas != NULL && tam > 0 && id != NULL){
		printf("\n\n    -----------------------------------  * MASCOTAS DISPONIBLES *  ------------------------------------\n");
		printf("    --------------------------------------------------------------------------------------------------\n");
		int opcion = 0;
		for(int i=0; i<tam; i++){
			cargarDescripcionColor(descripcionColor, mascotas[i].idColor, colores, tam_colores);
			cargarDescripcionTipo(descripcionTipo, mascotas[i].idTipo, tipos, tam_tipos);
			if(!mascotas[i].isEmpty){
				printf("       %2d. Nombre: %-20s / Tipo: %-10s / Color: %-10s / Edad:%3d \n", opcion+1, mascotas[i].nombre, descripcionTipo, descripcionColor, mascotas[i].edad);
				index[max] = i;
				opcion++;
				max++;
			}
		}
		printf("    --------------------------------------------------------------------------------------------------\n");
		if(getInteger(&choice, "\n    Seleccione una mascota: ", "\n  Opción inválida. ", 1, max, 3)){
			outcome = 1;
			*id = mascotas[index[choice-1]].id;
		}
	}
	return outcome;
}


int ordenarMascotasTipoNombre(eMascota* array, int tam){
    int outcome = 0;
    eMascota auxMascota;

    if(array != NULL && tam > 0){
        for(int i=0; i < tam - 1; i++){
            for(int j= i+1; j < tam; j++){
            	if(!array[i].isEmpty && !array[j].isEmpty){
					if((array[i].idTipo == array[j].idTipo && strcmp(array[i].nombre,array[j].nombre) > 0)
							||(array[i].idTipo != array[j].idTipo && (array[i].idTipo > array[j].idTipo))){
						auxMascota = array[i];
						array[i] = array[j];
						array[j] = auxMascota;
					}
            	}
            }
        }
        outcome = 1;
    }
    return outcome;
}

