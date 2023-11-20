// manejoInventario.c

#include "manejoInventario.h"
#include <stdlib.h>
#include <stdio.h>


int mainInventario()
{
    int op;
    char decision = 's';
    pila p;
    inicPila(&p);

    while (decision == 's')
    {
        marcoEsteticoSwitch("INVENTARIO");
        printf("1. Cargar objeto\n");
        printf("2. Mostrar inventario\n");
        printf("3. Desapilar ultimo objeto\n");
        printf("4. Buscar objeto\n");
        printf("5. Modificar objeto\n");
        printf("0. Salir\n");
        mostrarLinea(30);
        printf("Su decision: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            marcoEsteticoSwitch("INVENTARIO > CARGAR OBJETO");
            apilarObjeto(&p);
            break;
        case 2:
            marcoEsteticoSwitch("INVENTARIO > MOSTRAR INVENTARIO");
            mostrarPila(&p);
            break;
        case 3:
            marcoEsteticoSwitch("INVENTARIO > DESAPILAR ULTIMO OBJETO");
            eliminarObjeto(&p);
            break;
        case 4:
            marcoEsteticoSwitch("INVENTARIO > BUSCAR OBJETO");
            buscarObjeto(&p);
            break;
        case 5:
            marcoEsteticoSwitch("INVENTARIO > MODIFICAR OBJETO");
            modificarObjeto(&p);
            break;
        case 0:
            decision = 'n';
            break;
        default:
            printf("OPCION INVALIDA\n");
            break;
        }

        if (decision == 'n') {
            printf("Saliendo del programa.\n");
        } else {
            printf("Seguir ejecutando? (s/n): ");
            fflush(stdin);
            scanf(" %c", &decision);
        }
    }

    return 0;
}

void inicPila(pila *p)
{
    p->listaDePila = NULL;
}

void apilarObjeto(pila *p)
{
    nodoListaInventario *nuevoNodo = (nodoListaInventario *)malloc(sizeof(nodoListaInventario));

    if (nuevoNodo == NULL)
    {
        printf("Error al asignar memoria para el nuevo objeto.\n");
        return;
    }

    printf("Ingrese el nombre del objeto: ");
    fflush(stdin);
    fgets(nuevoNodo->objeto.nombreObjeto, sizeof(nuevoNodo->objeto.nombreObjeto), stdin);

    printf("Ingrese el peso del objeto en Kg: ");
    scanf("%f", &nuevoNodo->objeto.pesoEnKg);

    printf("Ingrese la cantidad de objetos: ");
    scanf("%d", &nuevoNodo->objeto.cantidad);

    nuevoNodo->siguiente = p->listaDePila;
    p->listaDePila = nuevoNodo;

    printf("Objeto apilado correctamente.\n");
}

void mostrarPila(const pila *p)
{
    if (p->listaDePila == NULL)
    {
        printf("La pila esta vacia.\n");
        return;
    }

    nodoListaInventario *actual = p->listaDePila;

    while (actual != NULL)
    {
        printf("Nombre: %s\n", actual->objeto.nombreObjeto);
        printf("Peso: %.2f Kg\n", actual->objeto.pesoEnKg);
        printf("Cantidad: %d\n", actual->objeto.cantidad);
        printf("-------------------------\n");

        actual = actual->siguiente;
    }
}

void eliminarObjeto(pila *p)
{
    if (p->listaDePila == NULL)
    {
        printf("La pila esta vacia, no hay objetos para desapilar.\n");
        return;
    }

    nodoListaInventario *temp = p->listaDePila;
    p->listaDePila = temp->siguiente;
    free(temp);

    printf("Objeto desapilado correctamente.\n");
}

void buscarObjeto(const pila *p)
{
    if (p->listaDePila == NULL)
    {
        printf("La pila esta vacia, no hay objetos para buscar.\n");
        return;
    }

    char nombreBuscado[50];
    printf("Ingrese el nombre del objeto a buscar: ");
    fflush(stdin);
    fgets(nombreBuscado, sizeof(nombreBuscado), stdin);

    nodoListaInventario *actual = p->listaDePila;

    while (actual != NULL)
    {
        if (strcmp(actual->objeto.nombreObjeto, nombreBuscado) == 0)
        {
            printf("Objeto encontrado:\n");
            printf("Nombre: %s\n", actual->objeto.nombreObjeto);
            printf("Peso: %.2f Kg\n", actual->objeto.pesoEnKg);
            printf("Cantidad: %d\n", actual->objeto.cantidad);
            return;
        }

        actual = actual->siguiente;
    }

    printf("Objeto no encontrado en el inventario.\n");
}

void modificarObjeto(pila *p)
{
    if (p->listaDePila == NULL)
    {
        printf("La pila esta vacia, no hay objetos para modificar.\n");
        return;
    }

    char nombreModificar[50];
    printf("Ingrese el nombre del objeto a modificar: ");
    fflush(stdin);
    fgets(nombreModificar, sizeof(nombreModificar), stdin);

    nodoListaInventario *actual = p->listaDePila;

    while (actual != NULL)
    {
        if (strcmp(actual->objeto.nombreObjeto, nombreModificar) == 0)
        {
            printf("Ingrese el nuevo peso del objeto en Kg: ");
            scanf("%f", &actual->objeto.pesoEnKg);

            printf("Ingrese la nueva cantidad de objetos: ");
            scanf("%d", &actual->objeto.cantidad);

            printf("Objeto modificado correctamente.\n");
            return;
        }

        actual = actual->siguiente;
    }

    printf("Objeto no encontrado en el inventario.\n");
}
