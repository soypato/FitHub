#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manejoDeClientes.h"


typedef struct
{
    char plan[25];
    int diasDelPlan;
    int idDePlan;
    char nombre[20];
    char apellido[20];
    int DNI;
    int edad;
    char domicilio[25];
    float peso;
    float estatura;
    int bajaPasiva;
    int diasConcurridosEstaSemana;
} stArchivo;

typedef struct
{
    char nombre[20];
    char apellido[20];
    int DNI;
    int edad;
    char domicilio[25];
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
int archi2ADA(stCeldaPlanes ADA[], int dimension, const char ARCHIVO_PLANES[]);
int altaCliente(const char ARCHIVO_PLANES[], stCeldaPlanes ADA[], int validos, stCliente clienteTmp, int idDelPlan, char nombrePlan[], int diasDelPlan);
int agregarEnArregloClientes(stCeldaPlanes ADA[], int validos, stCeldaPlanes planTmp);
int buscarPosicionEnElArreglo(stCeldaPlanes ADA[], int validos, stCeldaPlanes planTmp);
int buscarPosicionEnElArregloConID(stCeldaPlanes ADA[], int validos, int id);
stCeldaPlanes convertirAPlanes(char plan[25], int diasDelPlan, int idDelPlan);
stCliente convertirACliente(stArchivo archi);
void pasarNuevoClienteAlArchivo(const char ARCHIVO_PLANES[], stCliente clienteTmp, int idDelPlan, char nombrePlan[], int diasdelPlan);
nodoArbol* buscarDNIEnADA(stCeldaPlanes ADA[], int validos, int dni);
int cargarADA(const char ARCHIVO_PLANES[],stCeldaPlanes ADA[], int validos, int dniEntrada);
int preguntarDNI();
stArchivo buscarPorDNIretornarTodaLaInformacion(int dni);
void bajaCliente(stCeldaPlanes ADA[], int validos, int dni);
void restaurarCliente(stCeldaPlanes ADA[], int validos, int dni);
void contarAsistencia(stCeldaPlanes ADA[], int validos, int dni);
void reiniciarAsistencia(stCeldaPlanes ADA[], int validos, int dni);
float calcularIMC(float peso, float estatura);

void modificarClienteEnElADAyEnElArchivo(stCeldaPlanes ADA[], int validos, int dni);
nodoArbol * modificarClienteIndividual(nodoArbol * cliente);
stArchivo formatoADA2Archi(int idPlan, char nombrePlan[], int diasDelPlan, stCliente cliente);
void cambiarDePlan(stCeldaPlanes ADA[], int validos, int dni, int nuevoID, char nuevoNombre[], int nuevoDias);
void eliminarCliente(stCeldaPlanes ADA[], int validos, int dni);
void restaurarCliente(stCeldaPlanes ADA[], int validos, int dni);

void listadoClientes();
void mostrarPlan(stCeldaPlanes plan);
void mostrarArbol(nodoArbol * arbol);
void mostrarClienteIndividual(stCliente cliente);
void imprimirEncabezado();
void imprimirMenu();
void mostrarUnStArchivo(stArchivo archi);
void mostraArchivoCompleto();
void modificarClienteEnElArchivo(stArchivo archi);

void controlCliente();

/// TDA arbolCliente
nodoArbol * inicArbol();
nodoArbol * cargarNodoArbolClientes(stCliente cliente);
nodoArbol * insertar(nodoArbol * arbol, nodoArbol * nuevo);
nodoArbol * buscarArbolCliente(nodoArbol * arbol, int dni);

/// usaremos la librer�a de pilas para manejar pesas o discos del inventario.


#endif // CLIENTES_H_INCLUDED
