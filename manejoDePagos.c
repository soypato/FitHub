#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <conio.h>
#include <string.h>

#include "listasTDA.h"
#include "manejoDePagos.h"
#include "manejoDeClientes.h"
#include "ducktime.h"
#include "tipoUsuario.h"



const char Registro_Pagos[]="registroPagos.dat";

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
    nodoListaPagos * nodoTmp = inicLista();
    nodoListaPagos * lista = inicLista();
    int opcion;
    char decision = 's';
    char continuar = 's';
    while (tolower(decision) == 's' || tolower(decision) == 'y')
    {
        // Cada vez que se ejecute el men� refrescamos los datos de archivos
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

                printf("Desea generar otra factura de pago? (s/n): ");
                fflush(stdin);
                scanf("%c", &continuar);
            }
            continuar = 's';
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

nodoListaPagos * crearNuevoPagoCliente()
{
    stPago pagoTemporal;
    nodoListaPagos * nodoTemp = inicLista();

    tiempo fechaPago;

    printf("Ingrese el nombre y apellido del cliente: ");
    fflush(stdin);
    gets(pagoTemporal.nombreApellido);

    printf("DNI del cliente: ");
    scanf("%d", &pagoTemporal.DNICliente);

    printf("Ingrese el monto del pago: ");
    scanf("%f", &pagoTemporal.montoPago);

    printf("Seleccione el metodo de pago:\n");
    mostrarLinea(120);
    printf("1. Efectivo\
           2. Tarjeta de Credito\
           3. Tarjeta de Debito\
           4. Billetera Virtual\n");
    mostrarLinea(120);
    printf("Ingrese el numero correspondiente al metodo de pago: ");
    scanf("%d", &pagoTemporal.idMetodoDePago);


    switch(pagoTemporal.idMetodoDePago)
    {
    case 1:
        strcpy(pagoTemporal.metodoDePago,"Efectivo");
        break;
    case 2:
        mostrarLinea(20);
        printf("Ingrese emisor de tarjeta y banco: \n");
        fflush(stdin);
        gets(pagoTemporal.metodoDePago);
        break;
    case 3:
        mostrarLinea(20);
        printf("Ingrese emisor de tarjeta y banco: \n");
        fflush(stdin);
        gets(pagoTemporal.metodoDePago);
        break;
    case 4:
        mostrarLinea(20);
        printf("Ingrese el nombre de la billetera virtual o fintech: \n");
        fflush(stdin);
        gets(pagoTemporal.metodoDePago);
        break;
    default:
        break;
    }

    printf("Ingrese la fecha del pago (anio mes dia hora minuto): ");
    scanf("%d %d %d %d %d", &fechaPago.anio, &fechaPago.mes, &fechaPago.dia, &fechaPago.hora, &fechaPago.minuto);

    pagoTemporal.fechaDePago = fechaPago;

    nodoTemp = crearNodoLista(pagoTemporal);

    return nodoTemp;
}


void mostrarNodo(nodoListaPagos *nodo)
{
    mostrarLinea(30);
    printf("Nombre y Apellido: %s\n", nodo->pagoCliente.nombreApellido);
    printf("DNI: %d\n", nodo->pagoCliente.DNICliente);
    printf("Monto: AR$%0.2f\n", nodo->pagoCliente.montoPago);
    printf("ID Metodo de Pago: %d\n", nodo->pagoCliente.idMetodoDePago);
    switch(nodo->pagoCliente.idMetodoDePago)
    {
    case 1:
        printf("Metodo de Pago: %s\n", "Efectivo");
        break;
    case 2:
        printf("Metodo de Pago: CREDITO / %s\n", nodo->pagoCliente.metodoDePago);
        break;
    case 3:
        printf("Metodo de Pago: DEBITO / %s\n", nodo->pagoCliente.metodoDePago);
        break;
    case 4:
        printf("Metodo de Pago: VIRTUAL / %s\n", nodo->pagoCliente.metodoDePago);
        break;
    }

            printf("Fecha de Pago: %d/%d/%d %d:%d\n", nodo->pagoCliente.fechaDePago.dia, nodo->pagoCliente.fechaDePago.mes, nodo->pagoCliente.fechaDePago.anio, nodo->pagoCliente.fechaDePago.hora, nodo->pagoCliente.fechaDePago.minuto);

    mostrarLinea(30);

}

void mostrarLista(nodoListaPagos * inicioLista)
{
    nodoListaPagos *temp = inicioLista;
    while (temp != NULL)
    {
        mostrarNodo(temp);
        temp = temp->siguiente;
    }
}


