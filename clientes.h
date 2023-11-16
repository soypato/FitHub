#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"


typedef struct
{
    char plan[25];
    int diasDelPlan;
    int idDePlan;
    char nombre[20];
    char apellido[20];
    int DNI;
    int edad;
    float peso;
    float estatura;
    int bajaPasiva;
    int diasConcurridosEstaSemana;
} stArchivo;

typedef struct
{
    char nombre[20];
    char apellido[20];
    int DNI; /// CAMPO UNICO ///
    int edad;
    float peso;
    float estatura;
    int bajaPasiva; /// 1 para alta, 0 para baja
    int diasConcurridosEstaSemana;///cant de dias, inic en 0
} stCliente;

typedef struct nodoArbol
{
    stCliente cliente;
    struct nodoArbol* izq;
    struct nodoArbol* der;
} nodoArbol;

typedef struct
{
    int idPlan; /// 1 para starter, 2 para intermedio, 3 para avanzado, 4 para experto
    char plan[25];///starter-intermedio-avanzado-experto
    int diasDelPlan;///3 4 5 7
    struct nodoArbol* arbol;
} stCeldaPlanes;

/// Prototipados
int archi2ADA(stCeldaPlanes ADA[], int dimension, char archi[]);
int altaCliente(stCeldaPlanes ADA[], int validos, stCliente clienteTmp, int idPlan, char nombrePlan[], int diasDelPlan);
int agregarEnArregloClientes(stCeldaPlanes ADA[], int validos, stCeldaPlanes planTmp);
int buscarPosicionEnElArreglo(stCeldaPlanes ADA[], int validos, stCeldaPlanes planTmp);
int buscarPosicionEnElArregloConID(stCeldaPlanes ADA[], int validos, int id);
stCeldaPlanes convertirAPlanes(char plan[25], int diasDelPlan, int idDelPlan);
stCliente convertirACliente(stArchivo archi);
void ADA2Archi(stCeldaPlanes ADA[], int validos, char archi[]);
void pasarPlanesAArchivo(FILE * file, nodoArbol * arbol, int diasDelPlan, char plan[25], int idDelPlan);
nodoArbol* buscarDNIEnADA(stCeldaPlanes ADA[], int validos, int dni);
int cargarADA(stCeldaPlanes ADA[], int validos, int dniEntrada);
int preguntarDNI();
stArchivo buscarPorDNIretornarTodaLaInformacion(int dni);
void bajaCliente(stCeldaPlanes ADA[], int validos, int dni);
void restaurarCliente(stCeldaPlanes ADA[], int validos, int dni);
void modificarCliente(stCeldaPlanes ADA[], int validos, int dni);
float calcularIMC(float peso, float estatura);

void listadoClientes();
void mostrarPlan(stCeldaPlanes plan);
void mostrarArbol(nodoArbol * arbol);
void mostrarClienteIndividual(stCliente cliente);
void mostrarLinea(int cantidad); /// ESTA VA AL MAIN ASI LA USAN TODOS
void marcoEsteticoSwitch(char texto[]); /// ESTA TAMBIEN
void imprimirEncabezado();
void imprimirMenu();
void mostrarUnStArchivo(stArchivo archi);

/// TDA arbolCliente
nodoArbol * inicArbol();
nodoArbol * cargarNodoArbolClientes(stCliente cliente);
nodoArbol * insertar(nodoArbol * arbol, nodoArbol * nuevo);
nodoArbol * buscarArbolCliente(nodoArbol * arbol, int dni);

/// usaremos la librería de pilas para manejar pesas o discos del inventario.


#endif // CLIENTES_H_INCLUDED
