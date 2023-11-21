#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manejoEmpleado.h"
#include "controlAdmin.h"
#include "const.h"
#include "tipoUsuario.h"

void controlAdmin()
{
    int decision;
    do
    {
        marcoEsteticoSwitch("CONTROL DE ADMINISTRADOR");
        reset:
        mostrarLinea(40);
        printf("1- Manejo de clientes\n");
        printf("2- Manejo de pagos\n"); /// aca decía: "manejo de empleados" pero lo podríamos revisar :)
        printf("3- Manejo de empleados\n");
        printf("4- Manejo de inventario\n");
        printf("5- Manejo de clientes (version publica)\n");
        printf("0- Salir\n");
        mostrarLinea(40);

        printf("Su decision: ");
        fflush(stdin);
        scanf(" %d", &decision);

        switch (decision)
        {
        case 0:
            controlInicio();
            break;
        case 1:
            mainClientes();
            limpiarPantalla();
            break;
        case 2:
            mainPagosClientes();
            limpiarPantalla();
            break;
        case 3:
            mainEmpleados();
            limpiarPantalla();
            break;
        case 4:
            mainInventario();
            limpiarPantalla();
            break;
        case 5:
            controlCliente();
            limpiarPantalla();
            break;
        default:
            limpiarPantalla(); /// maybe???
            printf("Opcion invalida\n");
            goto reset;
            break;
        }
    }
    while (decision != 0);
}
