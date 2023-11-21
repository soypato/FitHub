/// SECTOR CLIENTES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ducktime.h"
#include "manejoDeClientes.h"
#include "manejoDePagos.h"
#include "const.h"
#include "tipoUsuario.h"
#include <time.h>

#define MAX_LONGITUD_RUTINA 1000

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
    printf("8- Contar asistencia\n");
    printf("9- Reiniciar asistencia\n");
    printf("10- Cambiar cliente de plan\n");
    printf("11- Generar rutina segun dias\n");
    printf("0 - Ir a atras\n");
    mostrarLinea(40);

}

stCeldaPlanes ADAPlanes[10];
int valADAPlanes = 0;
int dniTmp;
int opcion;
float IMC;
float peso;
float estatura;
int posTmp;
int idPlanTmp;
char nombreTmp[25];
int cantTmp;
int diasRutinaTmp;
char confirmacion='w';
stArchivo archivoTmp;
nodoArbol * nodoTmp1;
char decisionTmpEstado2;
int op=0;
char decision = 's';

int mainClientes()
{
    limpiarPantalla();
    while (tolower(decision) == 's'|| tolower(decision) == 'y')
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

                printf("Cambiar estado? (s/n): ");
                fflush(stdin);
                scanf("%c", &decisionTmpEstado2);
                if(tolower(decisionTmpEstado2) == 's')
                {
                    if(nodoTmp1->cliente.bajaPasiva == 1)
                    {
                        restarurarCliente(ADAPlanes, valADAPlanes, dniTmp);
                        printf("Cliente dado de baja de forma exitosa\n");
                    }
                    else
                    {
                        bajaCliente(ADAPlanes, valADAPlanes, dniTmp);
                        printf("Cliente dado de alta de forma exitosa\n");
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
preguntarDNIOtravez:
            dniTmp = preguntarDNI();
            nodoTmp1 = buscarDNIEnADA(ADAPlanes, valADAPlanes, dniTmp);
            if(nodoTmp1)
            {

                modificarClienteEnElADAyEnElArchivo(ADAPlanes, valADAPlanes, dniTmp);
                mostrarLinea(20);

                printf("Cliente modificado de forma exitosa\n");
            }
            else
            {
                printf("El cliente no existe en el sistema. Intentar otra vez?: ");
                fflush(stdin);
                scanf("%c",&confirmacion);
                if( confirmacion == 's')
                {
                    goto preguntarDNIOtravez;
                }
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
                archivoTmp = buscarPorDNIretornarTodaLaInformacion(dniTmp);
                mostrarUnStArchivo(archivoTmp);
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

            printf("Ahora, la altura(en cm!): ");
            scanf("%f", &estatura);

            IMC = calcularIMC(peso, estatura);

            printf("Tu IMC es: %f, eso quiere decir: ", IMC);

            if(IMC < 18.5)
            {
                printf("Bajo peso\n");
            }
            else if(IMC >= 18.5 && IMC < 25)
            {
                printf("Normal\n");
            }
            else if(IMC >= 25 && IMC < 30)
            {
                printf("Sobrepeso\n");
            }
            else if(IMC >= 30)
            {
                printf("Obesidad\n");
            }
            break;
        case 8:
            marcoEsteticoSwitch("MANEJO DE CLIENTES > CONTAR ASISTENCIA");
            dniTmp = preguntarDNI();
            nodoTmp1 = buscarDNIEnADA(ADAPlanes, valADAPlanes, dniTmp);
            if(nodoTmp1)
            {
                contarAsistencia(ADAPlanes, valADAPlanes, dniTmp);
            }
            else
            {
                printf("El cliente no existe en el sistema.");
            }
            break;
        case 9:
            marcoEsteticoSwitch("MANEJO DE CLIENTES > REINICIAR ASISTENCIA");
            dniTmp = preguntarDNI();
            nodoTmp1 = buscarDNIEnADA(ADAPlanes, valADAPlanes, dniTmp);
            if(nodoTmp1)
            {
                reiniciarAsistencia(ADAPlanes, valADAPlanes, dniTmp);
            }
            else
            {
                printf("El cliente no existe en el sistema.");
            }
            break;
        case 10:
            marcoEsteticoSwitch("MANEJO DE CLIENTES > CAMBIAR CLIENTE DE PLAN");
            dniTmp = preguntarDNI();
            nodoTmp1 = buscarDNIEnADA(ADAPlanes, valADAPlanes, dniTmp);
            if(nodoTmp1)
            {
                printf("Ingrese el ID del nuevo plan: ");
                scanf("%i", &idPlanTmp);
                printf("Ingrese el nombre del nuevo plan: ");
                fflush(stdin);
                gets(&nombreTmp);
                printf("Ingrese la cantidad de dias del nuevo plan: ");
                scanf("%i", &cantTmp);
                cambiarDePlan(ADAPlanes, valADAPlanes, dniTmp, idPlanTmp, nombreTmp, cantTmp);
            }
            else
            {
                printf("El cliente no existe en el sistema.");
            }
            break;

        case 11:
            printf("\n");
            marcoEsteticoSwitch("MANEJO DE CLIENTES > MOSTRAR RUTINA SEGUN DIAS");
            printf("Ingrese la cantidad de dias que desea para su rutina (3/4/5/6)\n");
restart:
            scanf("%d", &diasRutinaTmp);
            limpiarPantalla();

            char* rutinaMuscular = generarRutinaMuscular(diasRutinaTmp);
            printf("%s", rutinaMuscular);
            printf("\n");
            mostrarLinea(60);
            switch(diasRutinaTmp)
            {

            case 3:

                generarRutina3dias();
                break;

            case 4:
                generarRutina4dias();
                break;

            case 5:
                generarRutina5dias();
                break;

            case 6:
                generarRutina6dias();
                break;

            default:
                printf("Opcion invalida. Ingrese de nuevo el dia\n");
                goto restart;

                break;
            }
            break;


        case 0:
            //volverDependiendoTipoUsuario(tipoUsuario);
            return 0;
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
                fclose(file);
                return archi;
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
    nodoArbol* encontrado = inicArbol();
    for (int i = 0; i < validos; i++)
    {
        encontrado = buscarArbolCliente(ADA[i].arbol, dni);
        if(encontrado != NULL)
        {
            return encontrado;
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
    nodoArbol* nodoTmp = buscarDNIEnADA(ADA,validos,dni);
    stArchivo archiTmp;
    stArchivo datosPlan = buscarPorDNIretornarTodaLaInformacion(dni);

    nodoTmp->cliente.bajaPasiva = 1;

    archiTmp = formatoADA2Archi(datosPlan.idDePlan, datosPlan.plan, datosPlan.diasDelPlan, nodoTmp->cliente);
    mostrarUnStArchivo(archiTmp);
    modificarClienteEnElArchivo(archiTmp);
}


void restarurarCliente(stCeldaPlanes ADA[], int validos, int dni)
{
    nodoArbol * nodoTmp = buscarDNIEnADA(ADA, validos, dni);
    stArchivo archiTmp;
    stArchivo datosPlan = buscarPorDNIretornarTodaLaInformacion(dni);

    nodoTmp->cliente.bajaPasiva = 0;

    archiTmp = formatoADA2Archi(datosPlan.idDePlan, datosPlan.plan, datosPlan.diasDelPlan, nodoTmp->cliente);
    mostrarUnStArchivo(archiTmp);
    modificarClienteEnElArchivo(archiTmp);
}

void contarAsistencia(stCeldaPlanes ADA[], int validos, int dni)
{
    nodoArbol * nodoTmp = buscarDNIEnADA(ADA, validos, dni);
    stArchivo archiTmp;
    stArchivo datosPlan = buscarPorDNIretornarTodaLaInformacion(dni);

    if (nodoTmp->cliente.diasConcurridosEstaSemana < datosPlan.diasDelPlan)
    {
        nodoTmp->cliente.diasConcurridosEstaSemana++;
        archiTmp = formatoADA2Archi(datosPlan.idDePlan, datosPlan.plan, datosPlan.diasDelPlan, nodoTmp->cliente);
        mostrarUnStArchivo(archiTmp);
        printf("Cliente modificado de forma exitosa\n");

        modificarClienteEnElArchivo(archiTmp);
    }
    else
    {
        printf("Haz superado los dias disponibles por semana para este plan.\n");
    }
}

void reiniciarAsistencia(stCeldaPlanes ADA[], int validos, int dni)
{
    nodoArbol *nodoTmp = buscarDNIEnADA(ADA, validos, dni);

    if (nodoTmp != NULL)
    {
        stArchivo archiTmp;
        stArchivo datosPlan = buscarPorDNIretornarTodaLaInformacion(dni);
        nodoTmp->cliente.diasConcurridosEstaSemana = 0;
        printf("Hemos reiniciado los dias de forma exitosa\n");
        archiTmp = formatoADA2Archi(datosPlan.idDePlan, datosPlan.plan, datosPlan.diasDelPlan, nodoTmp->cliente);
        mostrarUnStArchivo(archiTmp);
        modificarClienteEnElArchivo(archiTmp);
    }
    else
    {
        printf("Cliente no encontrado en el ADA\n");
    }
}

void eliminarCliente(stCeldaPlanes ADA[], int validos, int dni)
{
    nodoArbol * nodoTmp = buscarDNIEnADA(ADA, validos, dni);
    stArchivo archiTmp;
    stArchivo datosPlan = buscarPorDNIretornarTodaLaInformacion(dni);

    nodoTmp->cliente.bajaPasiva = 1;

    archiTmp = formatoADA2Archi(datosPlan.idDePlan, datosPlan.plan, datosPlan.diasDelPlan, nodoTmp->cliente);
    modificarClienteEnElArchivo(archiTmp);
}

void restaurarCliente(stCeldaPlanes ADA[], int validos, int dni)
{
    nodoArbol * nodoTmp = buscarDNIEnADA(ADA, validos, dni);
    stArchivo archiTmp;
    stArchivo datosPlan = buscarPorDNIretornarTodaLaInformacion(dni);

    nodoTmp->cliente.bajaPasiva = 0;

    archiTmp = formatoADA2Archi(datosPlan.idDePlan, datosPlan.plan, datosPlan.diasDelPlan, nodoTmp->cliente);
    modificarClienteEnElArchivo(archiTmp);
}

void cambiarDePlan(stCeldaPlanes ADA[], int validos, int dni, int nuevoID, char nuevoNombre[], int nuevoDias)
{
    stArchivo archiTmp;
    nodoArbol * nodoTmp = buscarDNIEnADA(ADA, validos, dni);
    stArchivo datosPlan = buscarPorDNIretornarTodaLaInformacion(dni);

    printf("pre-modificacion\n");
    mostrarUnStArchivo(datosPlan);


    datosPlan.idDePlan = nuevoID;
    strcpy(datosPlan.plan,nuevoNombre);
    datosPlan.diasDelPlan = nuevoDias;

    printf("pos-modificacion\n");

    mostrarUnStArchivo(datosPlan);


    archiTmp = formatoADA2Archi(datosPlan.idDePlan, datosPlan.plan, datosPlan.diasDelPlan, nodoTmp->cliente);
    modificarClienteEnElArchivo(archiTmp);
}


void modificarClienteEnElADAyEnElArchivo(stCeldaPlanes ADA[], int validos, int dni)
{
    nodoArbol * nodoTmp = buscarDNIEnADA(ADA, validos, dni);
    stArchivo archiTmp;
    stArchivo datosPlan = buscarPorDNIretornarTodaLaInformacion(dni);

    mostrarUnStArchivo(datosPlan);

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
elegirOpcionModificacion:
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
        printf("Operac  ion cancelada por el usuario.\n");
        break;
    default:
        printf("Opcion invalida, introduzca de nuevo la opcion: ");
        scanf("%d", &opcion);
        goto elegirOpcionModificacion;
        break;
    }

    archiTmp = formatoADA2Archi(datosPlan.idDePlan, datosPlan.plan, datosPlan.diasDelPlan, nodoTmp->cliente);
    mostrarLinea(20);
    mostrarUnStArchivo(archiTmp);
    mostrarLinea(20);
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
    FILE* file = fopen(ARCHIVO_PLANES, "rb+");

    if(file)
    {
        stArchivo archiAux;
        int encontrado = 0;  // Variable para indicar si se encontró el cliente

        while (fread(&archiAux, sizeof(stArchivo), 1, file) > 0)
        {
            if((archiAux.DNI == archi.DNI)||(strcmp(archiAux.nombre,archi.nombre) == 0 && strcmp(archiAux.apellido,archi.apellido) == 0) || ( strcmp(archiAux.domicilio,archi.domicilio) == 0))
            {
                fseek(file, sizeof(stArchivo)*-1, SEEK_CUR);//lo encotro y mueve el registro a una pos antes
                fwrite(&archi, sizeof(stArchivo), 1, file); //sobreescribe esa pos
                encontrado = 1;  // Se ha encontrado el cliente
                goto saltarWhile;   //quiero ver si tiene  el mismo efecto que el break;/ entiendo que el break sale del if pero no se si del while. just in case
                //break;  // Salir del bucle, ya que se encontró y modificó el cliente
            }
        }
saltarWhile:
        if (encontrado == 0)
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


/// FUNCIONES DE MUESTREO INICIO

void mostrarADA(stCeldaPlanes ADA[], int validos)
{
    for(int i = 0; i < validos; i++)
    {

        printf("\n");
        mostrarLinea(10);
        printf("Plan:    |\n");
        mostrarLinea(10);
        mostrarPlan(ADA[i]);
        mostrarLinea(15);
        printf("Clientes:     |\n");
        mostrarLinea(15);
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
    printf("ID del Plan ................ %i\n", plan.idPlan);
    printf("Nombre ..................... %s\n", plan.plan);
    printf("Dias ....................... %i\n", plan.diasDelPlan);
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
    float imc = peso / ( (estatura/100) * (estatura/100));
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

void controlCliente()
{
    valADAPlanes = archi2ADA(ADAPlanes, 10, ARCHIVO_PLANES);
    char decision = 's';
    while(tolower(decision) == 's')
    {
        marcoEsteticoSwitch("ACCIONES DE CLIENTE");
reset:
        mostrarLinea(40);
        printf("1- Calcular IMC (indice de masa corporal)\n");
        printf("2- Contar asistencia\n");
        printf("3- Ir al inventario\n");
        printf("0- Salir\n");
        mostrarLinea(40);

        printf("Su decision: ");
        fflush(stdin);
        scanf(" %d", &op);

        switch (op)
        {
        case 0:
            return;
            break;
        case 1:
            marcoEsteticoSwitch("CLIENTES > CALCULO DE IMC");
            printf("El IMC es un calculo hecho por la OMS para determinar si una persona\ntiene bajo peso, peso normal, sobrepeso u obesidad,\npara calcularlo necesitamos el peso y la estatura de la persona\n");
            mostrarLinea(50);

            printf("Introduzca el peso(en kg): ");
            scanf("%f", &peso);

            printf("Ahora, la altura(en cm): ");
            scanf("%f", &estatura);

            IMC = calcularIMC(peso, estatura);

            printf("Tu IMC es: %f, eso quiere decir: ", IMC);

            if(IMC < 18.5)
            {
                printf("Bajo peso\n");
            }
            else if(IMC >= 18.5 && IMC < 25)
            {
                printf("Normal\n");
            }
            else if(IMC >= 25 && IMC < 30)
            {
                printf("Sobrepeso\n");
            }
            else if(IMC >= 30)
            {
                printf("Obesidad\n");
            }

            break;
        case 2:
            marcoEsteticoSwitch("MANEJO DE CLIENTES > CONTAR ASISTENCIA");
            dniTmp = preguntarDNI();
            nodoTmp1 = buscarDNIEnADA(ADAPlanes, valADAPlanes, dniTmp);
            if(nodoTmp1)
            {
                contarAsistencia(ADAPlanes, valADAPlanes, dniTmp);
            }
            else
            {
                printf("El cliente no existe en el sistema.");
            }
            break;
        case 3:
            mainInventario();
            break;
        default:
            limpiarPantalla();
            printf("Opcion invalida\n");
            goto reset;
            break;
        }

        printf("Desea continuar?  ");
        printf("S / N\n");
        fflush(stdin);
        scanf("%c",&decision);
    }
}

void generarRutina3dias()
{
    srand(time(NULL));
    int numeroRandom=0;
    numeroRandom = rand()% 3 + 1;


    switch(numeroRandom)
    {
    case 1:
        printf("EJERCICIOS\n");
        printf("\n");
        mostrarLinea(70);
        printf("Dia 1: Pecho y triceps\n");


        printf("Pecho: Press inclinado 2x6-9| Press plano 2x 7-10| Cruce en polea(high to low) 2x 8-12\n");
        printf("Triceps: Extension de soga 3x 6-9 | press frances 3x 7-12\n");
        mostrarLinea(70);
        printf("Dia 2: Espalda y biceps\n");
        printf("Espalda: Jalon al pecho 2x6-9 | Remo caballo 3x 5-9 | Remo gironda 3x 7-12\n");
        printf("Biceps: Curl scott 3x 7-10 | Martillo en polea 3x 7-10\n");
        mostrarLinea(70);
        printf("Dia 3: Hombro y piernas\n");
        printf("Hombro: Laterales 3x 8-13 | Press militar 2x 5-8 | Pajaro en polea 2x 8-13\n");
        printf("Pierna: Hack squat 2x 5-9 | Prensa 45° 2x 7-12 | Extension de cuadriceps 2x 6-9\n");
        mostrarLinea(70);
        break;

    case 2:
        printf("EJERCICIOS\n");
        printf("\n");
        mostrarLinea(70);
        printf("Dia 1: Pecho y triceps\n");

        printf("Pecho: Press plano c/barra 2x4-6 | Press inclinado 2x6-9\n");
        printf("Triceps: Extension de soga 3x6-9 | press frances 3x7-12\n");
        mostrarLinea(70);
        printf("Dia 2: Espalda y biceps\n");

        printf("Espalda: Pull-up 3x8-12 | Remo sentado con barra T 2x7-10 | Pulldown en polea 3x8-12\n");
        printf("Biceps: Curl 21s 3x7-10 | Curl concentrado 2x8-12\n");
        mostrarLinea(70);
        printf("Dia 3: Hombro y piernas\n");

        printf("Hombro: Press militar 2x8-12 | Elevaciones laterales 3x8-12 | Face pull 2x10-15\n");
        printf("Pierna: Sentadillas 3x6-9 | Prensa horizontal 2x7-10 | Curl femoral 3x8-12\n");
        mostrarLinea(70);
        break;

    case 3:
        printf("EJERCICIOS\n");
        printf("\n");
        mostrarLinea(70);
        printf("Dia 1: Pecho y triceps\n");

        printf("Pecho: Fondos 3x8-12 | Pullover con mancuerna 2x10-15\n");
        printf("Triceps: Triceps dip 3x8-12 | Press frances con barra EZ 2x10-15\n");
        mostrarLinea(70);
        printf("Dia 2: Espalda y biceps\n");

        printf("Espalda: Peso muerto 3x5-8 | Hiperextensiones 3x10-15 | Pull-up agarre cerrado 2x8-12\n");
        printf("Biceps: Curl 21s 3x7-10 | Martillo en polea 2x8-12\n");
        mostrarLinea(70);
        printf("Dia 3: Hombro y piernas\n");


        printf("Hombro: Press militar 3x6-9 | Elevaciones laterales 3x8-12 | Face pull 2x10-15\n");
        printf("Pierna: Sentadillas  2x8-12 | Prensa 3x10-15 | Curl femoral 3x8-12\n");
        mostrarLinea(70);
        break;

    default:

        printf("Opción no válida\n");
    }

}
void generarRutina4dias()
{
    srand(time(NULL));
    int numeroRandom=0;


    numeroRandom = rand()% 3 + 1;



    switch(numeroRandom)
    {
    case 1:
        printf("EJERCICIOS");
        printf("\n");
        mostrarLinea(70);
        printf("Dia 1: Pecho,triceps y hombro\n");

        printf("Pecho: Press inclinado 2x6-9 | Press plano 2x 7-10 | Cruce en polea(high to low) 2x 8-12\n");
        printf("Triceps: Extension de soga 3x 6-9 | press frances 2x7-12\n");
        printf("Hombro: Laterales 2x6-12 | Pajaros en polea 2x7-15\n");

        mostrarLinea(70);
        printf("Dia 2: Espalda y biceps\n");
        printf("Espalda: Jalon al pecho 2x6-9 | Remo caballo 3x 5-9 | Remo gironda 3x 7-12\n");
        printf("Biceps: Curl scott 3x 7-10 | Martillo en polea 3x 7-10\n");
        mostrarLinea(70);
        printf("Dia 3: Piernas\n");
        printf("Pierna: Hack squat 2x 5-9 | Prensa 45° 2x 7-12 | Extension de cuadriceps 2x 6-9\n");
        mostrarLinea(70);
        printf("Dia 4: Pecho, triceps y hombro\n");
        printf("Pecho: Press inclinado 2x6-9 | Press plano 2x7-10 | Cruce en polea(high to low) 2x-8-12\n");
        printf("Triceps: Extension de soga 3x6-9 | Press frances 2x7-12\n");
        printf("Hombro: Laterales 2x6-12 | Pajaros en polea 2x7-15\n");
        mostrarLinea(70);
        break;

    case 2:
        printf("EJERCICIOS");
        printf("\n");
        mostrarLinea(70);
        printf("Dia 1: Pecho,triceps y hombro\n");

        printf("Pecho: Press plano c/mancuerna 2x6-9 | Press inclinado 2x 5-10 | Pec deck 2x 8-12\n");
        printf("Triceps: Fondos 3x 6-9 | press frances 2x7-12\n");
        printf("Hombro: Press militar 2x6-12 | Pajaros en polea 2x7-15\n");
        mostrarLinea(70);
        printf("Dia 2: Espalda y biceps\n");
        printf("Espalda: Jalon al pecho 2x6-9 | Remo a caballo 3x 5-9 | Remo gironda 3x 7-12\n");
        printf("Biceps: Curl sentado c/mancuerna 3x 5-10 | Martillo en polea 3x 5-10\n");
        mostrarLinea(70);
        printf("Dia 3: Piernas\n");
        printf("Pierna: Prensa 45° 2x5-10 | Extension de cuadriceps  2x 7-12 | Curl femoral 2x 6-9\n");
        mostrarLinea(70);
        printf("Dia 4: Pecho, triceps y hombro\n");
        printf("Pecho: Press plano c/mancuerna 2x6-9 | Press inclinado 2x 5-10 | Pec deck 2x 8-12\n");
        printf("Triceps: Fondos 3x 6-9 | press frances 2x7-12\n");
        printf("Hombro: Laterales en polea 2x6-12 | Pajaros en polea 2x7-15\n");
        mostrarLinea(70);
        break;

    case 3:
        printf("EJERCICIOS");
        printf("\n");
        mostrarLinea(70);
        printf("Dia 1: Pecho,triceps y hombro\n");
        printf("Pecho: Press inclinado c/barra 2x6-9 | press plano c/mancuerna 2x 5-10 | Cruce en polea 2x 8-12\n");
        printf("Triceps: Extension de soga 3x 6-9 | press frances 2x7-12\n");
        printf("Hombro: Laterales en polea 2x6-12 | Pajaros en polea 2x7-15\n");
        mostrarLinea(70);
        printf("Dia 2: Espalda y biceps\n");
        printf("Espalda: Jalon al pecho 2x6-9 | Remo caballo 3x 5-9 | Remo gironda 3x 7-12\n");
        printf("Biceps: Curl sentado c/mancuerna 3x 5-10 | Martillo en polea 3x 5-10\n");
        mostrarLinea(70);
        printf("Dia 3: Piernas\n");
        printf("Pierna: Sentadilla en smith 2x5-10 | Extension de cuadriceps  2x 7-12 | Curl femoral 2x 6-9\n");
        mostrarLinea(70);
        printf("Dia 4: Pecho, triceps y hombro\n");
        printf("Pecho: Press plano c/mancuerna 2x6-9 | Press inclinado 2x 5-10 | Peck deck 2x 8-12\n");
        printf("Triceps: Extension de soga 3x 6-9 | press frances 2x7-12\n");
        printf("Hombro: Laterales en polea 2x6-12 | Pajaros en polea 2x7-15\n");
        mostrarLinea(70);
        break;

    default:

        printf("Opción no válida\n");
    }

}


void generarRutina5dias()
{
    srand(time(NULL));
    int numeroRandom = rand() % 3 + 1;

    switch (numeroRandom)
    {
    case 1:
        printf("EJERCICIOS");
        printf("\n");
        mostrarLinea(70);
        printf("Dia 1: Pecho, triceps y hombro\n");
        printf("Press plano 4x8-12 | Fondos en paralelas 3x10-15 | Apertura en polea 3x12-15\n");
        printf("Fondos en paralelas 3x10-15 | Press frances 3x7-13\n");
        printf("Laterales en polea 2x7-13 | Pajaro en polea 2x7-15\n");
        mostrarLinea(70);

        printf("Dia 2: Espalda y biceps\n");
        printf("Pull-up 4x8-12 | Remo T 3x10-15 | Curl con barra 3x12-15\n");
        mostrarLinea(70);

        printf("Dia 3: Piernas \n");
        printf("Sentadillas 2x7-10 | Prensa 3x6-15 | Curl femoral 2x6-10\n");
        mostrarLinea(70);
        printf("Dia 4: Pecho, triceps y hombro\n");
        printf("Press inclinado 3x8-12 | Press plano 3x5-10 \n");
        printf("Press frances 3x8-12 | Extension de soga en polea 3x12-15\n");
        printf("Press militar 1x6-10 | Laterales 2x6-12\n");
        mostrarLinea(70);
        printf("Dia 5: Espalda y biceps\n");
        printf("Jalon al pecho 4x8-12 | Curl martillo 3x10-15 | Pulldown en polea 3x12-15 | Curl scot 3x 7-12\n");
        mostrarLinea(70);
        break;

    case 2:
        printf("EJERCICIOS");
        printf("\n");
        mostrarLinea(70);
        printf("Dia 1: Pecho, triceps y hombro\n");
        printf("Press inclinado 4x8-12 | Fondos en paralelas 3x10-15 | Apertura en polea 3x12-15\n");
        printf("Fondos en paralelas 3x10-15 | Press frances 3x7-13\n");
        printf("Laterales 2x7-13 | Pajaro en polea 2x7-15\n");
        mostrarLinea(70);
        printf("Dia 2: Espalda y biceps\n");
        printf("Pull-up 4x8-12 | Pulldown en polea 3x10-15 | Curl con barra 3x12-15\n");
        mostrarLinea(70);
        printf("Dia 3: Piernas\n");
        printf("Sentadillas 3x8-12 | Prensa 3x10-15 | Curl femoral 2x5-10\n");
        mostrarLinea(70);
        printf("Dia 4: Pecho, triceps y hombro\n");
        printf("Press inclinado 3x8-12 | Press plano 3x5-10 \n");
        printf("Press frances 3x8-12 | Extension de soga en polea 3x12-15\n");
        printf("Press militar 1x6-10 | Laterales 2x6-12\n");
        mostrarLinea(70);
        printf("Dia 5: Espalda y biceps\n");
        printf("Jalon al pecho 4x8-12 | Curl martillo 3x10-15 | Pulldown en polea 3x12-15\n");
        mostrarLinea(70);
        break;

    case 3:
        printf("EJERCICIOS");
        printf("\n");
        mostrarLinea(70);
        printf("Dia 1: Pecho, triceps y hombro\n");
        printf("Press inclinado 4x8-12 | Fondos en paralelas 3x10-15 | Apertura en polea 3x12-15\n");
        printf("Fondos en paralelas 3x10-15 | Press frances 3x7-13\n");
        printf("Laterales 2x7-13 | Pajaro en polea 2x7-15\n");

        mostrarLinea(70);
        printf("Dia 2: Espalda y biceps\n");
        printf("Jalon al pecho 2x8-12 | Remo T 2x10-15 | Curl con barra 3x12-15\n");

        mostrarLinea(70);
        printf("Dia 3: Piernas\n");
        printf("Sentadillas 4x8-12 | Prensa 3x10-15| Extension de cuadriceps 2x5-10\n");

        mostrarLinea(70);
        printf("Dia 4: Pecho, triceps y hombro\n");
        printf("Press inclinado 3x8-12 | Press plano 3x5-10 \n");
        printf("Press frances 3x8-12 | Extension de soga en polea 3x12-15\n");
        printf("Press militar 1x6-10 | Laterales 2x6-12\n");
        mostrarLinea(70);
        printf("Dia 5: Espalda y biceps\n");
        printf("Jalon al pecho 4x8-12 | Curl martillo 3x10-15 | Pulldown en polea 3x12-15\n");
        mostrarLinea(70);

        break;

    default:
        printf("Opción no válida\n");
    }
}

void generarRutina6dias()
{
    srand(time(NULL));
    int numeroRandom = rand() % 3 + 1;

    switch (numeroRandom)
    {
    case 1:

        printf("EJERCICIOS");
        printf("\n");
        mostrarLinea(70);
        printf("Dia 1: Pecho, triceps y hombro\n");
        printf("Press plano 2x5-7 | Press inclinado 2x6-9\n");
        printf("Fondos en paralelas 3x10-15 | Extension de soga en polea 3x6-10\n");
        printf("Press militar 2x5-10 | laterales 2x6-12 | Pajarito en polea 2x5-10\n");
        mostrarLinea(70);
        printf("Dia 2: Espalda y biceps\n");
        printf("Remo T 2x5-9 | Pullover 2x10-15 | Curl con barra 3x12-15| Martillo c/mancuerna 3x5-9\n");
        mostrarLinea(70);
        printf("Dia 3: Piernas\n");
        printf("Sentadillas 2x6-9 | Prensa 2x10-15 |  Curl isquios 2x- 6-9\n");
        mostrarLinea(70);
        printf("Dia 4: Pecho, triceps y hombro\n");
        printf("Press plano 2x5-7 | Press inclinado 2x6-9\n");
        printf("Fondos en paralelas 3x10-15 | Extension de soga en polea 3x6-10\n");
        printf("Press militar 2x5-10 | laterales 2x6-12 | Pajarito en polea 2x5-10\n");
        mostrarLinea(70);
        printf("Dia 5: Espalda y biceps\n");
        printf("Jalon al pecho 2x8-12 | Curl martillo 3x10-15 | Pullover en polea 3x12-15 | Curl scot 3x 7-12\n");
        mostrarLinea(70);
        printf("Dia 6: Piernas\n");
        printf("Sentadillas 2x8-12 | Prensa 3x10-15 | Press militar 3x12-15 | Laterales 3x 8-13\n");

        break;

    case 2:
        printf("EJERCICIOS");
        printf("\n");
        mostrarLinea(70);
        printf("Dia 1: Pecho, triceps y hombro\n");
        printf("Press plano 2x5-7 | Press inclinado 2x6-9\n");
        printf("Press frances 3x10-15 | Extension de soga en polea 3x6-10\n");
        printf("Press militar 2x5-10 | laterales 2x6-12 | Pajarito en polea 2x5-10\n");
        mostrarLinea(70);
        printf("Dia 2: Espalda y biceps\n");
        printf("Pull-up 4x8-12 | Pulldown en polea 3x10-15 | Curl con barra 3x12-15\n");
        mostrarLinea(70);
        printf("Dia 3: Piernas\n");
        printf("Sentadillas 4x8-12 | Prensa 3x10-15 | Press militar 3x12-15 | Laterales 3x 6-8\n");
        mostrarLinea(70);
        printf("Dia 4: Pecho, triceps y hombro\n");
        printf("Press plano 2x5-7 | Press inclinado 2x6-9\n");
        printf("Press frances | Extension de soga en polea 3x6-10\n");
        printf("Press militar 2x5-10 | laterales 2x6-12 | Pajarito en polea 2x5-10\n");
        mostrarLinea(70);
        printf("Dia 5: Espalda y biceps\n");
        printf("Jalon al pecho 4x8-12 | Curl martillo 3x10-15 | Pulldown en polea 3x12-15\n");
        mostrarLinea(70);
        printf("Dia 6: Piernas\n");
        printf("Sentadillas 4x8-12 | Prensa 3x10-15 | Press militar 3x12-15 | Laterales 3x 7-12\n");
        mostrarLinea(70);
        break;

    case 3:

        printf("EJERCICIOS");
        printf("\n");
        mostrarLinea(70);
        printf("Dia 1: Pecho, triceps y hombro\n");
        printf("Press plano 2x5-7 | Press inclinado 2x6-9\n");
        printf("Press frances 3x10-15 | Extension de soga en polea 3x6-10\n");
        printf("Press militar 2x5-10 | laterales 2x6-12 | Pajarito en polea 2x5-10\n");
        mostrarLinea(70);
        printf("Dia 2: Espalda y biceps\n");
        printf("Jalon al pecho 2x8-12 | Remo T 2x10-15 | Curl con barra 3x12-15\n");
        mostrarLinea(70);
        printf("Dia 3: Piernas\n");
        printf("Sentadillas 4x8-12 | Prensa 3x10-15 | Press militar 3x12-15 | Laterales 3x 7-12\n");
        mostrarLinea(70);
        printf("Dia 4: Pecho, triceps y hombro\n");
        printf("Press plano 2x5-7 | Press inclinado 2x6-9\n");
        printf("Press frances | Extension de soga en polea 3x6-10\n");
        printf("Press militar 2x5-10 | laterales 2x6-12 | Pajarito en polea 2x5-10\n");
        mostrarLinea(70);
        printf("Dia 5: Espalda y biceps\n");
        printf("Jalon al pecho 4x8-12 | Curl martillo 3x10-15 | Pulldown en polea 3x12-15\n");
        mostrarLinea(70);
        printf("Dia 6: Piernas\n");
        printf("Sentadillas 4x8-12 | Prensa 3x10-15 | Press militar 3x12-15 | Laterales 3x 8-13\n");
        mostrarLinea(70);
        break;

    default:
        printf("Opción no válida\n");
    }
}


char* generarRutinaMuscular(int dias)
{
    char* rutina = (char*)malloc(MAX_LONGITUD_RUTINA * sizeof(char));

    if (rutina == NULL)
    {
        printf("Error: No se pudo asignar memoria para la rutina.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(rutina, "Rutina:\n");

    switch (dias)
    {
    case 3:

        strcat(rutina, "Dia 1: Pecho y triceps\n");
        strcat(rutina, "Dia 2: Espalda y biceps\n");
        strcat(rutina, "Dia 3: Piernas y hombros\n");
        break;
    case 4:
        strcat(rutina, "Dia 1: Pecho, triceps y hombro\n");
        strcat(rutina, "Dia 2: Espalda y biceps\n");
        strcat(rutina, "Dia 3: Piernas\n");
        strcat(rutina, "Dia 4: Pecho, triceps y hombro\n");

        break;
    case 5:

        strcat(rutina, "Dia 1: Pecho, triceps y hombro\n");
        strcat(rutina, "Dia 2: Espalda y biceps\n");
        strcat(rutina, "Dia 3: Piernas\n");
        strcat(rutina, "Dia 4: Pecho, triceps y hombro\n");
        strcat(rutina, "Dia 5: Espalda y biceps\n");

        break;

    case 6:

        strcat(rutina, "Dia 1: Pecho, triceps y hombro\n");
        strcat(rutina, "Dia 2: Espalda y biceps\n");
        strcat(rutina, "Dia 3: Piernas\n");
        strcat(rutina, "Dia 4: Pecho, triceps y hombro\n");
        strcat(rutina, "Dia 5: Espalda y biceps\n");
        strcat(rutina, "Dia 6: Piernas\n");
        break;
    }

    return rutina;
}

