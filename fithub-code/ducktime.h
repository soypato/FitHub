#include <stdio.h>
#include <stdlib.h>

#ifndef TIEMPO_H_INCLUDED
#define TIEMPO_H_INCLUDED
// ESTRUCTURA DEL TIEMPO
typedef struct
{
    int anio;
    int mes;
    int dia;
    int hora;
    int minuto;
    char nombreMes[4]; // Campo para almacenar el nombre del mes (3 caracteres + espacio para el carácter nulo)
} tiempo;

int validarFechas();
void mostrarFecha(tiempo fecha);

#endif // TIEMPO_H_INCLUDED
// DUCKTIME POR SOYPATO
