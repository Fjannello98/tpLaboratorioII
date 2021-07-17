#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <iostream>
using namespace std;
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "clsFecha.h"

// funciones de cin
void cargarCadena(char *pal,int tam);

// getFecha de hoy

Fecha getFechaDeHoy();

// estilos
void LINEA_EN_Y(const int,const int,const int,const int);
void LINEA_EN_X(const int,const int,const int,const int);

// buscar posicion

int buscarPosOperacion(const int);
int buscarPosCliente(const int);
int buscarPosVendedor(const int);
int buscarPosVehiculo(const int);


#endif // FUNCIONES_H_INCLUDED
