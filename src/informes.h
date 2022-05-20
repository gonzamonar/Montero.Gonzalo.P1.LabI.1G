/*
 * informes.h
 *
 *  Created on: May 20, 2022
 *      Author: GM
 */

#ifndef INFORMES_H_
#define INFORMES_H_
#endif /* INFORMES_H_ */


void seleccionInformes(eMascota* mascotas, int tam_mascotas, eServicio* servicios, int tam_servicios, eTipo* tipos, int tam_tipos, eColor* colores, int tam_colores, eTrabajo* trabajos, int tam_trabajos, eCliente* clientes, int tam_clientes, int qMascotas, int qTrabajos);
int filtrarMascotas(eMascota* array, int tam, eColor* colores, int tam_colores, eTipo* tipos, int tam_tipos, eCliente* clientes, int tam_clientes, int criterio, int filtro);
int informarMenorEdad(eMascota* array, int tam);
int informarPromedioVacunados(eMascota* array, int tam);
int contarColorTipo(eMascota* array, int tam, eColor* colores, int tam_colores, eTipo* tipos, int tam_tipos, int idColor, int idTipo);
int contarColores(eMascota* array, int tam, eColor* colores, int tam_colores);
int getMax(int* array, int size);
int filtrarTrabajos(eTrabajo* array, int tam, eMascota* mascotas, int tam_mascotas, eServicio* servicios, int tam_servicios, eTipo* tipos, int tam_tipos, int criterio, int idFiltro);
int sumarServicios(eTrabajo* array, int tam, eMascota* mascotas, int tam_mascotas, eServicio* servicios, int tam_servicios, eColor* colores, int tam_colores, eTipo* tipos, int tam_tipos, int idMascota);
int filtrarFechaTrabajos(eTrabajo* array, int tam, eMascota* mascotas, int tam_mascotas, eServicio* servicios, int tam_servicios, eTipo* tipos, int tam_tipos, eFecha fecha);
