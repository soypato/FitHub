#ifndef ARBOLESTDA_H_INCLUDED
#define ARBOLESTDA_H_INCLUDED
#include "manejoDeClientes.h"
#include "arbolesTDA.h"

typedef struct nodoArbol
{
    stCliente cliente;
    struct nodoArbol* izq;
    struct nodoArbol* der;
} nodoArbol;



/// TDA arbolCliente
nodoArbol * inicArbol();
nodoArbol * cargarNodoArbolClientes(stCliente cliente);
nodoArbol * insertar(nodoArbol * arbol, nodoArbol * nuevo);
nodoArbol * buscarArbolCliente(nodoArbol * arbol, int dni);
nodoArbol* buscarDNIEnADA(stCeldaPlanes ADA[], int validos, int dni);



#endif // ARBOLESTDA_H_INCLUDED
