#ifndef MANEJOEMPLEADO_H_INCLUDED
#define MANEJOEMPLEADO_H_INCLUDED

typedef struct{
    int legajo;
    char nombreYApellido[40];
    int edad;
    int DNI;
    char categoria[30];
    int bajaPasiva;
}stEmpleado;

#endif // MANEJOEMPLEADO_H_INCLUDED
