#ifndef LISTASTDA_H_INCLUDED
#define LISTASTDA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listasTDA.h"
#include "manejoDeClientes.h"
#include "ducktime.h"

typedef struct nodoLista{
     float montoPago;
     int idMetodoPago; //1 para efectivo, 2 tarj credito, 3 tarj debito, 4 billetera virtual
     char metodoPago[20];
     int DNI;
     char nombreYApellido[40];
      tiempo fechaPago;
     struct nodoLista * siguiente;
} nodoLista;

/// PROTOTIPADOS

#endif // LISTASTDA_H_INCLUDED
