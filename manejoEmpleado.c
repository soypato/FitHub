///sector manejo de empleados

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "ducktime.h"
#include "manejoDeClientes.h"
#include "const.h"
#include "tipoUsuario.h"

int mainEmpleados
()
{
    limpiarPantalla();
    int op=0;
    char decision = 's';
    while(tolower(decision) == 's')
    {
        //menu
        //carga de op

        reset:
        switch(op)
        {
        case 0:
            volverDependiendoTipoUsuario(tipoUsuario);
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            printf("Opcion invalida, introduzca de nuevo la opcion: ");
            scanf("%d", &op);
            goto reset;
            break;
        }
    printf("\nDesea continuar? S/N: ");fflush(stdin);scanf("%c", &decision);
    limpiarPantalla();
    }
    return 0;
}
