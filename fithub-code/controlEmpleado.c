#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manejoDeClientes.h"
#include "controlEmpleado.h"
#include "const.h"
#include "tipoUsuario.h"


void controlEmpleado()
{
    int decision;
    do
    {
        marcoEsteticoSwitch("CONTROL DE EMPLEADO");
        reset:
        mostrarLinea(40);
        printf("1- Manejo de clientes\n");
        printf("2- Manejo de pagos\n");
        printf("3- Ir al inventario\n");
        printf("0- Atras\n");

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
            mainInventario();
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




