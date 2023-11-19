#ifndef MANEJOEMPLEADO_H_INCLUDED
#define MANEJOEMPLEADO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listasTDA.h"
#include "manejoDePagos.h"
#include "manejoDeClientes.h"
#include "ducktime.h"
#include "manejoEmpleado.h"

typedef struct{
    char nombreYApellido[40];
    int legajo;
    int edad;
    int DNI;
    char categoria[30];
    int bajaPasiva;
}stEmpleado;

typedef struct nodoListaEmpleados{
    stEmpleado empleado;
    struct nodoListaEmpleados * siguiente;
}nodoListaEmpleados;

/// PROTOTIPADOS
nodoListaEmpleados * inicListaEmpleados ();
nodoListaEmpleados * crearNodoListaEmpleados (stEmpleado empleado);
nodoListaEmpleados * agregarNodoInicioEmpleado(nodoListaEmpleados * lista, nodoListaEmpleados * nuevo);
nodoListaEmpleados * agregarNodoOrdenadoPorNomYApeEmpleado(nodoListaEmpleados * lista, nodoListaEmpleados * nuevo);
nodoListaEmpleados * agregarNodoOrdenadoPorLegajoEmpleado(nodoListaEmpleados *lista, nodoListaEmpleados *nuevoNodo);
nodoListaEmpleados * agregarNodoOrdenadoPorDNIEmpleado(nodoListaEmpleados *lista, nodoListaEmpleados *nuevoNodo);
nodoListaEmpleados *agregarNodoOrdenadoPorEdadEmpleado(nodoListaEmpleados *lista, nodoListaEmpleados *nuevoNodo);


/// PROTOTIPADOS MANEJODEEMPLADO

nodoListaEmpleados * crearNuevoEmpleado();
void mostrarNodoEmpleado(nodoListaEmpleados *nodo);
void mostrarListaEmpleados(nodoListaEmpleados *lista);
void guardarEmpleadosEnArchivo(nodoListaEmpleados * lista);
void mostrarEmpleadosDesdeArchivo();
void mostrarEmpleadosDesdeArchivoOrdenadasPorLegajo();
void mostrarEmpleadosDesdeArchivoOrdenadasPorDNI();
void mostrarEmpleadosDesdeArchivoOrdenadasPorEdad();
void darDeBajaUnEmpleado();
void reactivarEmpleado();
void mostrarEmpleadosDadosDeBaja();
void modificarEmpleado();



#endif // MANEJOEMPLEADO_H_INCLUDED
