#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED

typedef struct nodoArbol{
    int dato;
    struct nodoArbol* izq;
    struct nodoArbol* der;
}nodoArbol;

///prototipado
nodoArbol* inicArbolB();
nodoArbol* crear_nodoArbol(int dato);
nodoArbol* insertar_en_arbol(nodoArbol* arbol, nodoArbol* nuevo);
nodoArbol* cargar_arbol(nodoArbol* arbol);
void mostrar_nodoArbol(nodoArbol* arbol);/// para int
void preorder(nodoArbol* arbol);
void inorder(nodoArbol* arbol);
void posorder(nodoArbol* arbol);
int es_grado_0(nodoArbol* arbol_nodo);
int es_grado_1(nodoArbol* arbol_nodo);
int es_grado_2(nodoArbol* arbol_nodo);
nodoArbol* buscar_arbol(nodoArbol* arbol,int dato);
void borrar_nodo_hoja(nodoArbol** arbol);
nodoArbol* borrar_nodo_rama(nodoArbol* arbol);
nodoArbol* borrar_nodo_raiz(nodoArbol* arbol);
nodoArbol* nodo_izquierda(nodoArbol* arbol);
nodoArbol* nodo_derecha(nodoArbol* arbol);
nodoArbol* borrar_nodoArbol(nodoArbol* arbol, int dato_a_borrar);




#endif // ARBOLES_H_INCLUDED
