#ifndef PAGOS_H_INCLUDED
#define PAGOS_H_INCLUDED
#include "ducktime.h"

typedef struct nodoLista
{
    float montoPago;
    int idMetodoDePago; /// 1 para efectivo, 2 tarj credito, 3 tarj debito, 4 billeteras virtuales
    /* cuando hagamos la funcion de alta del usuario poner, un if metodo de pago == 1 strcpy,
    para despues asignarle el metodo de pago que haya elegido segun el numero */
    char metodoDePago[20]; /// efectivo, bill virtual, tarjeta credito, tarjeta debito
    tiempo fechaDePago;
    struct nodoLista* siguiente;
} nodoLista;



#endif // PAGOS_H_INCLUDED
