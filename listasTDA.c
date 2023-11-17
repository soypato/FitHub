#include <stdio.h>
#include <stdlib.h>
#include "listasTDA.h"
#include "manejoDeClientes.h"
#include "ducktime.h"
#include <conio.h>
#include <stddef.h>
#include <string.h>

/// TDA LISTAS ///

nodoLista * inicLista ()
{
    return NULL;
}

nodoLista * crearNodoLista (int DNI,char nombreyApellido[], float montoPago, int idMetodoPago, char metodoPago[], tiempo fechaPago)
{
    nodoLista * nuevo = (nodoLista*) malloc (sizeof(nodoLista));
    nuevo->DNI = DNI;
    strcpy(nuevo->nombreYApellido, nombreyApellido);
    nuevo->fechaPago = fechaPago;
    nuevo->idMetodoPago = idMetodoPago;
    strcpy(nuevo->metodoPago, metodoPago);
    nuevo->montoPago = montoPago;
    nuevo->siguiente = NULL;

    return nuevo;
}

nodoLista * agregarNodoInicio(nodoLista * lista, nodoLista * nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        nuevo->siguiente = lista;
        lista = nuevo;
    }
    return lista;
}

nodoLista * agregar_nodo_ordenado(nodoLista * lista, nodoLista * nuevo)
{
    nodoLista * actual = lista;
    nodoLista * anterior = inicLista();
    while(actual!= NULL && strcmp(nuevo->nombreYApellido, actual->nombreYApellido) > 0 )
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if(anterior==NULL)
    {
        nuevo->siguiente = lista;
        lista = nuevo;
    }
    else
    {
        anterior->siguiente = nuevo;
        nuevo->siguiente = actual;
    }
    return lista;
}

