#ifndef LISTASTDA_H_INCLUDED
#define LISTASTDA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listasTDA.h"
#include "manejoDePagos.h"
#include "manejoDeClientes.h"
#include "ducktime.h"

typedef struct
{
    int DNICliente;
    char nombreApellido[30];
    float montoPago;
    int idMetodoDePago; /// 1 para efectivo, 2 tarj credito, 3 tarj debito, 4 billeteras virtuales
    char metodoDePago[20]; /// efectivo, bill virtual, tarjeta credito, tarjeta debito
    int bajaPasiva;
    tiempo fechaDePago;
}stPago;

/* cuando hagamos la funcion de alta del usuario poner, un if metodo de pago == 1 strcpy,
    para despues asignarle el metodo de pago que haya elegido segun el numero */

typedef struct nodoListaPagos{
    stPago pagoCliente;
    struct nodoListaPagos* siguiente;
}nodoListaPagos;

/// PROTOTIPADOS
nodoListaPagos * inicLista ();
nodoListaPagos * crearNodoLista (stPago pagoTemporal);
nodoListaPagos * agregarNodoInicio(nodoListaPagos * lista, nodoListaPagos * nuevo);
nodoListaPagos * agregarNodoOrdenadoPorNomYApe(nodoListaPagos * lista, nodoListaPagos * nuevo);
nodoListaPagos * agregarNodoOrdenadoPorMonto(nodoListaPagos *lista, nodoListaPagos *nuevoNodo);
nodoListaPagos * agregarNodoOrdenadoPorDNI(nodoListaPagos *lista, nodoListaPagos *nuevoNodo);

/// PROTOTIPADOS MANEJODEPAGOS
void imprimirMenuPagosEmpleado();
int mainPagosEmpleado();
nodoListaPagos * crearNuevoPagoCliente();
void mostrarNodo(nodoListaPagos *nodo);
void mostrarLista(nodoListaPagos* inicioLista);
void guardarFacturasEnArchivo(nodoListaPagos *lista);
void mostrarFacturasDesdeArchivo();
void mostrarFacturasDesdeArchivoOrdenadasPorMonto();
void mostrarFacturasDesdeArchivoOrdenadasPorDNI();
void darDeBajaUnaFactura();
void reactivarFactura();
void mostrarFacturasDadasDeBaja();


#endif // LISTASTDA_H_INCLUDED
