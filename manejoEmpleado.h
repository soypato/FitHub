#ifndef MANEJOEMPLEADO_H_INCLUDED
#define MANEJOEMPLEADO_H_INCLUDED

typedef struct{
    int legajo;
    char nombre[];
    char apelldio[];
    int edad;
    int DNI;

}stEmpleado;

#endif // MANEJOEMPLEADO_H_INCLUDED
