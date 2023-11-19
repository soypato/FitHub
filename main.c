#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
#include "manejoDeClientes.h"
#include "controlEmpleado.h"
#include "ducktime.h"
#include "tipoUsuario.h"
#include <conio.h>


/// PROTOTIPADOS
void menuPrincipal();
void limpiarPantalla();
void controlInicio();
int inicioSesion();
void controlEmpleado();
void marcoEsteticoSwitch(char texto[]);
void mostrarLinea(int cantidad);

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

void marcoEsteticoSwitch(char texto[])
{
    limpiarPantalla();
    mostrarLinea(20);
    printf("%s\n", texto);
    mostrarLinea(20);
}

void mostrarLinea(int cantidad)
{
    for(int i = 0; i < cantidad; i++)
    {
        printf("-");
    }
    printf("\n");
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

int inicioSesion()
{
    int tmpClave = 0;
    int loginExitoso = 0;
    limpiarPantalla();
    /// hacer funcino que muestre FITHUB
    restart:
    printf("\n\n>> Introduzca la contrasena: ");
    scanf("%d", &tmpClave);
    limpiarPantalla();

    // Dependiendo lo que pusimos en la clave, nos mostrará un menú u otro

    switch (tmpClave)
    {
    case claveSalir://0
        return 0;
        break;
    case claveAdmin://1
        tipoUsuario = 1;
        controlAdmin();
        break;
    case claveEmpleado:// 2
        tipoUsuario = 2;
        controlEmpleado();
        break;
    case claveCliente://3
        tipoUsuario = 3;
        controlCliente();
        break;
    default:
        printf("Clave incorrecta, presiona enter para intentar de nuevo\n");
        getchar(); // Captura el Enter previo al scanf
        getchar(); // Espera a que el usuario presione Enter para continuar
        limpiarPantalla();
        goto restart;
        break;
    }
    return 0;
}
