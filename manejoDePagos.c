#include <stdio.h>
#include <stdlib.h>
#include "listasTDA.h"
#include "manejoDePagos.h"
#include "manejoDeClientes.h"
#include "ducktime.h"
#include "tipoUsuario.h"
#include <conio.h>
#include <stddef.h>
#include <string.h>

void imprimirMenuPagosEmpleado()
{
    printf("1- Generar factura de un cliente\n");
    printf("2- Mostrar todas las facturas\n");
    printf("0- Volver\n");
    mostrarLinea(40);
}


int mainPagosEmpleado()
{
    limpiarPantalla();
    nodoLista * nodoTmp = inicLista();
    nodoLista * lista = inicLista();
    int opcion;
    char decision = 's';
    char continuar = 's';
    while (tolower(decision) == 's' || tolower(decision) == 'y')
    {
        // Cada vez que se ejecute el menú refrescamos los datos de archivos
        marcoEsteticoSwitch("MANEJO DE PAGOS");
        imprimirMenuPagosEmpleado();
        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);
        reset:
        switch(opcion)
        {
        case 1:
            marcoEsteticoSwitch("MANEJO DE PAGOS > GENERAR FACTURA CLIENTE");
            while(tolower(continuar) == 's' || tolower(continuar) == 'y')
            {
                nodoTmp = crearNuevoPagoCliente();
                lista = agregarNodoInicio(lista, nodoTmp);
                printf("Desea generar otra factura de pago? (s/n)\n");
                fflush(stdin);
                scanf("%c", &continuar);
            }
            break;
        case 2:
            marcoEsteticoSwitch("MANEJO DE PAGOS > MOSTRAR TODOS LOS PAGOS");
            mostrarLista(lista);
            break;
        case 0:
            volverDependiendoTipoUsuario(tipoUsuario);
            break;
        default:
            printf("Opcion invalida, introduzca de nuevo la opcion: ");
            scanf("%d", &opcion);
            goto reset;
            break;
        }
    printf("\nDesea continuar? S/N: ");
    fflush(stdin);
    scanf("%c", &decision);
    limpiarPantalla();
    }
    return 0;
}



/// FUNCIONES

nodoLista * crearNuevoPagoCliente()
{
    nodoLista * temp = inicLista();
    char nombreYApellido[40];
    int DNI;
    float montoPago;
    int idMetodoPago;
    char metodoPago[25];
    tiempo fechaPago;
    printf("Ingrese el nombre y apellido del cliente: ");
    fflush(stdin);
    gets(nombreYApellido);

    printf("DNI del cliente: ");
    scanf("%d", &DNI);

    printf("Ingrese el monto del pago: ");
    scanf("%f", &montoPago);

    printf("Seleccione el metodo de pago:\n");
    printf("1. Efectivo\n2. Tarjeta de Credito\n3. Tarjeta de Debito\n4. Billetera Virtual\n");
    printf("Ingrese el número correspondiente al método de pago: ");
    scanf("%d", &idMetodoPago);

    printf("Ingrese el nombre del método de pago: ");
    fflush(stdin);
    gets(metodoPago);

    printf("Ingrese la fecha del pago (anio mes dia hora minuto): ");
    scanf("%d %d %d %d %d", &fechaPago.anio, &fechaPago.mes,
            &fechaPago.dia, &fechaPago.hora, &fechaPago.minuto);
    temp = crearNodoLista(DNI, nombreYApellido, montoPago, idMetodoPago, metodoPago, fechaPago);

    return temp;
}

void mostrarNodo(nodoLista *nodo)
{
    mostrarLinea(30);
    printf("Nombre y Apellido: %s\n", nodo->nombreYApellido);
    printf("DNI: %d\n", nodo->DNI);
    printf("Monto: %f\n", nodo->montoPago);
    printf("Metodo de Pago: %s\n", nodo->metodoPago);
    printf("ID Metodo de Pago: %d\n", nodo->idMetodoPago);
    printf("Fecha de Pago: %d/%d/%d %d:%d\n", nodo->fechaPago.dia, nodo->fechaPago.mes, nodo->fechaPago.anio,
           nodo->fechaPago.hora, nodo->fechaPago.minuto);
    printf("\n");
    mostrarLinea(30);
}

void mostrarLista(nodoLista * inicioLista)
{
    nodoLista *temp = inicioLista;
    while (temp != NULL)
    {
        mostrarNodo(temp);
        temp = temp->siguiente;
    }
}
