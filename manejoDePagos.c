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
    printf("3- Mostrar facturas filtradas por Monto\n");
    printf("4- Mostrar facturas filtradas por DNI\n");
    printf("5- Mostrar facturas dadas de baja\n");
    printf("6- Quitar una factura\n");
    printf("7- Reactivar una factura\n");
    printf("0- Volver\n");
    mostrarLinea(40);
}


int mainPagosClientes()
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
            guardarFacturasEnArchivo(lista);
            continuar = 's';
            break;
        case 2:
            marcoEsteticoSwitch("MANEJO DE PAGOS > MOSTRAR TODAS LAS FACTURAS");
            mostrarFacturasDesdeArchivo();
            break;
        case 3:
            marcoEsteticoSwitch("MANEJO DE PAGOS > MOSTRAR FACTURAS POR MONTO");
            mostrarFacturasDesdeArchivoOrdenadasPorMonto();
            break;
        case 4:
            marcoEsteticoSwitch("MANEJO DE PAGOS > MOSTRAR FACTURAS POR DNI");
            mostrarFacturasDesdeArchivoOrdenadasPorDNI();
            break;
        case 5:
            marcoEsteticoSwitch("MANEJO DE PAGOS > MOSTRAR FACTURAS DADAS DE BAJA");
            mostrarFacturasDadasDeBaja();
            break;
        case 6:
            marcoEsteticoSwitch("MANEJO DE PAGOS > QUITAR UNA FACTURA");
            darDeBajaUnaFactura();
            break;
        case 7:
            marcoEsteticoSwitch("MANEJO DE PAGOS > REACTIVAR UNA FACTURA");
            reactivarFactura();
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
    pagoTemporal.bajaPasiva = 0;

    nodoTemp = crearNodoLista(pagoTemporal);

    return nodoTemp;
}


void mostrarNodo(nodoListaPagos *nodo)
{

    mostrarLinea(45);
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

    mostrarLinea(45);

}

void guardarFacturasEnArchivo(nodoListaPagos *lista)
{
    FILE *archivo = fopen(Registro_Pagos, "ab"); // Abre el archivo en modo de agregar binario

    if (archivo != NULL)
    {
        nodoListaPagos *temp = lista;

        while (temp != NULL)
        {
            fwrite(&(temp->pagoCliente), sizeof(stPago), 1, archivo);
            temp = temp->siguiente;
        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para guardar las facturas.\n");
    }
}

void mostrarLista(nodoListaPagos * inicioLista)
{
    nodoListaPagos *temp = inicioLista;
    while (temp != NULL)
    {
        if (temp->pagoCliente.bajaPasiva == 0)
        {
            mostrarNodo(temp);
        }
        temp = temp->siguiente;
    }
}

void mostrarFacturasDesdeArchivo()
{
    FILE *archivo = fopen(Registro_Pagos, "rb"); // Abre el archivo en modo de leer binario

    if (archivo != NULL)
    {
        stPago factura;
        while (fread(&factura, sizeof(stPago), 1, archivo) > 0)
        {
            if (factura.bajaPasiva == 0)
            {
                mostrarNodo(crearNodoLista(factura));
            }
        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para leer las facturas.\n");
    }
}

void mostrarFacturasDesdeArchivoOrdenadasPorMonto()
{
    FILE *archivo = fopen(Registro_Pagos, "rb"); // Abre el archivo en modo de leer binario

    if (archivo != NULL)
    {
        nodoListaPagos *lista = inicLista();
        stPago factura;

        // Leer las facturas y agregarlas a la lista
        while (fread(&factura, sizeof(stPago), 1, archivo) > 0)
        {
            nodoListaPagos *nuevoNodo = crearNodoLista(factura);
            lista = agregarNodoOrdenadoPorMonto(lista, nuevoNodo);
        }

        // Mostrar las facturas ordenadas por monto
        mostrarLista(lista);

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para leer las facturas.\n");
    }
}

void mostrarFacturasDesdeArchivoOrdenadasPorDNI()
{
    FILE *archivo = fopen(Registro_Pagos, "rb"); // Abre el archivo en modo de leer binario

    if (archivo != NULL)
    {
        nodoListaPagos *lista = inicLista();
        stPago factura;

        // Leer las facturas y agregarlas a la lista
        while (fread(&factura, sizeof(stPago), 1, archivo) > 0)
        {
            nodoListaPagos *nuevoNodo = crearNodoLista(factura);
            lista = agregarNodoOrdenadoPorDNI(lista, nuevoNodo);
        }

        // Mostrar las facturas ordenadas por monto
        mostrarLista(lista);

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para leer las facturas.\n");
    }
}


void darDeBajaUnaFactura()
{
    FILE *archivo = fopen(Registro_Pagos, "rb+"); // Abre el archivo en modo de leer y escribir binario

    if (archivo != NULL)
    {
        stPago factura;
        int dniBuscar;

        // Solicitar al usuario el DNI de la factura a modificar
        printf("Ingrese el DNI del cliente de la factura a quitar: ");
        scanf("%d", &dniBuscar);

        // Buscar la factura en el archivo
        int encontrado = 0;
        while (fread(&factura, sizeof(stPago), 1, archivo) > 0)
        {
            if (factura.DNICliente == dniBuscar)
            {
                encontrado = 1;

                // Mostrar la factura actual
                printf("Factura encontrada:\n");
                mostrarNodo(crearNodoLista(factura));

                // Solicitar al usuario si desea dar de baja la factura
                int opcion;
                printf("Desea dar de baja esta factura? (1: Si / 0: No): ");
                scanf("%d", &opcion);

                // Modificar el campo bajaPasiva según la opción del usuario
                if (opcion == 1)
                {
                    factura.bajaPasiva = 1;
                    fseek(archivo, -sizeof(stPago), SEEK_CUR); // Retrocede un registro para escribir sobre el registro actual
                    fwrite(&factura, sizeof(stPago), 1, archivo);
                    printf("Factura dada de baja exitosamente.\n");
                }
                else
                {
                    printf("Operacion cancelada. La factura no fue modificada.\n");
                }

                break; // No es necesario seguir buscando
            }
        }

        if (!encontrado)
        {
            printf("Factura no encontrada.\n");
        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para modificar la factura.\n");
    }
}


void reactivarFactura()
{
    FILE *archivo = fopen(Registro_Pagos, "rb+"); // Abre el archivo en modo de leer y escribir binario

    if (archivo != NULL)
    {
        stPago factura;
        int dniBuscar;

        // Solicitar al usuario el DNI de la factura a reactivar
        printf("Ingrese el DNI del cliente de la factura a reactivar: ");
        scanf("%d", &dniBuscar);

        // Buscar la factura en el archivo
        int encontrado = 0;
        while (fread(&factura, sizeof(stPago), 1, archivo) > 0)
        {
            if (factura.DNICliente == dniBuscar)
            {
                encontrado = 1;

                // Mostrar la factura actual
                printf("Factura encontrada:\n");
                mostrarNodo(crearNodoLista(factura));

                // Solicitar al usuario si desea reactivar la factura
                int opcion;
                printf("Desea reactivar esta factura? (1: Si / 0: No): ");
                scanf("%d", &opcion);

                // Modificar el campo bajaPasiva según la opción del usuario
                if (opcion == 1)
                {
                    factura.bajaPasiva = 0;
                    fseek(archivo, -sizeof(stPago), SEEK_CUR); // Retrocede un registro para escribir sobre el registro actual
                    fwrite(&factura, sizeof(stPago), 1, archivo);
                    printf("Factura reactivada exitosamente.\n");
                }
                else
                {
                    printf("Operacion cancelada. La factura no fue modificada.\n");
                }

                break; // No es necesario seguir buscando
            }
        }

        if (!encontrado)
        {
            printf("Factura no encontrada.\n");
        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para modificar la factura.\n");
    }
}


void mostrarFacturasDadasDeBaja()
{
    FILE *archivo = fopen(Registro_Pagos, "rb"); // Abre el archivo en modo de leer binario

    if (archivo != NULL)
    {
        stPago factura;
        int contadorFacturas = 0;

        while (fread(&factura, sizeof(stPago), 1, archivo) > 0)
        {
            if (factura.bajaPasiva == 1)
            {
                mostrarNodo(crearNodoLista(factura));
                contadorFacturas++;
            }
        }

        if (contadorFacturas == 0)
        {
            printf("No hay facturas dadas de baja en el archivo.\n");
        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para leer las facturas.\n");
    }
}
