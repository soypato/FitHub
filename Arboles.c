#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "Listas.h"
#include "Arboles.h"

nodoArbol* inicArbolB()
{
    return NULL;
}

nodoArbol* crear_nodoArbol(int dato)
{
    nodoArbol* nuevo= (nodoArbol*) malloc (sizeof(nodoArbol));
    nuevo->dato=dato;
    nuevo->der=NULL;
    nuevo->izq=NULL;
    return nuevo;
}

nodoArbol* insertar_en_arbol(nodoArbol* arbol, nodoArbol* nuevo)
{
    if(arbol==NULL)
    {
        arbol=nuevo;
    }
    else
    {
        if(nuevo->dato < arbol->dato)
        {
            (arbol)->izq = insertar_en_arbol(arbol->izq,nuevo);
        }
        else
        {
            (arbol)->der = insertar_en_arbol(arbol->der,nuevo);
        }
    }
    return arbol;
}


nodoArbol* cargar_arbol(nodoArbol* arbol)
{
    char mander ='s';
    int dato=0;
    nodoArbol* nuevo = inicArbolB();
    while(mander =='s')
    {
        //dato=cargar_persona();
        printf("ingrese dato: ");fflush(stdin);scanf("%d",&dato);
        nuevo = crear_nodoArbol(dato);
        arbol = insertar_en_arbol(arbol,nuevo);
        printf("seguir?\n");fflush(stdin);scanf("%c",&mander);
    }
    return arbol;
}

void mostrar_nodoArbol(nodoArbol* arbol)/// para int
{
    printf("dato: %d",arbol->dato);
}

///para integer

void preorder(nodoArbol* arbol)
{
    if(arbol)
    {
        mostrar_nodoArbol(arbol);/// printf() del ato en cuestuion
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

void inorder(nodoArbol* arbol)
{
    if(arbol)
    {
        preorder(arbol->izq);
        mostrar_nodoArbol(arbol);
        preorder(arbol->der);
    }
}

void posorder(nodoArbol* arbol)
{
    if(arbol)
    {
        preorder(arbol->izq);
        preorder(arbol->der);
        mostrar_nodoArbol(arbol);
    }
}
///para integer


///para dato x(stPersona)
/*
int preorder_persona(nodoArbol* arbol)
{
    if(arbol)
    {
        mostrar_persona(arbol->dato);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

int inorder_persona(nodoArbol* arbol)
{
    if(arbol)
    {
        preorder(arbol->izq);
        mostrar_persona(arbol->dato);
        preorder(arbol->der);
    }
}

int posorder_persona(nodoArbol* arbol)
{
    if(arbol)
    {
        preorder(arbol->izq);
        preorder(arbol->der);
        mostrar_persona(arbol->dato);
    }
}
*/

///



///fn auxiliares (grado 1 ,grado 2, raiz)

int es_grado_0(nodoArbol* arbol_nodo)///hoja
{
    if(arbol_nodo)
    {
        if(arbol_nodo->izq == NULL && arbol_nodo->der == NULL)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int es_grado_1(nodoArbol* arbol_nodo)///rama
{
    if(arbol_nodo)
    {
        if(arbol_nodo->izq == NULL && arbol_nodo->der != NULL)
        {
            return 1;
        }
        else if(arbol_nodo->izq != NULL && arbol_nodo->der == NULL)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int es_grado_2(nodoArbol* arbol_nodo)///raiz-sub raiz
{
    if(arbol_nodo)
    {
        if(arbol_nodo->izq != NULL && arbol_nodo->der != NULL)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

/// la busqueda
nodoArbol* buscar_arbol(nodoArbol* arbol,int dato)
{
    nodoArbol* rta=NULL;
    if(arbol)
    {
        if(arbol->dato == dato)
        {
            rta = arbol;
        }
        else
        {
            if(dato < arbol->dato)
            {
                rta = buscar_arbol(arbol->izq,dato);
            }
            else
            {
                rta = buscar_arbol(arbol->der,dato);
            }
        }
    }
    return rta;
}

/// BORRAR NODOS DE  ARBOL


void borrar_nodo_hoja(nodoArbol** arbol)
{
    free(arbol);
}

nodoArbol* borrar_nodo_rama(nodoArbol* arbol)
{
    nodoArbol* aux = arbol;

    if(arbol->der == NULL)
    {
        arbol=arbol->izq;
    }
    else
    {
        arbol=arbol->der;
    }
    free(aux);
    return arbol;
}

nodoArbol* borrar_nodo_raiz(nodoArbol* arbol)
{
    nodoArbol* aux = arbol;
    arbol=nodo_izquierda(arbol->der);
    free(aux);
    return arbol;
    /*
    nodoArbol* aux = arbol;
    arbol=nodo_derecha(arbol->izq);
    free(aux);
    return arbol;
    */
}

nodoArbol* nodo_izquierda(nodoArbol* arbol)
{
    if(arbol->izq!=NULL)
    {
        arbol=nodo_izquierda(arbol->izq);
    }
    return arbol;
}

nodoArbol* nodo_derecha(nodoArbol* arbol)
{
    if(arbol->der!=NULL)
    {
        arbol=nodo_derecha(arbol->der);
    }
    return arbol;
}

nodoArbol* borrar_nodoArbol(nodoArbol* arbol, int dato_a_borrar)
{
    if(arbol)
    {
        if(arbol->dato == dato_a_borrar)
        {
            if( es_grado_0(arbol) == 1 )
            {
                borrar_nodo_hoja(&arbol);
                arbol = NULL;
            }
            else if(es_grado_1(arbol) == 1 )
            {
                arbol = borrar_nodo_rama(arbol);
            }
            else
            {
                arbol = borrar_nodo_raiz(arbol);
            }
        }
        else
        {
            if(dato_a_borrar < arbol->dato)
            {
                arbol->izq = borrar_nodoArbol(arbol->izq,dato_a_borrar);
            }
            else
            {
                arbol->der = borrar_nodoArbol(arbol->der,dato_a_borrar);
            }
        }
    }

    return arbol;
}











































