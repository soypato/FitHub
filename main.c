/// SECTOR CLIENTES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ducktime.h"

const char ARCHIVO_PLANES[] = "planesClientes.dat";

typedef struct
{
    char plan[25];
    int diasDelPlan;
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


typedef struct nodoLista
{
    float montoPago;
    int idMetodoDePago; /// 1 para efectivo, 2 tarj credito, 3 tarj debito, 4 billeteras virtuales
    /* cuando hagamos la funcion de alta del usuario poner, un if metodo de pago == 1 strcpy,
    para despues asignarle el metodo de pago que haya elegido segun el numero */
    char metodoDePago[20]; /// efectivo, bill virtual, tarjeta credito, tarjeta debito
    tiempo fechaDePago;
    struct nodoLista* siguiente;
} nodoLista;

/// Prototipados
int archi2ADA(stCeldaPlanes ADA[], int dimension, char archi[]);
int altaCliente(stCeldaPlanes ADA[], int validos, stCliente clienteTmp, stCeldaPlanes planTmp);
int agregarEnArregloClientes(stCeldaPlanes ADA[], int validos, stCeldaPlanes planTmp);
int buscarPosicionEnElArreglo(stCeldaPlanes ADA[], int validos, stCeldaPlanes planTmp);
stCeldaPlanes convertirAPlanes(char plan[25], int diasDelPlan);
stCliente convertirACliente(stArchivo archi);
void ADA2Archi(stCeldaPlanes ADA[], int validos, char archi[]);
void pasarPlanesAArchivo(FILE * file, nodoArbol * arbol, int diasDelPlan, char plan[25]);
nodoArbol* buscarDNIEnADA(stCeldaPlanes ADA[], int validos, int dni);
int cargarADA(stCeldaPlanes ADA[], int validos, int dniEntrada);
int preguntarDNI();
void listadoClientes();
void imprimirMenu();
void imprimirEncabezado();


/// TDA arbolCliente
nodoArbol * inicArbol();
nodoArbol * cargarNodoArbolClientes(stCliente cliente);
nodoArbol * insertar(nodoArbol * arbol, nodoArbol * nuevo);
nodoArbol * buscarArbolCliente(nodoArbol * arbol, int dni);

/// usaremos la librería de pilas para manejar pesas o discos del inventario.

void imprimirEncabezado() {
    printf("\nBienvenido al sector de clientes\n");
    printf("--------------------------------\n");
}

void imprimirMenu() {
    printf("1- Alta de cliente\n");
    printf("2- Baja de cliente\n");
    printf("3- Modificacion de cliente\n");
    printf("4- Listado de clientes\n");
    printf("5- Buscar cliente\n");
    printf("6- Guardar modificaciones\n");
    printf("0- Ir a atrá\n");
    printf("\nIngrese una opcion: ");
}

int main()
{
    stCeldaPlanes ADAPlanes[10];
    int valADAPlanes = 0;
    int dniTmp;
    int opcion;
    nodoArbol * nodoTmp1;
    char decision = 'S';
    while (tolower(decision) == 's' || tolower(decision) == 'y')
    {
        // Cada vez que se ejecute el menú refrescamos los datos de archivos
        imprimirEncabezado();
        imprimirMenu();
        scanf("%d", &opcion);
        reset:
        valADAPlanes = archi2ADA(ADAPlanes, 10, ARCHIVO_PLANES);
        switch(opcion)
        {
        case 1:
            dniTmp = preguntarDNI();
            nodoTmp1 = buscarDNIEnADA(ADAPlanes, valADAPlanes, dniTmp);
            if(!nodoTmp1)
            {
                valADAPlanes = cargarADA(ADAPlanes, valADAPlanes, dniTmp);
            }
            else
            {
                printf("El cliente existe en el sistema");
            }
            break;
        case 2:
            // bajaCliente();
            break;
        case 3:
            // modificacionCliente();
            break;
        case 4:
            // listadoClientes();
            break;
        case 5:
            // buscarCliente();
            break;
        case 6:
            ADA2Archi(ADAPlanes, valADAPlanes, ARCHIVO_PLANES);
            break;
        case 0:
            decision = 'n';
            break;
        default:
            printf("Opcion invalida, introduzca de nuevo la opcion");
            scanf("%d", &opcion);
            goto reset;
            break;
        }
        printf("\nDesea continuar? S/N: ");
        fflush(stdin);
        scanf("%c", &decision);
        ADA2Archi(ADAPlanes, valADAPlanes, ARCHIVO_PLANES);
        system("cls");
    }
    return 0;
}
/*
void listadoClientes()
{
    printf("Listado de clientes\n");
    printf("-------------------\n");
    printf("1- Listado de clientes por plan\n");
    printf("2- Listado de clientes por edad\n");
    printf("3- Listado de clientes por peso\n");
    printf("4- Listado de clientes por altura\n");
    printf("5- Listado de clientes por nombre\n");
    printf("6- Listado de clientes por apellido\n");
    printf("7- Listado de clientes por DNI\n");
    printf("8- Listado de clientes por dias de la semana\n");
    printf("0- Ir a atrás\n");
    printf("\nIngrese una opcion: ");
} */

int preguntarDNI()
{
    int dni;
    printf("Ingrese el DNI del cliente: ");
    scanf("%d", dni);
    return dni;
}

int cargarADA(stCeldaPlanes ADA[], int validos, int dniEntrada)
{
    stCliente cliente;
    stCeldaPlanes plan;

    printf("Ingrese el ID del plan: ");
    scanf("%d", &plan.idPlan);

    switch(plan.idPlan)
    {
    case 1:
        strcpy(plan.plan, "Starter");
        plan.diasDelPlan = 3;
        break;
    case 2:
        strcpy(plan.plan, "Intermedio");
        plan.diasDelPlan = 4;
        break;
    case 3:
        strcpy(plan.plan, "Avanzado");
        plan.diasDelPlan = 5;
        break;
    case 4:
        strcpy(plan.plan, "Experto");
        plan.diasDelPlan = 7;
        break;
    }


    printf("Ingrese el nombre del cliente: ");
    fflush(stdin);
    gets(cliente.nombre);
    printf("Ingrese el apellido del cliente: ");
    fflush(stdin);
    gets(cliente.apellido);
    printf("Ingrese la edad del cliente: ");
    scanf("%d", &cliente.edad);
    printf("Ingrese el peso del cliente: ");
    scanf("%f", &cliente.peso);
    printf("Ingrese la estatura del cliente: ");
    scanf("%f", &cliente.estatura);

    cliente.DNI = dniEntrada;
    cliente.diasConcurridosEstaSemana = 0;
    cliente.bajaPasiva = 1;

    validos = altaCliente(ADA, validos, cliente, plan);

    return validos;
}


nodoArbol* buscarDNIEnADA(stCeldaPlanes ADA[], int validos, int dni) {
    nodoArbol * rta = inicArbol();
    nodoArbol * encontrado = inicArbol();
    for (int i = 0; i < validos; i++) {
        encontrado = buscarArbolCliente(ADA[i].arbol, dni);
        if (encontrado != NULL) {
            rta = encontrado;
        }
    }
    return encontrado;
}

void pasarPlanesAArchivo(FILE * file, nodoArbol * arbol, int diasDelPlan, char plan[25])
{
    if (arbol != NULL)
    {
        /// Pre-order: para que guarde en orden de DNIs como viene
        stArchivo archi;

        strcpy(archi.plan, plan);
        archi.diasDelPlan = diasDelPlan;
        archi.peso = arbol->cliente.peso;
        archi.estatura = arbol->cliente.estatura;
        archi.bajaPasiva = arbol->cliente.bajaPasiva;
        archi.diasConcurridosEstaSemana = arbol->cliente.diasConcurridosEstaSemana;
        strcpy(archi.nombre, arbol->cliente.nombre);
        strcpy(archi.apellido, arbol->cliente.apellido);
        archi.DNI = arbol->cliente.DNI;
        archi.edad = arbol->cliente.edad;

        fwrite(&archi, sizeof(stArchivo), 1, file);

        pasarPlanesAArchivo(file, arbol->izq, diasDelPlan, plan);
        pasarPlanesAArchivo(file, arbol->der, diasDelPlan, plan);
    }
    else
    {
        printf("No hay clientes que pasar al archivo");
    }
}

void ADA2Archi(stCeldaPlanes ADA[], int validos, char archi[])
{
    FILE * file = fopen(archi, "wb"); // Usamos WB porque queremos que se sobreescriba el archivo
    if(file)
    {
        int i=0;
        while(i < validos)
        {
            pasarPlanesAArchivo(file, ADA[i].arbol, ADA[i].diasDelPlan, ADA[i].plan); // le pasa todos los datos del plan
            i++;
        }
    fclose(file);
    }
    else
    {
        printf("No se pudo crear el archivo");
    }
}

int archi2ADA(stCeldaPlanes ADA[], int dimension, char archi[])
{
    FILE * file = fopen(archi, "rb");

    stArchivo archiTmp;
    stCeldaPlanes planTmp;
    stCliente clienteTmp;
    int validos;

    if(file)
    {

        while(fread(&archiTmp, sizeof(stArchivo), 1, archi) > 0 && validos < dimension)
        {
            clienteTmp = convertirACliente(archiTmp);
            planTmp = convertirAPlanes(archiTmp.plan, archiTmp.diasDelPlan);
            validos = altaCliente(ADA, validos, clienteTmp, planTmp);
        }
        fclose(file);
    }
    else
    {
        printf("El archivo no existe");
    }
    return validos;
}

int altaCliente(stCeldaPlanes ADA[], int validos, stCliente clienteTmp, stCeldaPlanes planTmp)
{
    nodoArbol * nuevo = cargarNodoArbolClientes(clienteTmp); // creo la est. secundaria
    int posBuscado = buscarPosicionEnElArreglo(ADA, validos, planTmp); // busco la posicion del cliente en el arreglo
    if(posBuscado == -1) // si falla
    {
        validos = agregarEnArregloClientes(ADA, validos, planTmp); // agrego el nodo al arreglo
        posBuscado = validos-1; // fuerzo la busqueda

    }
    ADA[posBuscado].arbol = insertar(ADA[posBuscado].arbol, nuevo); // inserto el nodo en el arbol
    return validos;
}

int agregarEnArregloClientes(stCeldaPlanes ADA[], int validos, stCeldaPlanes planTmp)
{
    ADA[validos] = planTmp;
    validos++;
    return validos;
}


int buscarPosicionEnElArreglo(stCeldaPlanes ADA[], int validos, stCeldaPlanes planTmp)
{
    int pos = -1;
    int i = 0;
    while(i < validos && pos == -1)
    {
        if(strcmp(ADA[i].plan, planTmp.plan) == 0)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}

stCeldaPlanes convertirAPlanes(char plan[25], int diasDelPlan)
{
    stCeldaPlanes planTmp;
    strcpy(planTmp.plan, plan);
    planTmp.diasDelPlan = diasDelPlan;
    planTmp.arbol = inicArbol();
    return planTmp;
}

stCliente convertirACliente(stArchivo archi)
{
    stCliente cliente;
    strcpy(cliente.nombre, archi.nombre);
    strcpy(cliente.apellido, archi.apellido);
    cliente.DNI = archi.DNI;
    cliente.edad = archi.edad;
    cliente.peso = archi.peso;
    cliente.estatura = archi.estatura;
    cliente.bajaPasiva = archi.bajaPasiva;
    cliente.diasConcurridosEstaSemana = archi.diasConcurridosEstaSemana;
    return cliente;
}


/// TDA ARBOLES

nodoArbol * inicArbol()
{
    return NULL;
}

nodoArbol * cargarNodoArbolClientes(stCliente cliente)
{
    nodoArbol * nuevo = (nodoArbol*)malloc(sizeof(nodoArbol));
    nuevo->cliente = cliente;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

nodoArbol * insertar(nodoArbol * arbol, nodoArbol * nuevo)
{
    if(arbol == NULL)
    {
        arbol = nuevo;
    }
    else
    {
        if(nuevo->cliente.DNI < arbol->cliente.DNI)
        {
            arbol->izq = insertar(arbol->izq, nuevo);
        }
        else
        {
            arbol->der = insertar(arbol->der, nuevo);
        }
    }
    return arbol;
}

nodoArbol * buscarArbolCliente(nodoArbol * arbol, int dni)
{
    nodoArbol * rta = NULL;
    if(arbol)
    {
        if(arbol->cliente.DNI == dni)
        {
            rta = arbol;
        }
        else
        {
            if(dni < arbol->cliente.DNI)
            {
                rta = buscarArbolCliente(arbol->izq, dni);
            }
            else
            {
                rta = buscarArbolCliente(arbol->der, dni);
            }
        }
    }
    return rta;
}
