#ifndef LISTASTDA_H_INCLUDED
#define LISTASTDA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listasTDA.h"
#include "manejoDePagos.h"
#include "manejoDeClientes.h"
#include "ducktime.h"

typedef struct
{
    int DNICliente;
    char nombreApellido[30];
    float montoPago;
    int idMetodoDePago; /// 1 para efectivo, 2 tarj credito, 3 tarj debito, 4 billeteras virtuales
    char metodoDePago[20]; /// efectivo, bill virtual, tarjeta credito, tarjeta debito
    tiempo fechaDePago;
}stPago;

/* cuando hagamos la funcion de alta del usuario poner, un if metodo de pago == 1 strcpy,
    para despues asignarle el metodo de pago que haya elegido segun el numero */

typedef struct nodoListaPagos{
    stPago pagoCliente;
    struct nodoListaPagos* siguiente;
}nodoListaPagos;

/// PROTOTIPADOS
void imprimirMenuPagosEmpleado();
int mainPagosEmpleado();
nodoListaPagos * crearNuevoPagoCliente();
void mostrarNodo(nodoListaPagos *nodo);
void mostrarLista(nodoListaPagos* inicioLista);


#endif // LISTASTDA_H_INCLUDED
