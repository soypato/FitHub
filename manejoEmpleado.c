///sector manejo de empleados

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "ducktime.h"
#include "manejoDeClientes.h"
#include "const.h"
#include "tipoUsuario.h"

void imprimirMenu()
{
    printf("1- Alta de cliente\n");
    printf("2- Baja y restauracion de cliente\n");
    printf("3- Modificacion de cliente\n");
    printf("4- Listado de planes + clientes\n");
    printf("5- Buscar cliente\n");
    printf("6- Mostrar clientes de un plan\n");
    printf("7- Calcular IMC (indice de masa corporal)\n");
    printf("0- Ir a atras\n");
    mostrarLinea(40);

}

int mainClientes()
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
