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



const char Registro_Pagos[]="registropagos.dat";

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
    printf("1. Efectivo\n2. Tarjeta de Credito\n3. Tarjeta de Debito\n4. Billetera Virtual\n");
    printf("Ingrese el número correspondiente al método de pago: ");
    scanf("%d", &pagoTemporal.idMetodoDePago);


    switch(pagoTemporal.idMetodoDePago)
    {
    case 1:
        strcpy(pagoTemporal.metodoDePago,"Efectivo");
        break;
    case 2:
        printf("ingrese Tarjeta y Banco: \n");
        fflush(stdin);
        gets(pagoTemporal.metodoDePago);
        break;
    case 3:
        printf("ingrese Tarjeta y Banco: \n");
        fflush(stdin);
        gets(pagoTemporal.metodoDePago);
        break;
    case 4:
        printf("ingrese Billetera: \n");
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
    printf("Monto: %f\n", nodo->pagoCliente.montoPago);
    printf("ID Metodo de Pago: %d\n", nodo->pagoCliente.idMetodoDePago);
    switch(nodo->pagoCliente.idMetodoDePago)
    {
    case 1:
        printf("Metodo de Pago: %s\n", "Efectivo");
        break;
    case 2:
        printf("Metodo de Pago: %s\n", nodo->pagoCliente.metodoDePago);
        break;
    case 3:
        printf("Metodo de Pago: %s\n", nodo->pagoCliente.metodoDePago);
        break;
    case 4:
        printf("Metodo de Pago: %s\n", nodo->pagoCliente.metodoDePago);
        break;
    }

    mostrarFecha(nodo->pagoCliente.fechaDePago);

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

