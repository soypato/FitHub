#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
#include "clientes.h"
#include "ducktime.h"
#include "tipoUsuario.h"

/// PROTOTIPADOS
void menuPrincipal();
void limpiarPantalla();
void controlInicio();
void inicioSesion();
void controlEmpleado();


int main()
{
    controlInicio();
    return 0;
}

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void controlInicio()
{
    char continuar = 1;

    while (continuar)
    {
        inicioSesion(); // login siempre, PRIMER LOGIN AL EJECUTAR
        printf("Que desea hacer? 1: Ir a inicio de sesion / 0: Cerrar programa): ");
        scanf("%d", &continuar);
        limpiarPantalla();
    }

}

void inicioSesion()
{
    int tmpClave = 0;
    int loginExitoso = 0;
    limpiarPantalla();
    printf("\n\nIntroduzca la contrasena: ");
    scanf("%d", &tmpClave);
    limpiarPantalla();

    // Dependiendo lo que pusimos en la clave, nos mostrará un menú u otro
    switch (tmpClave)
    {
    case claveEmpleado:
        printf("=== SECCION EMPLEADO ===\n" );
        tipoUsuario = 1;  // Mozo
        controlEmpleado();
        break;
    default:
        printf("Clave incorrecta, presiona enter para intentar de nuevo\n");
        getchar(); // Captura el Enter previo al scanf
        getchar(); // Espera a que el usuario presione Enter para continuar
        inicioSesion();
        break;
    }
}

void controlEmpleado()
{
    int decision;
    do
    {
        reset:
        mostrarLinea(40);
        printf("1- Menu de Empleado\n");
        printf("2- Menu de Clientes\n");
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
