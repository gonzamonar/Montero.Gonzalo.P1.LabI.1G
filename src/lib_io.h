/*
 * lib_io.h
 *
 *  Created on: May 13, 2022
 *      Author: GM
 */

#include "fecha.h"

#ifndef TP2_IO_H_
#define TP2_IO_H_
#endif /* TP2_IO_H_ */


/// @brief Funci�n para obtener un nro entero (INT) ingresado por el usuario.
///
/// @param pResultado 	(int*)	-> 	Puntero donde va a almacenarse el resultado del ingreso.
/// @param mensaje 		(char*)	-> 	Mensaje para solicitar el ingreso del dato.
/// @param mensajeError (char*)	-> 	Mensaje en caso de error en el ingreso.
/// @param minimo  		(int)	-> 	Valor m�nimo del n�mero a ingresar.
/// @param maximo 		(int)	-> 	Valor m�ximo del n�mero a ingresar.
/// @param reintentos 	(int)	-> 	Cantidad de reintentos otorgados al usuario.
///
/// @return Retorna 1 en caso de �xito del ingreso, 0 en caso de falla.
int getInteger(int*, char*, char*, int, int, int);

/// @brief Funci�n para recibir una confirmaci�n binaria de tipo S/N.
///
/// @param pResultado 	(char*)	-> 	Devuelve el valor S o N ingresado por el usuario.
/// @param mensaje 		(char*)	-> 	Mensaje para solicitar el ingreso del caracter.
/// @param mensajeError (char*)	-> 	Mensaje en caso de error en el ingreso.
/// @param reintentos 	(int)	-> 	Cantidad de reintentos otorgados al usuario.
///
/// @return retorna 1 en caso de �xito del ingreso, 0 en caso de falla.
int getConfirm(char*, char*, char*, int);

/// @brief Funci�n para obtener un nro real con decimales (FLOAT) ingresado por el usuario.
///
/// @param pResultado 	(float*)-> 	Puntero donde va a almacenarse el resultado del ingreso.
/// @param mensaje 		(char*)	-> 	Mensaje para solicitar el ingreso del dato.
/// @param mensajeError (char)*	->	Mensaje en caso de error en el ingreso.
/// @param minimo 		(float)	->	Valor m�nimo del n�mero a ingresar.
/// @param maximo 		(float)	-> 	Valor m�ximo del n�mero a ingresar.
/// @param reintentos 	(int)	-> 	Cantidad de reintentos otorgados al usuario.
///
/// @return Retorna 1 en caso de �xito del ingreso, 0 en caso de falla
int getFloatingPoint(float*, char*, char*, float, float, int);

int getMenuSelection(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo);

int totitle(char *str);

int getProperName(char* dest, int size, int maxlen, int minlen, char* mensaje, char* mensajeError, int reintentos, char* exceptions);

int getDate(eFecha *pFecha, char* mensaje, char* mensajeError, int reintentos);

int getSexo(char* pResultado, char* mensaje, char* mensajeError, int reintentos);
