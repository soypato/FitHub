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
        printf("2- Menu de \n"); /// aca dec�a: "manejo de empleados" pero lo podr�amos revisar :)
        printf("0- Salir\n");
        mostrarLinea(40);


        printf("Su decision: ");
        fflush(stdin);
        scanf(" %d", &decision);

        switch (decision)
        {
        case 1:
            mainClientes();
            limpiarPantalla();
            break;
        case 0:
            controlInicio();
            break;
        default:
            limpiarPantalla();
            printf("Opcion invalida\n");
            goto reset;
            break;
        }
    }
    while (decision != 0);
}