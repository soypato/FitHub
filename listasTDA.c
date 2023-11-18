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

nodoListaPagos * agregar_nodo_ordenado(nodoListaPagos * lista, nodoListaPagos * nuevo)
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

