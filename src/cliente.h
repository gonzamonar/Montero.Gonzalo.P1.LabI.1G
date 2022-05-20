/*
 * cliente.h
 *
 *  Created on: May 20, 2022
 *      Author: GM
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

	typedef struct{
		int id;		//comienza en 2000
		char nombre[20];
		char sexo;
		int isEmpty;
	}eCliente;

#endif /* CLIENTE_H_ */



	int initClientes(eCliente* array, int len);
	int harcodeClientes(eCliente* array, int size, int* nextId);
	int cargarDescripcionCliente(char* descripcion, int idCliente, eCliente* clientes, int tam);
	int seleccionarCliente(eCliente* clientes, int tam, int* id);
	int obtenerIndexCliente(eCliente* clientes, int tam_clientes, int idCliente);
	int agregarCliente(eCliente* array, int tam, int id, char nombre[], char sexo);
	int getFreeSpace_Clientes(eCliente* array, int tam, int* pIndex);
