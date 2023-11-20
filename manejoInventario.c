/// manejoInventario.c: es un archivo / lista que tiene comportamiento de PILA
/// es decir,

#include "manejoInventario.h"
#include <stdlib.h>
#include <stdio.h>

int mainInventario()
{
    int op;
    char decision = 's';
    pila p;
    inicPila(&p);
    cargarDesdeArchivo(&p); // Cargar datos desde el archivo al iniciar

    while (decision == 's')
    {
        marcoEsteticoSwitch("INVENTARIO");
        printf("1. Cargar objeto\n");
        printf("2. Mostrar inventario\n");
        printf("3. Desapilar ultimo objeto\n");
        printf("4. Buscar objeto\n");
        printf("5. Modificar objeto\n");
        printf("6. Recuento total\n");
        printf("0. Salir\n");
        mostrarLinea(50);
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
        case 6:
            marcoEsteticoSwitch("INVENTARIO > MOSTRAR STOCK TOTAL");
            mostrarStockTotal(&p);
            break;
        case 0:
            decision = 'n';
            break;
        default:
            printf("OPCION INVALIDA\n");
            break;
        }

        if (decision == 'n')
        {
            printf("Saliendo del programa.\n");
        }
        else
        {
            printf("Seguir ejecutando? (s/n): ");
            fflush(stdin);
            scanf(" %c", &decision);
        }
    }

    guardarEnArchivo(&p); // Guardar datos en el archivo al salir
    return 0;
}

void cargarDesdeArchivo(pila *p)
{
    FILE *archivo = fopen("manejoInventario.dat", "rb");
    if (archivo == NULL)
    {
        // El archivo aún no existe, no hay datos que cargar
        return;
    }

    stObjeto buffer;
    while (fread(&buffer, sizeof(stObjeto), 1, archivo) == 1)
    {
        nodoListaInventario *nuevoNodo = (nodoListaInventario *)malloc(sizeof(nodoListaInventario));
        if (nuevoNodo == NULL)
        {
            fclose(archivo);
            printf("Error al asignar memoria para el nuevo objeto.\n");
        }
        nuevoNodo->objeto = buffer;
        nuevoNodo->siguiente = p->listaDePila;
        p->listaDePila = nuevoNodo;
    }

    fclose(archivo);
}

void guardarEnArchivo(const pila *p)
{
    FILE *archivo = fopen("manejoInventario.dat", "wb");
    if (archivo == NULL)
    {
        printf("Error al abrir o crear el archivo para escritura.\n");
        return;
    }

    nodoListaInventario *actual = p->listaDePila;

    while (actual != NULL)
    {
        fwrite(&(actual->objeto), sizeof(stObjeto), 1, archivo);
        actual = actual->siguiente;
    }

    fclose(archivo);
}

void agregarAlArchivo(const stObjeto *objeto)
{
    FILE *archivo = fopen("manejoInventario.dat", "ab");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo para agregar objeto.\n");
        return;
    }

    fwrite(objeto, sizeof(stObjeto), 1, archivo);

    fclose(archivo);
}

void eliminarDelArchivo(const char *nombreObjeto)
{
    FILE *archivo = fopen("manejoInventario.dat", "rb");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo para eliminar objeto.\n");
        return;
    }

    FILE *temporal = fopen("temp.dat", "wb");
    if (temporal == NULL)
    {
        fclose(archivo);
        printf("Error al abrir el archivo temporal.\n");
        return;
    }

    stObjeto buffer;

    while (fread(&buffer, sizeof(stObjeto), 1, archivo) == 1)
    {
        if (strcmp(buffer.nombreObjeto, nombreObjeto) != 0)
        {
            fwrite(&buffer, sizeof(stObjeto), 1, temporal);
        }
    }

    fclose(archivo);
    fclose(temporal);

    /// NO SE ASUSTEN! Esta función parte de stdio
    remove("manejoInventario.dat");
    rename("temp.dat", "manejoInventario.dat");
}

void modificarEnArchivo(const stObjeto *objetoModificado)
{
    FILE *archivo = fopen("manejoInventario.dat", "rb");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo para modificar objeto.\n");
        return;
    }

    FILE *temporal = fopen("temp.dat", "wb");
    if (temporal == NULL)
    {
        fclose(archivo);
        printf("Error al abrir el archivo temporal.\n");
        return;
    }

    stObjeto buffer;

    while (fread(&buffer, sizeof(stObjeto), 1, archivo) == 1)
    {
        if (strcmp(buffer.nombreObjeto, objetoModificado->nombreObjeto) == 0)
        {
            fwrite(objetoModificado, sizeof(stObjeto), 1, temporal);
        }
        else
        {
            fwrite(&buffer, sizeof(stObjeto), 1, temporal);
        }
    }

    fclose(archivo);
    fclose(temporal);

    // Renombrar el archivo temporal como el archivo original
    remove("manejoInventario.dat");
    rename("temp.dat", "manejoInventario.dat");

    printf("Objeto modificado en el archivo: %s\n", objetoModificado->nombreObjeto);
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

    agregarAlArchivo(&(nuevoNodo->objeto)); // Agregar al archivo en tiempo real
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

    // Eliminar del archivo en tiempo real
    eliminarDelArchivo(temp->objeto.nombreObjeto);

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

            modificarEnArchivo(&(actual->objeto)); // Modificar en el archivo en tiempo real
            printf("Objeto modificado correctamente.\n");
            return;
        }

        actual = actual->siguiente;
    }

    printf("Objeto no encontrado en el inventario.\n");
}

void mostrarStockTotal(const pila *p)
{
    if (p->listaDePila == NULL)
    {
        printf("La pila está vacía, no hay objetos para mostrar.\n");
        return;
    }

    printf("+---------------------+---------------------+---------------------+\n");
    printf("| %-19s | %-19s | %-19s |\n", "NOMBRE", "CANTIDAD", "ACUMULADO");
    printf("+---------------------+---------------------+---------------------+\n");

    nodoListaInventario *actual = p->listaDePila;

    int acumulado = 0;

    while (actual != NULL)
    {
        acumulado += actual->objeto.cantidad;

        printf("| %-19s | %-19d | %-19d |\n", actual->objeto.nombreObjeto, actual->objeto.cantidad, acumulado);

        actual = actual->siguiente;
    }

    printf("+---------------------+---------------------+---------------------+\n");

    // Imprimir el total debajo de la tabla
    printf("TOTAL: %d\n", acumulado);
}
