/*
 * informes.c
 *
 *  Created on: May 20, 2022
 *      Author: GM
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
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

//define block Colores
#define NEGRO 5000
#define BLANCO 5001
#define ROJO 5002
#define GRIS 5003
#define AZUL 5004

void seleccionInformes(eMascota* mascotas, int tam_mascotas, eServicio* servicios, int tam_servicios, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores, eTrabajo* trabajos, int tam_trabajos, eCliente* clientes, int tam_clientes, int qMascotas, int qTrabajos){
	int selection;
	int idColor;
	int idTipo;
	int idMascota;
	int idServicio;
	eFecha fecha;

	do{
		system("cls");
		selection = mostrarMenuInformes();
		switch(selection){
			case 1: //Mostrar mascotas del color seleccionado por el usuario
					if(qMascotas){
						if(seleccionarColor(colores, tam_colores, &idColor)){
							system("cls");
							filtrarMascotas(mascotas, tam_mascotas, colores, tam_colores, tipos, tam_tipos, clientes, tam_clientes, 0, idColor); //criterio 0 == Color
						}
					}else{
						printf("\n\n  No hay mascotas dadas de alta en el sistema");
					}
					pause();
					break;

			case 2: //Informar promedio de mascotas vacunadas sobre el total
					if(qMascotas){
						informarPromedioVacunados(mascotas, tam_mascotas);
					}else{
						printf("\n\n  No hay mascotas dadas de alta en el sistema");
					}
					pause();
					break;

			case 3: //Informar la/s mascotas de menor edad
					if(qMascotas){
						informarMenorEdad(mascotas, tam_mascotas);
					}else{
						printf("\n\n  No hay mascotas dadas de alta en el sistema");
					}
					pause();
					break;

			case 4: //Mostrar un listado de las mascotas separadas por tipo.
					if(qMascotas){
						system("cls");
						for(int id=1000; id<1005; id++){
							filtrarMascotas(mascotas, tam_mascotas, colores, tam_colores, tipos, tam_tipos, clientes, tam_clientes, 1, id); //criterio 1 == Tipo
						}
					}else{
						printf("\n\n  No hay mascotas dadas de alta en el sistema");
					}
					pause();
					break;

			case 5: //Elegir un color y un tipo y contar cuantas mascotas hay de ese color y ese tipo.
					if(qMascotas){
						system("cls");
						if(seleccionarColor(colores, tam_colores, &idColor) && seleccionarTipo(tipos, tam_tipos, &idTipo)){
							contarColorTipo(mascotas, tam_mascotas, colores, tam_colores, tipos, tam_tipos, idColor, idTipo);
						}
					}else{
						printf("\n\n  No hay mascotas dadas de alta en el sistema");
					}
					pause();
					break;

			case 6: //Mostrar el color con más cantidad de mascotas
					if(qMascotas){
						contarColores(mascotas, tam_mascotas, colores, tam_colores);
					}else{
						printf("\n\n  No hay mascotas dadas de alta en el sistema");
					}
					pause();
					break;

			case 7: //Pedir una mascota y mostrar todos los trabajos que se le hicieron a la misma.
					if(qTrabajos){
						if(seleccionarMascota(mascotas, tam_mascotas, tipos, tam_tipos, colores, tam_colores, &idMascota)){
							filtrarTrabajos(trabajos, tam_trabajos, mascotas, tam_mascotas, servicios, tam_servicios, tipos, tam_tipos, 1, idMascota);
						}
					}else{
						printf("\n\n  No hay trabajos dados de alta en el sistema");
					}
					pause();
					break;

			case 8: //Pedir una mascota e informar la suma de los importes de los servicios que se le hicieron.
					if(qTrabajos){
						if(seleccionarMascota(mascotas, tam_mascotas, tipos, tam_tipos, colores, tam_colores, &idMascota)){
							sumarServicios(trabajos, tam_trabajos, mascotas, tam_mascotas, servicios, tam_servicios, colores, tam_colores, tipos, tam_tipos, idMascota);
						}
					}else{
						printf("\n\n  No hay trabajos dados de alta en el sistema");
					}
					pause();
					break;

			case 9: //Pedir un servicio y mostrar las mascotas a las que se les realizó ese servicio y la fecha.
					if(qTrabajos){
						if(seleccionarServicio(servicios, tam_servicios, &idServicio)){
							filtrarTrabajos(trabajos, tam_trabajos, mascotas, tam_mascotas, servicios, tam_servicios, tipos, tam_tipos, 0, idServicio);
						}
					}else{
						printf("\n\n  No hay trabajos dados de alta en el sistema");
					}
					pause();
					break;


			case 10: //Pedir una fecha y mostrar todos los servicios realizados en la misma.
					if(qTrabajos){
						if(getDate(&fecha, "\n  Ingrese la fecha del trabajo (dd/mm/aaaa): ", "  Error, ingrese una fecha válida. ", 3)){
							filtrarFechaTrabajos(trabajos, tam_trabajos, mascotas, tam_mascotas, servicios, tam_servicios, tipos, tam_tipos, fecha);
						}
					}else{
						printf("\n\n  No hay trabajos dados de alta en el sistema");
					}
					pause();
					break;

			case 11: //salir
					selection = 11;
					break;

		}
	}while(selection != 11);
}



int filtrarMascotas(eMascota* array, int tam, eColor* colores, int tam_colores, eTipo* tipos, int tam_tipos, eCliente* clientes, int tam_clientes, int criterio, int filtro){
	int outcome = 0;
	char descripcionColor[8];
	char descripcionTipo[8];
	char nombreCliente[20];

	if(array!=NULL && tam>0&& tipos!=NULL && tam_tipos>0 && colores!=NULL && tam_colores>0){
		printf("\n\n");
		printf(" +------------------------------------------------------------------------------------------------------+\n");
		if(criterio){
			cargarDescripcionTipo(descripcionTipo, filtro, tipos, tam_tipos);
			printf(" |--------------------------------  *** MASCOTAS DE TIPO: %-8s ***  --------------------------------|\n", descripcionTipo);
			printf(" |------------------------------------------------------------------------------------------------------|\n");
			printf("   %6s | %20s | %20s | %5s | %8s | %15s \n", "ID", "Nombre", "Color ", "Edad", "Vacunado", "Dueña/o");
			printf(" +------------------------------------------------------------------------------------------------------+\n");
		}else{
			cargarDescripcionColor(descripcionColor, filtro, colores, tam_colores);
			printf(" |--------------------------------  *** MASCOTAS DE COLOR: %-8s ***  -------------------------------|\n", descripcionColor);
			printf(" |------------------------------------------------------------------------------------------------------|\n");
			printf("   %6s | %20s | %20s | %5s | %8s | %15s \n", "ID", "Nombre", "Tipo  ", "Edad", "Vacunado", "Dueña/o");
			printf(" +------------------------------------------------------------------------------------------------------+\n");
		}
		for(int i=0;i<tam;i++){
			cargarDescripcionCliente(nombreCliente, array[i].idCliente, clientes, tam_clientes);
			if(criterio){
				if(!array[i].isEmpty && array[i].idTipo == filtro){
					outcome = 1;
					cargarDescripcionColor(descripcionColor, array[i].idColor, colores, tam_colores);
					printf("   %6d | %20s | %20s | %5d | %8c | %-15s \n", array[i].id, array[i].nombre, descripcionColor, array[i].edad, array[i].vacunado, nombreCliente);
				}
			}else{
				if(!array[i].isEmpty && array[i].idColor == filtro){
					outcome = 1;
					cargarDescripcionTipo(descripcionTipo, array[i].idTipo, tipos, tam_tipos);
					printf("   %6d | %20s | %20s | %5d | %8c | %-15s \n", array[i].id, array[i].nombre, descripcionTipo, array[i].edad, array[i].vacunado, nombreCliente);
				}
			}
		}
		printf(" +------------------------------------------------------------------------------------------------------+\n");
	}
	return outcome;
}


int informarMenorEdad(eMascota* array, int tam){
	int outcome = 0;
	int min;
	int contador = 0;
	int indexador[tam];

	if(array != NULL && tam>0){
		outcome = 1;
		for(int i=0;i<tam;i++){
			if(!array[i].isEmpty && (array[i].edad<min || i==0)){
				min = array[i].edad;
			}
		}

		for(int i=0;i<tam;i++){
			if(!array[i].isEmpty && (array[i].edad==min)){
				indexador[contador] = i;
				contador++;
			}
		}

		if(contador==1){
			printf("\n\n  La mascota de menor edad es %s, con %d años.", array[indexador[0]].nombre, array[indexador[0]].edad);
		}else{
			printf("\n\n  Las mascotas de menor edad son ");
			int i;
			for(i=0;i<contador-1;i++){
				(i>0) ? printf(", %s", array[indexador[i]].nombre) : printf("%s", array[indexador[i]].nombre) ;
			}
			if(min==1){
				printf(" y %s, con una edad de %d año.\n\n", array[indexador[i]].nombre, array[indexador[0]].edad);
			}else{
				printf(" y %s, con una edad de %d años.\n\n", array[indexador[i]].nombre, array[indexador[0]].edad);
			}
		}
	}

	return outcome;
}


int informarPromedioVacunados(eMascota* array, int tam){
	int outcome = 0;
	int contador = 0;
	float total = 0;
	float promedio;

	if(array != NULL && tam>0){
		outcome=1;
		for(int i=0;i<tam;i++){
			if(!array[i].isEmpty){
				total++;
				if(array[i].vacunado=='s'){
					contador++;
				}
			}
		}
		promedio = contador / total * 100;
		printf("\n\n  El promedio de mascotas vacunadas es del %.2f %%: están vacunadas %d de %.0f mascotas.", promedio, contador, total);
	}
	return outcome;
}


int contarColorTipo(eMascota* array, int tam, eColor* colores, int tam_colores, eTipo* tipos, int tam_tipos, int idColor, int idTipo){
	int outcome = 0;
	int contador = 0;
	char descripcionColor[8];
	char descripcionTipo[8];

	if(array != NULL && tam>0){
		outcome = 1;
		for(int i=0;i<tam;i++){
			if(!array[i].isEmpty && array[i].idColor==idColor && array[i].idTipo==idTipo){
				contador++;
			}
		}

		cargarDescripcionColor(descripcionColor, idColor, colores, tam_colores);
		cargarDescripcionTipo(descripcionTipo, idTipo, tipos, tam_tipos);
		if(contador==1){
			printf("\n\n  Hay %d %s de color %s.", contador, descripcionTipo, descripcionColor);
		}else if(contador>1){
			printf("\n\n  Hay %d %ss de color %s.", contador, descripcionTipo, descripcionColor);
		}else{
			printf("\n\n  No se cargó ningún %s de color %s.", descripcionTipo, descripcionColor);
		}
	}
	return outcome;
}


int contarColores(eMascota* array, int tam, eColor* colores, int tam_colores){
	int outcome = 0;
	int contador[5] = {0,0,0,0,0}; //negro, blanco, rojo, gris, azul
	int max;
	char descripcionColor[8];
	char colorMasElegido[50] = {""};

	if(array != NULL && tam>0){
		outcome = 1;
		for(int i=0;i<tam;i++){
			if(!array[i].isEmpty){
				switch(array[i].idColor){
					case NEGRO:
						contador[0]++;
						break;
					case BLANCO:
						contador[1]++;
						break;
					case ROJO:
						contador[2]++;
						break;
					case GRIS:
						contador[3]++;
						break;
					case AZUL:
						contador[4]++;
				}
			}
		}

		max = getMax(contador, 5);
		int j=0;
		for(int i=0;i<5;i++){
			if(contador[i]==max){
				cargarDescripcionColor(descripcionColor, i+5000, colores, tam_colores);
				strcat(colorMasElegido, descripcionColor);
				strcat(colorMasElegido, ", ");
				j++;
			}
		}
		if(j==1){
			printf("\n\n  El color más frecuente es %scon %d mascotas.", colorMasElegido, max);
		}else{
			printf("\n\n  Los colores más frecuente son %scon %d mascotas cada uno.", colorMasElegido, max);
		}
	}
	return outcome;
}


int getMax(int* array, int size){
	int max;
	if(array != NULL && size>0){
		for(int i=0;i<size;i++){
			if(array[i]>max || i==0){
				max = array[i];
			}
		}
	}
	return max;
}


int filtrarTrabajos(eTrabajo* array, int tam, eMascota* mascotas, int tam_mascotas, eServicio* servicios, int tam_servicios, eTipo* tipos, int tam_tipos, int criterio, int idFiltro){
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
			if(!array[i].isEmpty && ((criterio==1 && array[i].idMascota==idFiltro) || (criterio==0 && array[i].idServicio==idFiltro))){
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


int sumarServicios(eTrabajo* array, int tam, eMascota* mascotas, int tam_mascotas, eServicio* servicios, int tam_servicios, eColor* colores, int tam_colores, eTipo* tipos, int tam_tipos, int idMascota){
	int outcome = 0;
	int indexMascota;
	int indexServicio;

	if(array!=NULL && tam>0 && mascotas!=NULL && tam_mascotas>0 && servicios!=NULL && tam_servicios>0){
		outcome = 1;
		float suma = 0;
		indexMascota = obtenerIndexMascota(mascotas, tam_mascotas, idMascota);
		for(int i=0;i<tam;i++){
			if(!array[i].isEmpty && array[i].idMascota==idMascota){
				indexServicio = obtenerIndexServicio(servicios, tam_servicios, array[i].idServicio);
				suma += servicios[indexServicio].precio;
			}
		}
		mostrarFichaMascota(mascotas[indexMascota], tipos, tam_tipos, colores, tam_colores);
		printf("\n\n  El monto total de los servicios realizados a %s es de $ %.2f.", mascotas[indexMascota].nombre, suma);
	}
	return outcome;
}


int filtrarFechaTrabajos(eTrabajo* array, int tam, eMascota* mascotas, int tam_mascotas, eServicio* servicios, int tam_servicios, eTipo* tipos, int tam_tipos, eFecha fecha){
	int outcome = 0;
	int indexMascota;
	int indexServicio;
	int flag = 0;
	char descripcionMascota[20];


	if(array!=NULL && tam>0 && mascotas!=NULL && tam_mascotas>0 && servicios!=NULL && tam_servicios>0 && tipos!=NULL && tam_tipos>0){
		outcome = 1;

		for(int i=0;i<tam;i++){
			if(!array[i].isEmpty && (array[i].fecha.dia == fecha.dia && array[i].fecha.mes == fecha.mes && array[i].fecha.anio == fecha.anio)){
				flag = 1;
				break;
			}
		}
		if(flag){
			system("cls");
			printf("\n\n");
			printf(" +------------------------------------------------------------------------------------------------------+\n");
			printf(" |---------------------------------  *** TRABAJOS DEL %02d/%02d/%4d ***  ----------------------------------|\n", fecha.dia, fecha.mes, fecha.anio);
			printf(" |------------------------------------------------------------------------------------------------------|\n");
			printf("      ID |                   MASCOTA                      |           SERVICIO           \n");
			printf("         |    id              nombre                 tipo |    servicio           precio \n");
			printf(" +------------------------------------------------------------------------------------------------------+\n");
			for(int i=0;i<tam;i++){
				if(!array[i].isEmpty && (array[i].fecha.dia == fecha.dia && array[i].fecha.mes == fecha.mes && array[i].fecha.anio == fecha.anio)){
					indexMascota = obtenerIndexMascota(mascotas, tam_mascotas, array[i].idMascota);
					indexServicio = obtenerIndexServicio(servicios, tam_servicios, array[i].idServicio);
					cargarDescripcionTipo(descripcionMascota, mascotas[indexMascota].idTipo, tipos, tam_tipos);
					printf("  %6d | %4d %20s %20s |  %-20s %5.2f \n", array[i].id, mascotas[indexMascota].id, mascotas[indexMascota].nombre, descripcionMascota,
								servicios[indexServicio].descripcion, servicios[indexServicio].precio);
				}
			}
			printf(" +------------------------------------------------------------------------------------------------------+\n");
		}else{
			printf("\n\n   No se realizaron trabajos en la fecha elegida.");
		}
	}
	return outcome;
}
