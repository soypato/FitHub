#ifndef MANEJOINVENTARIO_H_INCLUDED
#define MANEJOINVENTARIO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char nombreObjeto[50];
    float pesoEnKg;
    int cantidad;
} stObjeto;

typedef struct nodoListaInventario
{
  stObjeto objeto;
  struct nodoListaInventario * siguiente;
} nodoListaInventario;

typedef struct pila
{
    nodoListaInventario * listaDePila;
} pila;


void inicPila(pila *p);
void apilarObjeto(pila *p);
void mostrarPila(const pila *p);
void eliminarObjeto(pila *p);
void buscarObjeto(const pila *p);
void modificarObjeto(pila *p);
#endif // MANEJOINVENTARIO_H_INCLUDED
