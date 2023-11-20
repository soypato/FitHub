#include "manejoInventario.h"
#include "stdlib.h"
#include "stdio.h"

int mainInventario()
{
    int op;
    int decision;
    pila p;
    inicPila(&p);

    while(decision == 's')
    {
        printf("1. CARGAR INVENTARIO\n");
        printf("2. MOSTRAR INVENTARIO\n");
        printf("3. AGREGAR OBJETO\n");
        printf("4. ELIMINAR OBJETO\n");
        printf("5. BUSCAR OBJETO\n");
        printf("6. MODIFICAR OBJETO\n");
        printf("7. SALIR\n");
        scanf("%d", &op);

        switch(op)
        {
            case 1:
                cargarInventario();
                break;
            case 2:
                mostrarPila(p);
                break;
            case 3:
                agregarObjeto();
                break;
            case 4:
                eliminarObjeto();
                break;
            case 5:
                buscarObjeto();
                break;
            case 6:
                modificarObjeto();
                break;
            case 7:
                decision = 'n';
                break;
            default:
                printf("OPCION INVALIDA\n");
                break;
        }
    }
    return 0;
}
nodoListaInventario * inicListaInventario()
{
    return NULL;
}

nodoListaInventario * crearNodoInventario(stObjeto objeto)
{
    nodoListaInventario * aux = (nodoListaInventario *)malloc(sizeof(nodoListaInventario));
    aux->objeto = objeto;
    aux->siguiente = NULL;
    return aux;
}

nodoListaInventario * agregarAlPrincipio(nodoListaInventario * lista, nodoListaInventario * nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo = lista;
        lista = nuevoNodo;
    }
    return lista;
}

nodoListaInventario * borrarPrimerNodo(nodoListaInventario * lista)
{
    nodoListaInventario * tmp = inicListaInventario();
    nodoListaInventario * rta = inicListaInventario();
    if(lista != NULL)
    {
        tmp = lista;
        tmp->siguiente = NULL;
        lista = lista->siguiente;
        free(tmp);
    }
    return rta;
}
nodoListaInventario * retornarPrimerNodo(nodoListaInventario * lista)
{
    nodoListaInventario * tmp = inicListaInventario();
    if(lista != NULL)
    {
        tmp = lista;
        tmp->siguiente = NULL;
    }
    return tmp;
}

int listaVacia(nodoListaInventario * lista)
{
    int rta = 0;
    if(lista == NULL)
    {
        rta = 1;
    }
    return rta;
}

/// ////// FUNCIONES MUESTREO

void mostrarNodoInventario(nodoListaInventario * nodo)
{
    mostrarUnObjeto(nodo->objeto);
}

void mostrarUnObjeto(stObjeto dato)
{
    mostrarLinea(30);
    printf("NOMBRE DEL OBJETO ............................ %s", &dato.nombreObjeto);
    printf("PESO EN KILOS     ............................ %f", &dato.pesoEnKg);
    printf("CANTIDAD ............................ %s", &dato.nombreObjeto);
    mostrarLinea(30);
}
/// ////// TDA PILAS CON LISTAS

int inicPila(pila * p)
{
    inicListaInventario(p->listaDePila);
}

int pilaVacia(pila p)
{
    int rta = 0;
    if(listaVacia(p.listaDePila) == 1)
    {
        rta = 1;
    }
    return rta;
}

stObjeto tope(pila p)
{
    nodoListaInventario * tmp = retornarPrimerNodo(p.listaDePila);
    stObjeto rta = tmp->objeto;
    return rta;
}

void mostrarPila(pila p)
{
    mostrarNodoInventario(p.listaDePila);
}

void apilar(pila * p, stObjeto dato)
{
    nodoListaInventario * nuevoNodo = crearNodoInventario(dato);
    p->listaDePila = agregarAlPrincipio(p->listaDePila, nuevoNodo);
}

stObjeto desapilar(pila * p)
{
    nodoListaInventario * tmp = retornarPrimerNodo(p->listaDePila);
    stObjeto rta = tmp->objeto;
    p->listaDePila = borrarPrimerNodo(p->listaDePila);
    return rta;
}

/// ////// FUNCIONES DE INVENTARIO

void cargarInventario()
{
    pila inventario;
    inicPila(&inventario);
    stObjeto objeto;
    char decision = 's';
    while(decision == 's')
    {
        printf("NOMBRE DEL OBJETO ............................ ");
        scanf("%s", &objeto.nombreObjeto);
        printf("PESO EN KILOS     ............................ ");
        scanf("%f", &objeto.pesoEnKg);
        printf("CANTIDAD ............................ ");
        scanf("%d", &objeto.cantidad);
        apilar(&inventario, objeto);
        printf("DESEA CONTINUAR CARGANDO OBJETOS? s/n");
        scanf("%c", &decision);
    }
}


void agregarObjeto()
{
    pila inventario;
    inicPila(&inventario);
    stObjeto objeto;
    printf("NOMBRE DEL OBJETO ............................ ");
    scanf("%s", &objeto.nombreObjeto);
    printf("PESO EN KILOS     ............................ ");
    scanf("%f", &objeto.pesoEnKg);
    printf("CANTIDAD ............................ ");
    scanf("%d", &objeto.cantidad);
    apilar(&inventario, objeto);
}

void eliminarObjeto()
{
    pila inventario;
    inicPila(&inventario);
    stObjeto objeto;
    char nombreObjeto[20];
    printf("NOMBRE DEL OBJETO ............................ ");
    scanf("%s", &nombreObjeto);
    while(!pilaVacia(inventario))
    {
        objeto = desapilar(&inventario);
        if(strcmp(objeto.nombreObjeto, nombreObjeto) != 0)
        {
            apilar(&inventario, objeto); // Si es distinto lo vuelo a apilar, sino queda desapilado
        }
        else
        {
            printf("OBJETO ELIMINADO");
        }
    }
}

void buscarObjeto()
{
    pila inventario;
    inicPila(&inventario);
    stObjeto objeto;
    char nombreObjeto[20];
    printf("NOMBRE DEL OBJETO ............................ ");
    scanf("%s", &nombreObjeto);
    while(!pilaVacia(inventario))
    {
        objeto = desapilar(&inventario);
        if(strcmp(objeto.nombreObjeto, nombreObjeto) != 0)
        {
            apilar(&inventario, objeto); // Si es distinto lo vuelo a apilar, sino queda desapilado
        }
        else
        {
            printf("OBJETO ENCONTRADO");
        }
    }
}

void modificarObjeto()
{
    pila inventario;
    inicPila(&inventario);
    stObjeto objeto;
    char nombreObjeto[20];
    printf("NOMBRE DEL OBJETO ............................ ");
    scanf("%s", &nombreObjeto);
    while(!pilaVacia(inventario))
    {
        objeto = desapilar(&inventario);
        if(strcmp(objeto.nombreObjeto, nombreObjeto) != 0)
        {
            apilar(&inventario, objeto); // Si es distinto lo vuelo a apilar, sino queda desapilado
        }
        else
        {
            printf("NOMBRE DEL OBJETO ............................ ");
            scanf("%s", &objeto.nombreObjeto);
            printf("PESO EN KILOS     ............................ ");
            scanf("%f", &objeto.pesoEnKg);
            printf("CANTIDAD ............................ ");
            scanf("%d", &objeto.cantidad);
            apilar(&inventario, objeto);
        }
    }
}
