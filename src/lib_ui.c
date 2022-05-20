/*
 * lib_ui.c
 *
 *  Created on: May 13, 2022
 *      Author: GM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib_ui.h"
#include "lib_io.h"


void pause(void){
	char c;
	fflush(stdin);
	printf("\n\n  ***** Presione enter para continuar. *****");
	scanf("%c", &c);
	fflush(stdin);
}


int printMainMenu(int qMascotas, int qTrabajos){
	system("cls");
	int selection;
	char msjMascotas[20];
	char msjTrabajos[20];
	(qMascotas!=1) ? (strcpy(msjMascotas,"mascotas cargadas")) : (strcpy(msjMascotas," mascota cargada "));
	(qTrabajos!=1) ? (strcpy(msjTrabajos,"trabajos cargados")) : (strcpy(msjTrabajos," trabajo cargado "));
	printf("\n\n");
	printf(" +------------------------------------------------------------------------------------------------------+\n");
	printf(" |--------------------------------------  *** MENÚ PRINCIPAL ***  --------------------------------------|\n");
	printf(" |------------------------------------------------------------------------------------------------------|\n");
	printf(" |                                                                                                      |\n");
	printf(" |  1. ALTA MASCOTA          < %4d %s >                                                 |\n", qMascotas, msjMascotas);
	printf(" |  2. MODIFICAR MASCOTA                                                                                |\n");
	printf(" |  3. BAJA MASCOTA                                                                                     |\n");
	printf(" |  4. LISTAR MASCOTAS                                                                                  |\n");
	printf(" |  5. LISTAR TIPOS                                                                                     |\n");
	printf(" |  6. LISTAR COLORES                                                                                   |\n");
	printf(" |  7. LISTAR SERVICIOS                                                                                 |\n");
	printf(" |  8. ALTA TRABAJO          < %4d %s >                                                 |\n", qTrabajos, msjTrabajos);
	printf(" |  9. LISTAR TRABAJOS                                                                                  |\n");
	printf(" |  10. MENU INFORMES                                                                                   |\n");
	printf(" |  11. Salir                                                                                           |\n");
	printf(" |                                                                                                      |\n");
	printf(" |------------------------------------------------------------------------------------------------------|\n");
	printf(" +------------------------------------------------------------------------------------------------------+\n\n");
	fflush(stdin);
	getMenuSelection(&selection, "  Elija una opción: ", "\n  Opción de menú incorrecta, inténtelo nuevamente.\n", 1, 11);
	return selection;
}


void mostrarMenuModificacion(int* option){
	printf("\n  ¿Qué campo desea modificar?\n");
	printf("    1. Nombre.\n");
	printf("    2. Tipo.\n");
	printf("    3. Color.\n");
	printf("    4. Edad.\n");
	printf("    5. Vacunado.\n");
	printf("    6. Volver al menú principal.\n");
	if(!getInteger(option, "\n  Elija el nº de opción: ", "\n  Opción de menú incorrecta, inténtelo nuevamente.", 1, 6, 3)){
		printf("\n  El proceso de modificación ha sido cancelado.");
		*option = 6;
		pause();
	}
}


int mostrarMenuInformes(void){
	system("cls");
	int selection;
	printf("\n\n");
	printf(" +------------------------------------------------------------------------------------------------------+\n");
	printf(" |-------------------------------------  *** SUBMENÚ INFORMES ***  -------------------------------------|\n");
	printf(" |------------------------------------------------------------------------------------------------------|\n");
	printf(" |                                                                                                      |\n");
	printf(" |    1. Mostrar mascotas del color seleccionado                                                        |\n");
	printf(" |    2. Informar promedio de mascotas vacunadas                                                        |\n");
	printf(" |    3. Informar mascota/s de menor edad                                                               |\n");
	printf(" |    4. Listar mascotas agrupadas por tipo                                                             |\n");
	printf(" |    5. Informar cantidad de mascotas de un color y tipo seleccionado                                  |\n");
	printf(" |    6. Informar el color con más cantidad de mascotas                                                 |\n");
	printf(" |    7. Mostrar historial de trabajos realizados a una mascota                                         |\n");
	printf(" |    8. Informar total de importes de servicios realizados a una mascota                               |\n");
	printf(" |    9. Mostrar mascotas a las que se les realizó el servicio seleccionado                             |\n");
	printf(" |   10. Mostrar los trabajos realizados en una fecha seleccionada                                      |\n");
	printf(" |   11. REGRESAR AL MENÚ PRINCIPAL                                                                     |\n");
	printf(" |                                                                                                      |\n");
	printf(" |------------------------------------------------------------------------------------------------------|\n");
	printf(" +------------------------------------------------------------------------------------------------------+\n\n");
	fflush(stdin);
	getMenuSelection(&selection, "  Elija una opción: ", "\n  Opción de menú incorrecta, inténtelo nuevamente.\n", 1, 11);
	return selection;
}


void mostrarMenuClientes(int* option){
	printf("\n  ¿Qué desea hacer?\n");
	printf("    1. Ingresar un cliente nuevo.\n");
	printf("    2. Seleccionar un cliente ya existente.\n");
	printf("    3. Cancelar el alta.\n");
	if(!getInteger(option, "\n  Elija el nº de opción: ", "\n  Opción de menú incorrecta, inténtelo nuevamente.", 1, 3, 3)){
		printf("\n  El proceso de modificación ha sido cancelado.");
		*option = 3;
		pause();
	}
}
