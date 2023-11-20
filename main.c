#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "windows.h"
#include "const.h"
#include "manejoDeClientes.h"
#include "controlEmpleado.h"
#include "ducktime.h"
#include "tipoUsuario.h"
#include <conio.h>
#include <stdbool.h>
#include "manejoInventario.h"

/// PROTOTIPADOS
void menuPrincipal();
void limpiarPantalla();
void controlInicio();
void inicioSesion();
void controlEmpleado();
void marcoEsteticoSwitch(char texto[]);
void mostrarLinea(int cantidad);
void gotoxy(int x, int y);

void ocultarCursor()
{
    printf("\e[?25l");
}

void activarCursor()
{
    printf("\e[?25h");
}

void gotoxy(int x, int y)
{
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y= y;
	SetConsoleCursorPosition(hcon,dwPos);
}

void recuadro(int xs, int ys, int xi, int yi)
{
    int i;

    for(i = xs; i<= xi; i++)
    {
        gotoxy(i, ys); printf("%c", 196);
        gotoxy(i, yi); printf("%c", 196);
    }

    for(i = ys; i<= yi; i++)
    {
        gotoxy(xs, i); printf("%c", 179);
        gotoxy(xi, i); printf("%c", 179);
    }
    gotoxy(xs, ys); printf("%c", 218);
    gotoxy(xi, yi); printf("%c", 217);
    gotoxy(xi, ys); printf("%c", 191);
    gotoxy(xs, yi); printf("%c", 192);
}

void centrarTexto(char *texto, int y)
{
    int longitud = strlen(texto);
    gotoxy(40-(longitud/2),y); printf(texto);
}

int main()
{
    system("COLOR 04");
    limpiarPantalla();
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
    mostrarLinea(25);
    printf("%s\n", texto);
    mostrarLinea(25);
}

void mostrarLinea(int cantidad)
{
    for(int i = 0; i < cantidad; i++)
    {
        printf("-");
    }
    printf("\n");
}


void inicioSesion()
{
    int i;
    int tmpClave = 0;
    int loginExitoso = 0;
    limpiarPantalla();
    /// hacer funcino que muestre FITHUB
    restart:
    recuadro(0, 0, 79, 24);
    recuadro(1, 1, 78, 3);
    centrarTexto("S I S T E M A    F I T H U B", 2);
    gotoxy(2, 5);printf(">> Introduzca la clave\n  (o marque 3 en caso de que sea cliente): ");
    scanf("%d", &tmpClave);
    ocultarCursor();
    centrarTexto("C A R G A N D O...",21);
    for(i = 3; i <= 76; i++)
    {
        gotoxy(i, 23); printf("%c",177);
    }



    for(i = 3; i <= 76; i++)
    {
        gotoxy(i, 23); printf("%c",219);
        Sleep(15);
    }
    gotoxy(3,21); printf("                                                                    ");
    gotoxy(3,23); printf("                                                                    ");

    activarCursor();
    limpiarPantalla();

    // Dependiendo lo que pusimos en la clave, nos mostrará un menú u otro

    switch (tmpClave)
    {
    case claveSalir:
        limpiarPantalla();
        recuadro(0, 0, 39, 12);
        gotoxy(7,3);printf("Cerrando programa...\n");
        gotoxy(7,5);printf("Gracias por elegir FIT HUB!\n");
        gotoxy(7,7);printf("Hasta luego!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        break;
    case claveAdmin:
        tipoUsuario = 1;
        controlAdmin();
        break;
    case claveEmpleado:
        tipoUsuario = 2;
        controlEmpleado();
        break;
    case claveCliente:
        tipoUsuario = 3;
        controlCliente();
        break;
    default:
        printf("Clave incorrecta, presiona enter para intentar de nuevo\n");
        getchar(); // Captura el Enter previo al scanf
        getchar(); // Espera a que el usuario presione Enter para continuar
        goto restart;
        break;
    }
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
    return;
}

