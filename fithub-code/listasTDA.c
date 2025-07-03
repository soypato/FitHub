#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <conio.h>
#include "listasTDA.h"
#include "manejoDePagos.h"
#include "ducktime.h"


/// TDA LISTAS ///

nodoListaPagos * inicLista ()
{
    return NULL;
}

nodoListaPagos * crearNodoLista (stPago pagoTemporal)
{
    nodoListaPagos * nuevo = (nodoListaPagos*)malloc(sizeof(nodoListaPagos));

    nuevo->pagoCliente  = pagoTemporal;
    nuevo->siguiente=NULL;

    return nuevo;
}

nodoListaPagos * agregarNodoInicio(nodoListaPagos * lista, nodoListaPagos * nuevo)
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

nodoListaPagos * agregarNodoOrdenadoPorNomYApe(nodoListaPagos * lista, nodoListaPagos * nuevo)
{
    nodoListaPagos * actual = lista;
    nodoListaPagos * anterior = inicLista();
    while(actual!= NULL && strcmp(nuevo->pagoCliente.nombreApellido, actual->pagoCliente.nombreApellido) > 0 )
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

// Agrega un nodo a la lista de forma ordenada por el campo 'monto'
nodoListaPagos * agregarNodoOrdenadoPorMonto(nodoListaPagos *lista, nodoListaPagos *nuevoNodo)
{
    if (lista == NULL || nuevoNodo->pagoCliente.montoPago < lista->pagoCliente.montoPago)
    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    else
    {
        nodoListaPagos *actual = lista;

        while (actual->siguiente != NULL && actual->siguiente->pagoCliente.montoPago < nuevoNodo->pagoCliente.montoPago)
        {
            actual = actual->siguiente;
        }

        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
    }

    return lista;
}

// Agrega un nodo a la lista de forma ordenada por el campo 'DNI'
nodoListaPagos *agregarNodoOrdenadoPorDNI(nodoListaPagos *lista, nodoListaPagos *nuevoNodo)
{
    if (lista == NULL || nuevoNodo->pagoCliente.DNICliente < lista->pagoCliente.DNICliente)
    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    else
    {
        nodoListaPagos *actual = lista;

        while (actual->siguiente != NULL && actual->siguiente->pagoCliente.DNICliente < nuevoNodo->pagoCliente.DNICliente)
        {
            actual = actual->siguiente;
        }

        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
    }

    return lista;
}
