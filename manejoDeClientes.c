/// SECTOR CLIENTES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ducktime.h"
#include "manejoDeClientes.h"
#include "const.h"
#include "tipoUsuario.h"

const char ARCHIVO_PLANES[] = "planesClientes.dat";

void imprimirMenu()
{
    printf("1- Alta de cliente\n");
    printf("2- Baja y restauracion de cliente\n");
    printf("3- Modificacion de cliente\n");
    printf("4- Listado de planes + clientes\n");
    printf("5- Buscar cliente\n");
    printf("6- Mostrar clientes de un plan\n");
    printf("7- Calcular IMC (indice de masa corporal)\n");
    printf("0- Ir a atras\n");
    mostrarLinea(40);

}

int mainClientes()
{
    limpiarPantalla();
    stCeldaPlanes ADAPlanes[10];
    int valADAPlanes = 0;
    int dniTmp;
    int opcion;
    float IMC;
    float peso;
    float estatura;
    int posTmp;
    stCeldaPlanes idTmp;
    nodoArbol * nodoTmp1;
    char decisionTmpEstado2;
    char planTmp[50];
    char decision = 's';
    while (tolower(decision) == 's' || tolower(decision) == 'y')
    {
        // Cada vez que se ejecute el menú refrescamos los datos de archivos
        marcoEsteticoSwitch("MANEJO DE CLIENTES");
        imprimirMenu();
        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);

        valADAPlanes = archi2ADA(ADAPlanes, 10, ARCHIVO_PLANES);
        printf("validos: %i",valADAPlanes);
reset:
        switch(opcion)
        {
        case 1:

            marcoEsteticoSwitch("MANEJO DE CLIENTES > NUEVO CLIENTE");
            dniTmp = preguntarDNI();
            nodoTmp1 = buscarDNIEnADA(ADAPlanes, valADAPlanes, dniTmp);
            if(!nodoTmp1)
            {
                valADAPlanes = cargarADA(ARCHIVO_PLANES,ADAPlanes, valADAPlanes, dniTmp);

                /// REFRESCAMOS LA BUSQUEDA
                nodoTmp1 = buscarDNIEnADA(ADAPlanes, valADAPlanes, dniTmp);
                printf("Datos cargados satisfactoriamente\n");
                mostrarClienteIndividual(nodoTmp1->cliente);
            }
            else
            {
                mostrarLinea(10);
                printf("El cliente existe en el sistema\n");
                mostrarLinea(10);
                mostrarClienteIndividual(nodoTmp1->cliente);
            }
            break;
        case 2:
            marcoEsteticoSwitch("MANEJO DE CLIENTES > BAJA Y RESTAURACION DE CLIENTES");
            dniTmp = preguntarDNI();
            nodoTmp1 = buscarDNIEnADA(ADAPlanes, valADAPlanes, dniTmp);
            if(nodoTmp1)
            {
                mostrarLinea(20);
                mostrarClienteIndividual(nodoTmp1->cliente);
                printf("El estado del cliente en este momento es: ");
                if(nodoTmp1->cliente.bajaPasiva == 0)
                {
                    printf("ausente\n");
                }
                else
                {
                    printf("activo\n");
                }
                mostrarLinea(20);
                printf("Cambiar estado? (s/n): ");
                fflush(stdin);
                scanf("%c", &decisionTmpEstado2);
                if(tolower(decisionTmpEstado2) == 's')
                {
                    if(nodoTmp1->cliente.bajaPasiva == 0)
                    {
                        restarurarCliente(ADAPlanes, valADAPlanes, dniTmp);
                        printf("Cliente dado de alta de forma exitosa\n");
                    }
                    else
                    {
                        bajaCliente(ADAPlanes, valADAPlanes, dniTmp);
                        printf("Cliente dado de baja de forma exitosa\n");
                    }
                }
                else
                {
                    printf("Operacion cancelada por el usuario.\n");
                }
            }
            else
            {
                printf("El cliente no existe en el sistema.");
            }
            break;
        case 3:
            marcoEsteticoSwitch("MANEJO DE CLIENTES > MODIFICAR CLIENTE");
            mostrarADA(ADAPlanes, valADAPlanes);
            dniTmp = preguntarDNI();
            nodoTmp1 = buscarDNIEnADA(ADAPlanes, valADAPlanes, dniTmp);
            if(nodoTmp1)
            {
                modificarClienteEnElADAyEnElArchivo(ADAPlanes, valADAPlanes, dniTmp);
                printf("Cliente modificado de forma exitosa\n");
            }
            else
            {
                printf("El cliente no existe en el sistema.");
            }

            break;
        case 4:
            marcoEsteticoSwitch("MANEJO DE CLIENTES > LISTADO DE PLANES + CLIENTES");
            mostrarADA(ADAPlanes, valADAPlanes);
            break;
        case 5:
            marcoEsteticoSwitch("MANEJO DE CLIENTES > BUSCAR CLIENTE");
            dniTmp = preguntarDNI();
            nodoTmp1 = buscarDNIEnADA(ADAPlanes, valADAPlanes, dniTmp);
            if(nodoTmp1)
            {
                buscarPorDNIretornarTodaLaInformacion(dniTmp);
            }
            else
            {
                printf("El cliente no existe en el sistema");
            }
            break;
        case 6:
            marcoEsteticoSwitch("MANEJO DE CLIENTES > MOSTRAR USUARIOS DE UN PLAN");
            printf("* Se muestran los planes ya cargados con clientes\n");
            mostrarPlanes(ADAPlanes, valADAPlanes);
            printf("Introduzca el ID del plan que quiere mostrar: ");
            scanf("%i", &posTmp);
            posTmp = buscarPosicionEnElArregloConID(ADAPlanes, valADAPlanes, posTmp);
            marcoEsteticoSwitch("MANEJO DE CLIENTES > MOSTRAR USUARIOS DE UN PLAN > MOSTRAR CLIENTES");
            mostrarArbol(ADAPlanes[posTmp].arbol);
            break;
        case 7:
            marcoEsteticoSwitch("MANEJO DE CLIENTES > CALCULO DE IMC");
            printf("El IMC es un calculo hecho por la OMS para determinar si una persona\ntiene sobrepeso, bajo peso, obesidad o si esta en su peso normal,\npara calcularlo necesitamos el peso y la estatura de la persona\n");
            mostrarLinea(50);

            printf("Introduzca el peso: ");
            scanf("%f", &peso);

            printf("Ahora, la altura: ");
            scanf("%f", &estatura);

            IMC = calcularIMC(peso, estatura);

            printf("Tu IMC es: %f, eso quiere decir: ", IMC);

            if(IMC < 18.5)
            {
                printf("Bajo peso\n");
            }
            else if(IMC >= 18.5 && IMC <= 24.9)
            {
                printf("Normal\n");
            }
            else if(IMC >= 25 && IMC <= 29.9)
            {
                printf("Sobrepeso\n");
            }
            else if(IMC >= 30)
            {
                printf("Obesidad\n");
            }
            break;
        case 0:
            volverDependiendoTipoUsuario(tipoUsuario);
            break;
        default:
            printf("Opcion invalida, introduzca de nuevo la opcion: ");
            scanf("%d", &opcion);
            goto reset;
            break;
        }
        printf("\nDesea continuar? S/N: ");
        fflush(stdin);
        scanf("%c", &decision);
        limpiarPantalla();
    }
    return 0;
}

stArchivo buscarPorDNIretornarTodaLaInformacion(int dni)
{
    stArchivo archi;
    FILE * file = fopen(ARCHIVO_PLANES, "rb");
    if(file)
    {
        while(fread(&archi, sizeof(stArchivo), 1, file) > 0)
        {
            if(archi.DNI == dni)
            {
                mostrarLinea(50);
                mostrarUnStArchivo(archi);
            }
        }
        fclose(file);
    }
    else
    {
        printf("El archivo no existe");
    }
    return archi;
}


int preguntarDNI()
{
    int dni;
    printf("Ingrese el DNI del cliente: ");
    scanf("%d", &dni);
    return dni;
}

int cargarADA(const char ARCHIVO_PLANES[],stCeldaPlanes ADA[], int validos, int dniEntrada)
{
    stCliente cliente;
    stCeldaPlanes plan;
    int idTmp;
    mostrarPlanes(ADA, validos);
    printf("Ingrese el ID del plan (o uno nuevo si quiere crear un nuevo plan): ");
    scanf("%d", &idTmp);

    int posArreglo = buscarPosicionEnElArregloConID(ADA, validos, idTmp);

    if(posArreglo != -1) /// Si encuentra el plan
    {
        plan = ADA[posArreglo]; // Guarda en "plan" la posicion de antes (que ya tiene el plan)
    }
    else /// Si no encuentra el plan, lo crea
    {
        mostrarLinea(20);
        printf("El plan no existe, por favor, danos mas detalles para crearlo:\n");
        mostrarLinea(20);
        printf("Ingrese el nombre del plan: ");
        fflush(stdin);
        gets(plan.plan);
        printf("Ingrese los dias del plan: ");
        scanf("%d", &plan.diasDelPlan);
        plan.idPlan = idTmp;
        plan.arbol = inicArbol();
    }


    /*
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
    default:
        strcpy(plan.plan, "Desconocido");
        plan.diasDelPlan = -1;
        break;
    }

    */

    /** Ya para esta altura de la func, "plan" tiene que tener una pos. valida,
    sea porque la creamos o porque ya estaba y la pasamos **/

    printf("Ingrese el apellido del cliente: ");
    fflush(stdin);
    gets(cliente.apellido);

    printf("Ingrese el nombre del cliente: ");
    fflush(stdin);
    gets(cliente.nombre);

    printf("Ingrese la edad del cliente: ");
    scanf("%d", &cliente.edad);
    printf("Ingrese el domicilio del cliente: ");
    fflush(stdin);
    gets(cliente.domicilio);
    printf("Ingrese el peso del cliente: ");
    scanf("%f", &cliente.peso);
    printf("Ingrese la estatura del cliente (en centimetros): ");
    scanf("%f", &cliente.estatura);

    cliente.DNI = dniEntrada;
    cliente.diasConcurridosEstaSemana = 0;
    cliente.bajaPasiva = 1;
    validos = altaCliente(ARCHIVO_PLANES, ADA, validos, cliente, plan.idPlan, plan.plan, plan.diasDelPlan);
    pasarNuevoClienteAlArchivo(ARCHIVO_PLANES, cliente, plan.idPlan, plan.plan, plan.diasDelPlan);
    return validos;
}



nodoArbol* buscarDNIEnADA(stCeldaPlanes ADA[], int validos, int dni)
{
    nodoArbol * rta = inicArbol();
    nodoArbol * encontrado = inicArbol();
    for (int i = 0; i < validos; i++)
    {
        encontrado = buscarArbolCliente(ADA[i].arbol, dni);
        if (encontrado != NULL)
        {
            rta = encontrado;
        }
    }
    return encontrado;
}

stArchivo convertirAEstrcuturaArchivo(stCeldaPlanes plan, stCliente cliente)
{
    stArchivo archi;
    archi.idDePlan = plan.idPlan;
    strcpy(archi.plan, plan.plan);
    archi.diasDelPlan = plan.diasDelPlan;

    archi.peso = cliente.peso;
    archi.estatura = cliente.estatura;
    archi.bajaPasiva = cliente.bajaPasiva;
    archi.diasConcurridosEstaSemana = cliente.diasConcurridosEstaSemana;
    strcpy(archi.nombre, cliente.nombre);
    strcpy(archi.apellido, cliente.apellido);
    archi.DNI = cliente.DNI;
    archi.edad = cliente.edad;
    strcpy(archi.domicilio, cliente.domicilio);

    return archi;

}


int archi2ADA(stCeldaPlanes ADA[], int dimension, const char ARCHIVO_PLANES[])
{
    FILE * file = fopen(ARCHIVO_PLANES, "rb");
    stArchivo archi;
    int validos = 0;
    if(file)
    {
        while((fread(&archi, sizeof(stArchivo), 1, file)) > 0 && (validos < dimension))
        {
            stCliente cliente = convertirACliente(archi);
            validos = altaCliente(ARCHIVO_PLANES, ADA, validos, cliente, archi.idDePlan, archi.plan, archi.diasDelPlan);
        }
        fclose(file);
    }
    else
    {
        printf("El archivo no existe");
    }
    return validos;
}


void pasarNuevoClienteAlArchivo(const char ARCHIVO_PLANES[], stCliente clienteTmp, int idDelPlan, char nombrePlan[], int diasdelPlan)
{
    stCeldaPlanes planTMP = convertirAPlanes(nombrePlan, diasdelPlan, idDelPlan);
    stArchivo nuevoDato;
    stArchivo auxiliar;
    nuevoDato = convertirAEstrcuturaArchivo(planTMP, clienteTmp);

    FILE* buffer = fopen(ARCHIVO_PLANES, "rb");

    if(buffer) // existe // buffer != NULL
    {
        if( (ftell(buffer)) > 0)//tiene datos
        {

            fseek(buffer,sizeof(stArchivo)*-1,SEEK_END);
            fread(&auxiliar,sizeof(stArchivo),1,buffer);
            nuevoDato.idCliente = auxiliar.idCliente+1;

            fclose(buffer);

            buffer = fopen(ARCHIVO_PLANES,"ab");
            if(buffer)
            {
                fwrite(&nuevoDato,sizeof(stArchivo),1,buffer);
                fclose(buffer);
            }
        }
        else//no tiene datos
        {
            fclose(buffer);

            buffer  = fopen(ARCHIVO_PLANES,"ab");

            if(buffer)
            {
                nuevoDato.idCliente = 1;
                fwrite(&nuevoDato,sizeof(stArchivo),1,buffer);
                fclose(buffer);
            }
        }
    }
    else // no existe // buffer == NULL
    {
        fclose(buffer);
        buffer = fopen(ARCHIVO_PLANES,"wb"); // como no existe el archi no hay problema con usar wb
        if(buffer)
        {
            nuevoDato.idCliente = 1;
            fwrite(&nuevoDato,sizeof(stArchivo),1,buffer);
            fclose(buffer);
        }

    }

    //fclose(buffer);

}


int altaCliente(const char ARCHIVO_PLANES[], stCeldaPlanes ADA[], int validos, stCliente clienteTmp, int idDelPlan, char nombrePlan[], int diasDelPlan)
{

    stCeldaPlanes planTmp = convertirAPlanes(nombrePlan, diasDelPlan, idDelPlan);
    nodoArbol * nuevo = cargarNodoArbolClientes(clienteTmp); // creo la est. secundaria
    int posBuscado = buscarPosicionEnElArreglo(ADA, validos, planTmp); // busco la posicion del cliente en el arreglo
    if(posBuscado == -1) // si falla(no encontro el plan)
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
        if( (strcmp(ADA[i].plan, planTmp.plan)) == 0)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}


int buscarPosicionEnElArregloConID(stCeldaPlanes ADA[], int validos, int id)
{
    int pos = -1;
    int i = 0;
    while(i < validos && pos == -1)
    {
        if(id == ADA[i].idPlan)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}


stCeldaPlanes convertirAPlanes(char plan[25], int diasDelPlan, int idDelPlan)
{
    stCeldaPlanes planTmp;
    strcpy(planTmp.plan, plan);
    planTmp.diasDelPlan = diasDelPlan;
    planTmp.idPlan = idDelPlan;
    planTmp.arbol = inicArbol();
    return planTmp;
}


stCliente convertirACliente(stArchivo archi)
{
    stCliente cliente;
    strcpy(cliente.nombre, archi.nombre);
    strcpy(cliente.apellido, archi.apellido);
    cliente.DNI = archi.DNI;
    strcpy(cliente.domicilio, archi.domicilio);
    cliente.edad = archi.edad;
    cliente.peso = archi.peso;
    cliente.estatura = archi.estatura;
    cliente.bajaPasiva = archi.bajaPasiva;
    cliente.diasConcurridosEstaSemana = archi.diasConcurridosEstaSemana;
    return cliente;
}


void bajaCliente(stCeldaPlanes ADA[], int validos, int dni)
{
    nodoArbol * nodoTmp = buscarDNIEnADA(ADA, validos, dni);
    nodoTmp->cliente.bajaPasiva = 0;
}


void restarurarCliente(stCeldaPlanes ADA[], int validos, int dni)
{
    nodoArbol * nodoTmp = buscarDNIEnADA(ADA, validos, dni);
    nodoTmp->cliente.bajaPasiva = 1;
}


/// FUNCIONES DE MUESTREO INICIO

void mostrarADA(stCeldaPlanes ADA[], int validos)
{
    printf("validos %d", validos);

    for(int i = 0; i < validos; i++)
    {

        printf("\n");
        mostrarLinea(40);
        printf("Plan:\n");
        mostrarLinea(40);
        mostrarPlan(ADA[i]);
        mostrarLinea(20);
        printf("Clientes:\n");
        mostrarLinea(20);
        mostrarArbol(ADA[i].arbol);
    }
}


void mostrarPlanes(stCeldaPlanes ADA[], int validos)
{
    for(int i = 0; i <validos; i++)
    {
        mostrarLinea(40);
        mostrarPlan(ADA[i]);
        mostrarLinea(40);
    }
}


void mostrarPlan(stCeldaPlanes plan)
{
    printf("ID del Plan................. %i\n", plan.idPlan);
    printf("Nombre ..................... %s\n", plan.plan);
    printf("Dias........................ %i\n", plan.diasDelPlan);
}


void mostrarArbol(nodoArbol * arbol)
{
    if(arbol)
    {
        mostrarArbol(arbol->izq);
        mostrarClienteIndividual(arbol->cliente);
        mostrarArbol(arbol->der);
    }
}


void mostrarClienteIndividual(stCliente cliente)
{
    printf("Nombre: %s\n", cliente.nombre);
    printf("Apellido: %s\n", cliente.apellido);
    printf("DNI: %d\n", cliente.DNI);
    printf("Edad: %d\n", cliente.edad);
    printf("Domicilio: %s\n", cliente.domicilio);
    printf("Peso: %.2f\n", cliente.peso);
    printf("Estatura: %.2f\n", cliente.estatura);
    if(cliente.bajaPasiva == 1)
    {
        printf("Este cliente esta activo\n");
    }
    else
    {
        printf("Este cliente esta ausente\n");
    }
    printf("Dias concurridos esta semana: %d\n", cliente.diasConcurridosEstaSemana);
    mostrarLinea(20);
}


void mostrarUnStArchivo(stArchivo archi)
{
    printf("Nombre: %s\n", archi.nombre);
    printf("Apellido: %s\n", archi.apellido);
    printf("DNI: %d\n", archi.DNI);
    printf("Edad: %d\n", archi.edad);
    printf("Domicilio: %s\n", archi.domicilio);
    printf("Peso: %.2f\n", archi.peso);
    printf("Estatura: %.2f\n", archi.estatura);
    if(archi.bajaPasiva == 1)
    {
        printf("Este cliente esta activo\n");
    }
    else
    {
        printf("Este cliente esta ausente\n");
    }
    printf("Dias concurridos esta semana: %d\n", archi.diasConcurridosEstaSemana);
    mostrarLinea(8);
    printf("ID del plan: %d\n", archi.idDePlan);
    printf("Plan: %s\n", archi.plan);
    printf("Dias del plan: %d\n", archi.diasDelPlan);
    printf("\n");
}


void mostrarArchivoClientes()
{
    FILE * file = fopen(ARCHIVO_PLANES, "rb");
    stArchivo archi;
    if(file)
    {
        while(fread(&archi, sizeof(stArchivo), 1, file) > 0)
        {
            mostrarLinea(50);
            mostrarUnStArchivo(archi);
        }
        fclose(file);
    }
}


void modificarClienteEnElADAyEnElArchivo(stCeldaPlanes ADA[], int validos, int dni)
{
    nodoArbol * nodoTmp = buscarDNIEnADA(ADA, validos, dni);
    stArchivo archiTmp;
    stCeldaPlanes planTmp;
    planTmp.arbol->cliente.DNI = dni;
    int posTmp = buscarPosicionEnElArreglo(ADA, validos, planTmp);

    int opcion;
    printf("Que desea modificar?\n");
    printf("1- Nombre\n");
    printf("2- Apellido\n");
    printf("3- DNI\n");
    printf("4- Edad\n");
    printf("5- Domicilio\n");
    printf("6- Peso\n");
    printf("7- Estatura\n");
    printf("8- Baja pasiva\n");
    printf("9- Dias concurridos esta semana\n");
    printf("0- Cancelar\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);

    switch(opcion)
    {
    case 1:
        printf("Ingrese el nuevo nombre: ");
        fflush(stdin);
        gets(nodoTmp->cliente.nombre);
        break;
    case 2:
        printf("Ingrese el nuevo apellido: ");
        fflush(stdin);
        gets(nodoTmp->cliente.apellido);
        break;
    case 3:
        printf("Ingrese el nuevo DNI: ");
        scanf("%d", &nodoTmp->cliente.DNI);
        break;
    case 4:
        printf("Ingrese la nueva edad: ");
        scanf("%d", &nodoTmp->cliente.edad);
        break;
    case 5:
        printf("Ingrese el nuevo domicilio: ");
        fflush(stdin);
        gets(nodoTmp->cliente.domicilio);
        break;
    case 6:
        printf("Ingrese el nuevo peso: ");
        scanf("%f", &nodoTmp->cliente.peso);
        break;
    case 7:
        printf("Ingrese la nueva estatura: ");
        scanf("%f", &nodoTmp->cliente.estatura);
        break;
    case 8:
        printf("Ingrese el nuevo estado de baja pasiva: ");
        scanf("%d", &nodoTmp->cliente.bajaPasiva);
        break;
    case 9:
        printf("Ingrese los nuevos dias concurridos esta semana: ");
        scanf("%d", &nodoTmp->cliente.diasConcurridosEstaSemana);
        break;
    case 0:
        printf("Operacion cancelada por el usuario.\n");
        break;
    default:
        printf("Opcion invalida, introduzca de nuevo la opcion: ");
        scanf("%d", &opcion);
        break;
    }

    archiTmp = formatoADA2Archi(ADA[posTmp].idPlan, ADA[posTmp].plan, ADA[posTmp].diasDelPlan, nodoTmp->cliente);
    mostrarUnStArchivo(archiTmp);
    modificarClienteEnElArchivo(archiTmp);


}

stArchivo formatoADA2Archi(int idPlan, char nombrePlan[], int diasDelPlan, stCliente cliente)
{
    stArchivo archi;
    archi.idDePlan = idPlan;
    strcpy(archi.plan, nombrePlan);
    archi.diasDelPlan = diasDelPlan;

    archi.peso = cliente.peso;
    archi.estatura = cliente.estatura;
    archi.bajaPasiva = cliente.bajaPasiva;
    archi.diasConcurridosEstaSemana = cliente.diasConcurridosEstaSemana;
    strcpy(archi.nombre, cliente.nombre);
    strcpy(archi.apellido, cliente.apellido);
    archi.DNI = cliente.DNI;
    archi.edad = cliente.edad;
    strcpy(archi.domicilio, cliente.domicilio);

    return archi;
}



void modificarClienteEnElArchivo(stArchivo archi)
{
    FILE *file = fopen(ARCHIVO_PLANES, "rb+");

    if (file != NULL)
    {
        stArchivo archiAux;
        int encontrado = 0;  // Variable para indicar si se encontró el cliente

        while (fread(&archiAux, sizeof(stArchivo), 1, file) > 0)
        {
            if (archiAux.DNI == archi.DNI)
            {
                fseek(file, -sizeof(stArchivo), SEEK_CUR);
                fwrite(&archi, sizeof(stArchivo), 1, file);
                encontrado = 1;  // Se ha encontrado el cliente
                break;  // Salir del bucle, ya que se encontró y modificó el cliente
            }
        }

        if (!encontrado)
        {
            printf("Cliente no encontrado en el archivo\n");
        }

        fclose(file);
    }
    else
    {
        printf("El archivo no pudo abrirse\n");
    }
}

void mostraArchivoCompleto()
{
    FILE* buffer = fopen(ARCHIVO_PLANES,"rb");

    stArchivo archi;

    while( (fread(&archi,sizeof(stArchivo),1,buffer)) > 0 )
    {
        mostrarUnStArchivo(archi);
    }

    fclose(buffer);
}


/// FUNCIONES DE MUESTREO FIN


float calcularIMC(float peso, float estatura)
{
    float imc = peso / (estatura * estatura);
    return imc;
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


nodoArbol * insertar(nodoArbol * arbol, nodoArbol * nuevoNodo)
{
    if(arbol == NULL)
    {
        arbol = nuevoNodo;
    }
    else
    {
        if(nuevoNodo->cliente.DNI > arbol->cliente.DNI)
        {
            arbol->der = insertar(arbol->der, nuevoNodo);
        }
        else
        {
            arbol->izq = insertar(arbol->izq, nuevoNodo);
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
