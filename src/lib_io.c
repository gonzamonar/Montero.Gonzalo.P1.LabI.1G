/*
 * lib_io.c
 *
 *  Created on: May 13, 2022
 *      Author: GM
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "fecha.h"


/// @brief Reversión de la función fgets eliminando el enter final del ingreso.
///
/// @param str (char*)	-> Puntero a STRING donde se almacena la cadena ingresada.
/// @param len (int)	-> INT que indica la longitud de la cadena.
///
/// @return Retorna 1 en caso de éxito del ingreso, 0 en caso de falla.
static int myGets(char*, int);

/// @brief Solicita el ingreso de un número al usuario y valida que sea INT.
///
/// @param pResultado (int*)-> Puntero a INT donde se almacena el ingreso.
///
/// @return Retorna 1 en caso de éxito del ingreso, 0 en caso de falla.
static int getInt(int*);

/// @brief Valida que todos los valores dentro de una cadena sean números enteros.
///
/// @param str (char*)-> STRING a validar por la función.
///
/// @return Retorna 1 en caso de éxito de la validación y 0 en caso de falla.
static int validateInteger(char* str);

/// @brief Solicita el ingreso de un número al usuario y valida que sea FLOAT.
///
/// @param pResultado (float*)-> Puntero a FLOAT donde se almacena el ingreso.
///
/// @return Retorna 1 en caso de éxito del ingreso, 0 en caso de falla.
static int getFloat(float*);

/// @brief Valida que todos los valores dentro de una cadena sean números reales (con decimales).
///
/// @param str (char*)-> STRING a validar por la función.
///
/// @return Retorna 1 en caso de éxito de la validación y 0 en caso de falla.
static int validateFloat(char*);

static int myStrGets(char* str, int size, int maxlen, int minlen);

static int getStr(char* dest, int size, int maxlen, int minlen, char* exceptions);

static int validateAlphaStr(char* str, char* exceptions);

static int checkVowelsAndConsonants(char* str);




static int myStrGets(char* str, int size, int maxlen, int minlen){
	int outcome = 0;
	if(str != NULL && size > 0 && fgets(str, size, stdin) == str){
		if(strlen(str)<=maxlen && strlen(str)>=minlen){
			fflush(stdin);
			if(str[strlen(str)-1] == '\n'){
				str[strlen(str)-1] = '\0';
			}
			outcome = 1;
		}
	}
	return outcome;
}

static int myGets(char* str, int len){
	int outcome = 0;
	if(str != NULL && len > 0 && fgets(str, len, stdin) == str){
		fflush(stdin);
		if(str[strlen(str)-1] == '\n'){
			str[strlen(str)-1] = '\0';
		}
		outcome = 1;
	}
	return outcome;
}

static int getInt(int* pResultado){
	int outcome = 0;
	char buffer[64];
	if(pResultado != NULL){
		if(myGets(buffer, sizeof(buffer)) && validateInteger(buffer)){
			*pResultado = atoi(buffer);
			outcome = 1;
		}
	}
	return outcome;
}

static int validateInteger(char* str){
	int outcome = 1;
	int i = 0;
	if(str != NULL && strlen(str) > 0){
		while(str[i] != '\0'){
			if(str[i] < '0' || str[i] > '9'){
				outcome = 0;
				break;
			}
			i++;
		}
	}
	return outcome;
}

static int getFloat(float* pResultado){
	int outcome = 0;
	char buffer[64];
	if(pResultado != NULL){
		if(myGets(buffer, sizeof(buffer)) && validateFloat(buffer)){
			*pResultado = atof(buffer);
			outcome = 1;
		}
	}
	return outcome;
}

static int validateFloat(char* str){
	int outcome = 1;
	int i = 0;
	if(str != NULL && strlen(str) > 0){
		while(str[i] != '\0'){
			if((str[i] < '0' || str[i] > '9') && str[i] != '.'){
				outcome = 0;
				break;
			}
			i++;
		}
	}
	return outcome;
}

static int getStr(char* dest, int size, int maxlen, int minlen, char* exceptions){
	int outcome = 0;
	char buffer[size+4];
	if(dest != NULL){
		if(myStrGets(buffer, size, maxlen, minlen) && validateAlphaStr(buffer, exceptions) && checkVowelsAndConsonants(buffer)){
			strcpy(dest, buffer);
			outcome = 1;
		}
	}
	return outcome;
}

static int checkVowelsAndConsonants(char* str){
	int outcome = 0;
	int i = 0;
	int consonantFlag = 0;
	int vowelFlag = 0;

	if(str != NULL && strlen(str) > 0){
		while(str[i] != '\0'){
			if(!vowelFlag && strchr("aeiouAEIOU", str[i])){
				vowelFlag = 1;
			}

			if(!consonantFlag && strchr("bcdfghjklmnñpqrstvwxyzBCDFGHJKLMNÑPQRSTVWXYZ", str[i])){
				consonantFlag = 1;
			}

			if(vowelFlag && consonantFlag){
				outcome = 1;
				break;
			}
			i++;
		}
	}
	return outcome;
}

static int validateAlphaStr(char* str, char* exceptions){
	int outcome = 1;
	int i = 0;

	if(str != NULL && strlen(str) > 0){
		while(str[i] != '\0'){
			if(!isalpha(str[i]) && !(strchr(exceptions, str[i]))){
				outcome = 0;
				break;
			}
			i++;
		}
	}
	return outcome;
}




int getInteger(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos){
	int outcome = 0;
	int number;
	if(mensaje != NULL && pResultado != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 1){
		do{
			reintentos--;
			fflush(stdin);
			printf("%s", mensaje);
			if(getInt(&number)){
				if(number >= minimo && number <= maximo){
					*pResultado = number;
					outcome = 1;
					break;
				}
			}
			fflush(stdin);
			if(reintentos>=1){
				printf("%s", mensajeError);
				printf("(Intentos restantes: %d)\n", reintentos);
			}
		}while(reintentos >= 1);
	}
	return outcome;
}


int getMenuSelection(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo){
	int outcome = 0;
	int number;
	if(mensaje != NULL && pResultado != NULL && mensajeError != NULL && minimo <= maximo){
		fflush(stdin);
		printf("%s", mensaje);
		if(getInt(&number)){
			if(number >= minimo && number <= maximo){
				*pResultado = number;
				outcome = 1;
				return outcome;
			}
		}
		fflush(stdin);
		printf("%s", mensajeError);
	}
	return outcome;
}


int getConfirm(char* pResultado, char* mensaje, char* mensajeError, int reintentos){
	int outcome = 0;
	char buffer;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && reintentos >= 1){
		do{
			fflush(stdin);
			printf("%s", mensaje);
			scanf("%c", &buffer);
			buffer = tolower(buffer);
			if(buffer == 's' || buffer == 'n'){
				*pResultado = buffer;
				outcome = 1;
				break;
			}else{
				if(reintentos>=1){
					printf("%s", mensajeError);
					printf("(Intentos restantes: %d)\n", reintentos);
				}
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return outcome;
}


int getFloatingPoint(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos){
	int outcome = 0;
	float number;
	if(mensaje != NULL && pResultado != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0){
		do{
			fflush(stdin);
			printf("%s", mensaje);
			if(getFloat(&number)){
				if(number >= minimo && number <= maximo){
					*pResultado = number;
					outcome = 1;
					break;
				}
			}

			if(reintentos>=1){
				printf("%s", mensajeError);
				printf("(Intentos restantes: %d)\n", reintentos);
			}
			reintentos--;
		}while(reintentos >= 0);
	}
	return outcome;
}


int totitle(char *str){
	int outcome = 0;
	int len = strlen(str);
	int i = 1;

	if(str != NULL && len>0){
		outcome = 1;
		str[0] = toupper(str[0]);
		str[1] = tolower(str[1]);
		while(str[i+1] != '\0'){
			if(str[i] == ' '){
				str[i+1] = toupper(str[i+1]);
			}else{
				str[i+1] = tolower(str[i+1]);
			}
			i++;
		}
	}
	return outcome;
}


int getProperName(char* dest, int size, int maxlen, int minlen, char* mensaje, char* mensajeError, int reintentos, char* exceptions){
	int outcome = 0;
	char strBuffer[size+4];

	if(mensaje != NULL && dest != NULL && mensajeError != NULL && size >0 && maxlen>=minlen && reintentos >= 1){
		do{
			reintentos--;
			fflush(stdin);
			printf("%s", mensaje);
			if(getStr(strBuffer,size,maxlen,minlen,exceptions)){
					fflush(stdin);
					totitle(strBuffer);
					strcpy(dest, strBuffer);
					outcome = 1;
					break;
			}
			if(reintentos>=1){
				printf("%s", mensajeError);
				printf("(Intentos restantes: %d)\n", reintentos);
			}
		}while(reintentos >= 1);
	}
	return outcome;
}


int getDate(eFecha *pFecha, char* mensaje, char* mensajeError, int reintentos){
	int outcome = 0;
	int dia;
	int mes;
	int anio;
	if(mensaje != NULL && mensajeError != NULL && reintentos >= 1){
		do{
			reintentos--;
			fflush(stdin);
			printf("%s", mensaje);
			scanf("%d/%d/%d", &dia, &mes, &anio);
			if(dia>0 && dia<32 && mes>0 && mes<13 && anio>1900 && anio<2100){
				pFecha->dia = dia;
				pFecha->mes = mes;
				pFecha->anio = anio;
				outcome = 1;
				break;
			}
			fflush(stdin);
			if(reintentos>=1){
				printf("%s", mensajeError);
				printf("(Intentos restantes: %d)\n", reintentos);
			}
		}while(reintentos >= 1);
	}
	return outcome;
}



int getSexo(char* pResultado, char* mensaje, char* mensajeError, int reintentos){
	int outcome = 0;
	char buffer;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && reintentos >= 1){
		do{
			fflush(stdin);
			printf("%s", mensaje);
			scanf("%c", &buffer);
			buffer = tolower(buffer);
			if(buffer == 'm' || buffer == 'f'){
				*pResultado = buffer;
				outcome = 1;
				break;
			}else{
				if(reintentos>=1){
					printf("%s", mensajeError);
					printf("(Intentos restantes: %d)\n", reintentos);
				}
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return outcome;
}

