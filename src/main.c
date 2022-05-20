/*
 ============================================================================
 Name        : c.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "lib_io.h"
#include "lib_ui.h"
#include "fecha.h"
#include "tipo.h"
#include "color.h"
#include "cliente.h"
#include "mascota.h"
#include "servicio.h"
#include "trabajo.h"
#include "informes.h"

#define TAM_MASCOTAS 200
#define TAM_TRABAJOS 200
#define TAM_CLIENTES 100
#define TAM_TIPOS 5
#define TAM_COLORES 5
#define TAM_SERVICIOS 3


int main(void) {
	eMascota mascotas[TAM_MASCOTAS];
	eTrabajo trabajos[TAM_TRABAJOS];
	eTipo tipos[TAM_TIPOS];
	eColor colores[TAM_COLORES];
	eServicio servicios[TAM_SERVICIOS];
	eCliente clientes[TAM_CLIENTES];

	int nextIdMascotas = 1;
	int nextIdTrabajos = 1;
	int nextIdClientes = 2000;
	int qMascotas = 0;
	int qTrabajos = 0;
	int selection;

	setbuf(stdout, NULL);
	setlocale(LC_ALL, "");

	initMascotas(mascotas, TAM_MASCOTAS);
	initTrabajos(trabajos, TAM_TRABAJOS);
	initClientes(clientes, TAM_CLIENTES);
	initTipos(tipos, TAM_TIPOS);
	initColores(colores, TAM_COLORES);
	initServicios(servicios, TAM_SERVICIOS);

	harcodeMascotas(mascotas, TAM_MASCOTAS, &nextIdMascotas, &qMascotas);
	harcodeTrabajos(trabajos, TAM_TRABAJOS, &nextIdTrabajos, &qTrabajos);
	harcodeClientes(clientes, TAM_CLIENTES, &nextIdClientes);
	harcodeTipos(tipos, TAM_TIPOS);
	harcodeColores(colores, TAM_COLORES);
	harcodeServicios(servicios, TAM_SERVICIOS);

	do{
		switch(printMainMenu(qMascotas, qTrabajos)){
			case 1: //alta mascota
					(qMascotas!=TAM_MASCOTAS) ? crearMascota(mascotas, TAM_MASCOTAS, tipos, TAM_TIPOS, colores, TAM_COLORES, clientes, TAM_CLIENTES, &nextIdMascotas, &qMascotas, &nextIdClientes) : printf("\n  No se pueden cargar más mascotas en el sistema.");
					pause();
					break;

			case 2: //modificar mascota
					(qMascotas) ? modificarMascota(mascotas, TAM_MASCOTAS, tipos, TAM_TIPOS, colores, TAM_COLORES, clientes, TAM_CLIENTES, &nextIdMascotas) : printf("\n  No hay mascotas cargadas para modificar.");
					pause();
					break;

			case 3: //baja mascota
					(qMascotas) ? bajaMascota(mascotas, TAM_MASCOTAS, tipos, TAM_TIPOS, colores, TAM_COLORES, clientes, TAM_CLIENTES, &nextIdMascotas, &qMascotas) : printf("\n  No hay mascotas cargadas para eliminar.");
					pause();
					break;

			case 4: //listar mascotas
					(qMascotas) ? listarMascotas(mascotas, TAM_MASCOTAS, tipos, TAM_TIPOS, colores, TAM_COLORES, clientes, TAM_CLIENTES) : printf("\n  No hay mascotas cargadas para mostrar.") ;
					pause();
					break;

			case 5: //listar tipos
					listarTipos(tipos, TAM_TIPOS);
					pause();
					break;

			case 6: //listar colores
					listarColores(colores, TAM_COLORES);
					pause();
					break;

			case 7: //listar servicios
					listarServicios(servicios, TAM_SERVICIOS);
					pause();
					break;

			case 8: //alta trabajo
					if(qTrabajos!=TAM_TRABAJOS){
						if(qMascotas!=0){
							crearTrabajo(trabajos, TAM_TRABAJOS, mascotas, TAM_MASCOTAS, tipos, TAM_TIPOS, colores, TAM_COLORES, servicios, TAM_SERVICIOS, &nextIdTrabajos, &qTrabajos);
						}else{
							printf("\n  No hay mascotas cargadas para dar de alta trabajos.");
						}
					}else{
						printf("\n  No se pueden cargar más trabajos en el sistema.");
					}
					pause();
					break;

			case 9: //listar trabajos
					(qTrabajos) ? listarTrabajos(trabajos, TAM_TRABAJOS, mascotas, TAM_MASCOTAS, servicios, TAM_SERVICIOS, tipos, TAM_TIPOS) : printf("\n  No hay trabajos cargados para mostrar.");
					pause();
					break;

			case 10://menu informes
					seleccionInformes(mascotas, TAM_MASCOTAS, servicios, TAM_SERVICIOS, tipos, TAM_TIPOS, colores, TAM_COLORES, trabajos, TAM_TRABAJOS, clientes, TAM_CLIENTES, qMascotas, qTrabajos);
					break;

			case 11: //salir
					selection = 11;
					printf("\n  Programa concluido.");
					pause();
					break;

			default:
					pause();
					break;
		}
	}while(selection != 11);
}
