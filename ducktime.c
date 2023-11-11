#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ducktime.h"

const char *obtenerNombreMes(int mes)
{
    const char *nombresMeses[] = {
        "ene", "feb", "mar", "abr", "may", "jun",
        "jul", "ago", "sep", "oct", "nov", "dic"};

    if (mes >= 1 && mes <= 12)
    {
        return nombresMeses[mes - 1];
    }
    if (mes == NULL)
    {
        return ", no hay fecha definida"; // cuando se hace, por ejemplo, check-out
    }
    else
    {
        return "mes invalido";
    }
}

int esAnioBisiesto(int anio)
{
    if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0)
    {
        return 1; // Es un año bisiesto
    }
    else
    {
        return 0; // No es un año bisiesto
    }
}

void cargaDeFechas(tiempo *A)
{
    printf("Introduzca el anio: ");
    scanf("%i", &(A->anio));

    printf("Introduzca el mes: ");
    scanf("%i", &(A->mes));

    while (A->mes < 1 || A->mes > 12)
    {
        printf("Mes incorrecto, intente de nuevo: ");
        scanf("%i", &(A->mes));
    }

    int maxDias;

    if (A->mes == 2) // Febrero
    {
        if (esAnioBisiesto(A->anio))
        {
            maxDias = 29;
        }
        else
        {
            maxDias = 28;
        }
    }
    else if (A->mes == 4 || A->mes == 6 || A->mes == 9 || A->mes == 11) // Abril, junio, septiembre, noviembre
    {
        maxDias = 30;
    }
    else // Resto de los meses
    {
        maxDias = 31;
    }

    printf("Introduzca el dia: ");
    scanf("%i", &(A->dia));

    while (A->dia < 1 || A->dia > maxDias) // calcula los días según el mes
    {
        printf("Dia incorrecto para tal mes, intente de nuevo (1-%d): ", maxDias);
        scanf("%i", &(A->dia));
    }

    const char *nombreMes = obtenerNombreMes(A->mes);
    strcpy(A->nombreMes, nombreMes);
}


void mostrarFecha(tiempo fecha)
{
    printf("Fecha: %d %s. %d\n", fecha.dia, fecha.nombreMes, fecha.anio);
}
