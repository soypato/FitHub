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

nodoListaInventario * inicListaInventario();
nodoListaInventario * crearNodoInventario(stObjeto objeto);
nodoListaInventario * agregarAlPrincipio(nodoListaInventario * lista, nodoListaInventario * nuevoNodo);
nodoListaInventario * borrarPrimerNodo(nodoListaInventario * lista);
nodoListaInventario * retornarPrimerNodo(nodoListaInventario * lista);
int listaVacia(nodoListaInventario * lista);
void mostrarNodoInventario(nodoListaInventario * nodo);
void mostrarUnObjeto(stObjeto dato);
int inicPila(pila * p);
void mostrarPila(pila p);
stObjeto tope(pila p);
int pilaVacia(pila p);
#endif // MANEJOINVENTARIO_H_INCLUDED
