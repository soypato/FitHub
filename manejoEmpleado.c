///sector manejo de empleados

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "ducktime.h"
#include "manejoDeClientes.h"
#include "const.h"
#include "tipoUsuario.h"
#include "manejoEmpleado.h"

const char Registro_Empleados[]="registroEmpleados.dat";

void imprimirMenuManejoEmpleados()
{
    printf("1- Ingresar nuevo empleado\n");
    printf("2- Mostrar todos los empleados activos\n");
    printf("3- Mostrar empleados por legajo\n");
    printf("4- Mostrar empleados por DNI\n");
    printf("5- Mostrar empleados por Edad\n");
    printf("6- Mostrar empleados despedidos\n");
    printf("7- Despedir empleado\n");
    printf("8- Re-Contratar empleado\n");
    printf("9- Modificar empleado\n");
    printf("10- Exportar a Excel mediante CSV\n");
    printf("0- Volver\n");
    mostrarLinea(40);
}

int mainEmpleados()
{
    limpiarPantalla();
    nodoListaEmpleados * nodoTmp = inicListaEmpleados();
    nodoListaPagos * lista = inicListaEmpleados();
    int opcion;
    char decision = 's';
    char continuar = 's';
    while (tolower(decision) == 's' || tolower(decision) == 'y')
    {
        // Cada vez que se ejecute el men� refrescamos los datos de archivos
        marcoEsteticoSwitch("MANEJO DE EMPLEADOS");
        imprimirMenuManejoEmpleados();
        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);
        reset:
        switch(opcion)
        {
        case 1:
            while(tolower(continuar) == 's' || tolower(continuar) == 'y')
            {
                marcoEsteticoSwitch("MANEJO DE EMPLEADOS > INGRESAR EMPLEADO");
                nodoTmp = crearNuevoEmpleado(nodoTmp);
                lista = agregarNodoInicioEmpleado(lista, nodoTmp);

                printf("Desea ingresar otro empleado? (s/n): ");
                fflush(stdin);
                scanf("%c", &continuar);
                limpiarPantalla();
            }
            guardarEmpleadosEnArchivo(lista);
            continuar = 's';
            break;
        case 2:
            marcoEsteticoSwitch("MANEJO DE EMPLEADOS > MOSTRAR TODOS LOS EMPLEADOS");
            mostrarEmpleadosDesdeArchivo();
            break;
        case 3:
            marcoEsteticoSwitch("MANEJO DE EMPLEADOS > MOSTRAR EMPLEADOS POR LEGAJO");
            mostrarEmpleadosDesdeArchivoOrdenadasPorLegajo();
            break;
        case 4:
            marcoEsteticoSwitch("MANEJO DE EMPLEADOS > MOSTRAR EMPLEADOS POR DNI");
            mostrarEmpleadosDesdeArchivoOrdenadasPorDNI();
            break;
        case 5:
            marcoEsteticoSwitch("MANEJO DE EMPLEADOS > MOSTRAR EMPLEADOS POR EDAD");
            mostrarEmpleadosDesdeArchivoOrdenadasPorEdad();
            break;
        case 6:
            marcoEsteticoSwitch("MANEJO DE EMPLEADOS > MOSTRAR EMPLEADOS DESPEDIDOS");
            mostrarEmpleadosDadosDeBaja();
            break;
        case 7:
            marcoEsteticoSwitch("MANEJO DE EMPLEADOS > DESPEDIR EMPLEADO");
            darDeBajaUnEmpleado();
            break;
        case 8:
            marcoEsteticoSwitch("MANEJO DE EMPLEADOS > RE-CONTRATAR EMPLEADO");
            reactivarEmpleado();
            break;
        case 9:
            marcoEsteticoSwitch("MANEJO DE EMPLEADOS > MODIFICAR DATOS EMPLEADO");
            modificarEmpleado();
            break;
        case 10:
            marcoEsteticoSwitch("MANEJO DE CLIENTES > EXPORTAR A EXCEL");
            exportarEmpleadosCSV();
            printf("empleados.csv exportado\n");
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

void exportarEmpleadosCSV()
{
    FILE *archivo = fopen(Registro_Empleados, "rb"); // Abre el archivo en modo de leer binario
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo de empleados para lectura.\n");
        return;
    }

    FILE *archivoCSV = fopen("empleados.csv", "w");
    if (archivoCSV == NULL)
    {
        printf("Error al abrir el archivo CSV para escritura.\n");
        fclose(archivo);
        return;
    }

    fprintf(archivoCSV, "Nombre y Apellido,Legajo,Edad,DNI,Categoria,Baja Pasiva\n");

    stEmpleado empleado;

    while (fread(&empleado, sizeof(stEmpleado), 1, archivo) > 0)
    {
        fprintf(archivoCSV, "%s,%d,%d,%d,%s,%d\n",
                empleado.nombreYApellido,
                empleado.legajo,
                empleado.edad,
                empleado.DNI,
                empleado.categoria,
                empleado.bajaPasiva);
    }

    fclose(archivo);
    fclose(archivoCSV);

}


/// FUNCIONES TDA stEMPLEADOS ///

nodoListaEmpleados * inicListaEmpleados ()
{
    return NULL;
}

nodoListaEmpleados * crearNodoListaEmpleados (stEmpleado empleado)
{
    nodoListaEmpleados * nuevo = (nodoListaEmpleados*)malloc(sizeof(nodoListaEmpleados));

    nuevo->empleado = empleado;
    nuevo->siguiente = NULL;

    return nuevo;
}

nodoListaEmpleados * agregarNodoInicioEmpleado(nodoListaEmpleados * lista, nodoListaEmpleados * nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        nuevo->siguiente = lista;
        lista = nuevo;
    }
    return lista;
}

nodoListaEmpleados * agregarNodoOrdenadoPorNomYApeEmpleado(nodoListaEmpleados * lista, nodoListaEmpleados * nuevo)
{
    nodoListaEmpleados * actual = lista;
    nodoListaEmpleados * anterior = inicListaEmpleados();
    while(actual!= NULL && strcmp(nuevo->empleado.nombreYApellido, actual->empleado.nombreYApellido) > 0 )
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if(anterior==NULL)
    {
        nuevo->siguiente = lista;
        lista = nuevo;
    }
    else
    {
        anterior->siguiente = nuevo;
        nuevo->siguiente = actual;
    }
    return lista;
}

// Agrega un nodo a la lista de forma ordenada por el campo 'legajo'
nodoListaEmpleados * agregarNodoOrdenadoPorLegajoEmpleado(nodoListaEmpleados *lista, nodoListaEmpleados *nuevoNodo)
{
    if (lista == NULL || nuevoNodo->empleado.legajo < lista->empleado.legajo)
    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    else
    {
        nodoListaEmpleados * actual = lista;

        while (actual->siguiente != NULL && actual->siguiente->empleado.legajo < nuevoNodo->empleado.legajo)
        {
            actual = actual->siguiente;
        }

        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
    }

    return lista;
}

// Agrega un nodo a la lista de forma ordenada por el campo 'DNI'
nodoListaEmpleados *agregarNodoOrdenadoPorDNIEmpleado(nodoListaEmpleados *lista, nodoListaEmpleados *nuevoNodo)
{
    if (lista == NULL || nuevoNodo->empleado.DNI < lista->empleado.DNI)
    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    else
    {
        nodoListaEmpleados *actual = lista;

        while (actual->siguiente != NULL && actual->siguiente->empleado.DNI < nuevoNodo->empleado.DNI)
        {
            actual = actual->siguiente;
        }

        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
    }

    return lista;
}

nodoListaEmpleados *agregarNodoOrdenadoPorEdadEmpleado(nodoListaEmpleados *lista, nodoListaEmpleados *nuevoNodo)
{
    if (lista == NULL || nuevoNodo->empleado.edad < lista->empleado.edad)
    {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    else
    {
        nodoListaEmpleados *actual = lista;

        while (actual->siguiente != NULL && actual->siguiente->empleado.edad < nuevoNodo->empleado.edad)
        {
            actual = actual->siguiente;
        }

        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
    }

    return lista;
}

/// FIN FUNCIONES TDA stEMPLEADOS ///

/// FUNCIONES MANEJO DE EMPLEADOS ///

nodoListaEmpleados * crearNuevoEmpleado()
{
    stEmpleado nuevoEmpleado;
    int categoria;
    printf("Ingrese nombre y apellido: ");
    fflush(stdin);
    gets(nuevoEmpleado.nombreYApellido);

    printf("Ingrese legajo: ");
    scanf("%d", &nuevoEmpleado.legajo);

    printf("Ingrese edad: ");
    scanf("%d", &nuevoEmpleado.edad);

    printf("Ingrese DNI: ");
    scanf("%d", &nuevoEmpleado.DNI);

    printf("Seleccione la categoria del empleado:\n");
    mostrarLinea(120);
    printf("1. Administrativo\
            2. Entrenador\
            3. Recepcionista\
            \n");
    mostrarLinea(120);
    printf("Ingrese el numero correspondiente a la categoria: ");
    scanf("%d", &categoria);


    switch(categoria)
    {
    case 1:
        strcpy(nuevoEmpleado.categoria,"Administrativo");
        break;
    case 2:
        strcpy(nuevoEmpleado.categoria,"Entrenador");
        break;
    case 3:
        strcpy(nuevoEmpleado.categoria,"Recepcionista");
        break;
    default:
        break;
    }

    nuevoEmpleado.bajaPasiva = 0;

    nodoListaEmpleados * nuevoNodo = crearNodoListaEmpleados(nuevoEmpleado);

    return nuevoNodo;
}

void mostrarNodoEmpleado(nodoListaEmpleados *nodo)
{
    mostrarLinea(45);
    printf("Nombre y Apellido: %s\n", nodo->empleado.nombreYApellido);
    printf("Legajo: %d\n", nodo->empleado.legajo);
    printf("Edad: %d\n", nodo->empleado.edad);
    printf("DNI: %d\n", nodo->empleado.DNI);
    printf("Categoria: %s\n", nodo->empleado.categoria);
    mostrarLinea(45);
}

void mostrarListaEmpleados(nodoListaEmpleados *lista)
{
    nodoListaEmpleados *actual = lista;

    if (actual == NULL)
    {
        printf("La lista de empleados está vacía.\n");
    }
        else
    {
        while (actual != NULL)
        {
            if(actual->empleado.bajaPasiva == 0)
            {
            mostrarNodoEmpleado(actual);
            actual = actual->siguiente;
            }
        }
    }
}

void guardarEmpleadosEnArchivo(nodoListaEmpleados * lista)
{
    FILE * archivo = fopen(Registro_Empleados, "ab"); // Abre el archivo en modo de agregar binario

    if (archivo != NULL)
    {
        nodoListaEmpleados * temp = lista;

        while (temp != NULL)
        {
            fwrite(&(temp->empleado), sizeof(stEmpleado), 1, archivo);
            temp = temp->siguiente;
        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para guardar los empleados.\n");
    }
}


void mostrarEmpleadosDesdeArchivo()
{
    FILE *archivo = fopen(Registro_Empleados, "rb"); // Abre el archivo en modo de leer binario

    if (archivo != NULL)
    {
        stEmpleado empleado;
        while (fread(&empleado, sizeof(stEmpleado), 1, archivo) > 0)
        {
            if (empleado.bajaPasiva == 0)
            {
                mostrarNodoEmpleado(crearNodoListaEmpleados(empleado));
            }
        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para leer los empleados.\n");
    }
}


void mostrarEmpleadosDesdeArchivoOrdenadasPorLegajo()
{
    FILE *archivo = fopen(Registro_Empleados, "rb"); // Abre el archivo en modo de leer binario

    if (archivo != NULL)
    {
        nodoListaPagos *lista = inicLista();
        stEmpleado empleado;

        // Leer las facturas y agregarlas a la lista
        while (fread(&empleado, sizeof(stEmpleado), 1, archivo) > 0)
        {
            nodoListaEmpleados * nuevoNodo = crearNodoListaEmpleados(empleado);
            lista = agregarNodoOrdenadoPorLegajoEmpleado(lista, nuevoNodo);
        }

        // Mostrar las facturas ordenadas por monto
        mostrarListaEmpleados(lista);

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para leer los empleados.\n");
    }
}


void mostrarEmpleadosDesdeArchivoOrdenadasPorDNI()
{
    FILE *archivo = fopen(Registro_Empleados, "rb"); // Abre el archivo en modo de leer binario

    if (archivo != NULL)
    {
        nodoListaPagos *lista = inicLista();
        stEmpleado empleado;

        // Leer las facturas y agregarlas a la lista
        while (fread(&empleado, sizeof(stEmpleado), 1, archivo) > 0)
        {
            nodoListaEmpleados * nuevoNodo = crearNodoListaEmpleados(empleado);
            lista = agregarNodoOrdenadoPorDNIEmpleado(lista, nuevoNodo);
        }

        // Mostrar las facturas ordenadas por monto
        mostrarListaEmpleados(lista);

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para leer los empleados.\n");
    }
}


void mostrarEmpleadosDesdeArchivoOrdenadasPorEdad()
{
    FILE *archivo = fopen(Registro_Empleados, "rb"); // Abre el archivo en modo de leer binario

    if (archivo != NULL)
    {
        nodoListaPagos *lista = inicLista();
        stEmpleado empleado;

        // Leer las facturas y agregarlas a la lista
        while (fread(&empleado, sizeof(stEmpleado), 1, archivo) > 0)
        {
            nodoListaEmpleados * nuevoNodo = crearNodoListaEmpleados(empleado);
            lista = agregarNodoOrdenadoPorEdadEmpleado(lista, nuevoNodo);
        }

        // Mostrar las facturas ordenadas por monto
        mostrarListaEmpleados(lista);

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para leer los empleados.\n");
    }
}


void darDeBajaUnEmpleado()
{
    FILE *archivo = fopen(Registro_Empleados, "rb+"); // Abre el archivo en modo de leer y escribir binario

    if (archivo != NULL)
    {
        stEmpleado empleado;
        int dniBuscar;

        // Solicitar al usuario el DNI de la factura a modificar
        printf("Ingrese el DNI del empleado a quitar: ");
        scanf("%d", &dniBuscar);

        // Buscar la factura en el archivo
        int encontrado = 0;
        while (fread(&empleado, sizeof(stEmpleado), 1, archivo) > 0)
        {
            if (empleado.DNI == dniBuscar)
            {
                encontrado = 1;

                // Mostrar la factura actual
                printf("Empleado encontrado:\n");
                mostrarNodoEmpleado(crearNodoListaEmpleados(empleado));

                // Solicitar al usuario si desea dar de baja la factura
                int opcion;
                printf("Desea dar de baja este empleado? (1: Si / 0: No): ");
                scanf("%d", &opcion);

                // Modificar el campo bajaPasiva según la opción del usuario
                if (opcion == 1)
                {
                    empleado.bajaPasiva = 1;
                    fseek(archivo, -sizeof(stEmpleado), SEEK_CUR); // Retrocede un registro para escribir sobre el registro actual
                    fwrite(&empleado, sizeof(stEmpleado), 1, archivo);
                    printf("Empleado dado de baja exitosamente.\n");
                }
                else
                {
                    printf("Operacion cancelada. El empleado no fue modificado.\n");
                }

                break; // No es necesario seguir buscando
            }
        }

        if (!encontrado)
        {
            printf("Empleado no encontrado.\n");
        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para modificar la factura.\n");
    }
}


void reactivarEmpleado()
{
    FILE *archivo = fopen(Registro_Empleados, "rb+"); // Abre el archivo en modo de leer y escribir binario

    if (archivo != NULL)
    {
        stEmpleado empleado;
        int dniBuscar;

        // Solicitar al usuario el DNI de la factura a reactivar
        printf("Ingrese el DNI del empleado a reactivar: ");
        scanf("%d", &dniBuscar);

        // Buscar la factura en el archivo
        int encontrado = 0;
        while (fread(&empleado, sizeof(stEmpleado), 1, archivo) > 0)
        {
            if (empleado.DNI == dniBuscar)
            {
                encontrado = 1;

                // Mostrar la factura actual
                printf("Empleado encontrada:\n");
                mostrarNodoEmpleado(crearNodoListaEmpleados(empleado));

                // Solicitar al usuario si desea reactivar la factura
                int opcion;
                printf("Desea reactivar este empleado? (1: Si / 0: No): ");
                scanf("%d", &opcion);

                // Modificar el campo bajaPasiva según la opción del usuario
                if (opcion == 1)
                {
                    empleado.bajaPasiva = 0;
                    fseek(archivo, -sizeof(stEmpleado), SEEK_CUR); // Retrocede un registro para escribir sobre el registro actual
                    fwrite(&empleado, sizeof(stEmpleado), 1, archivo);
                    printf("Empleado reactivada exitosamente.\n");
                }
                else
                {
                    printf("Operacion cancelada. El empleado no fue modificado.\n");
                }

                break; // No es necesario seguir buscando
            }
        }

        if (!encontrado)
        {
            printf("Empleado no encontrado.\n");
        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para modificar el empleado.\n");
    }
}


void mostrarEmpleadosDadosDeBaja()
{
    FILE *archivo = fopen(Registro_Empleados, "rb"); // Abre el archivo en modo de leer binario

    if (archivo != NULL)
    {
        stEmpleado empleado;
        int contadorEmpleado = 0;

        while (fread(&empleado, sizeof(stEmpleado), 1, archivo) > 0)
        {
            if (empleado.bajaPasiva == 1)
            {
                mostrarNodoEmpleado(crearNodoListaEmpleados(empleado));
                contadorEmpleado++;
            }
        }

        if (contadorEmpleado == 0)
        {
            printf("No hay empleados dados de baja en el archivo.\n");
        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para leer los empleados.\n");
    }
}


void modificarEmpleado()
{
    FILE *archivo = fopen(Registro_Empleados, "rb+"); // Abre el archivo en modo de leer y escribir binario

    if (archivo != NULL)
    {
        stEmpleado empleado;
        int dniBuscar;

        // Solicitar al usuario el DNI del empleado a modificar
        printf("Ingrese el DNI del empleado a modificar: ");
        scanf("%d", &dniBuscar);

        // Buscar el empleado en el archivo
        int encontrado = 0;
        while (fread(&empleado, sizeof(stEmpleado), 1, archivo) > 0)
        {
            if (empleado.DNI == dniBuscar)
            {
                encontrado = 1;

                // Mostrar el empleado actual
                printf("Empleado encontrado:\n");
                mostrarNodoEmpleado(crearNodoListaEmpleados(empleado));

                // Menú de opciones para modificar campos
                int opcion;
                do
                {
                    printf("\nSeleccione el campo a modificar:\n");
                    printf("1- Nombre y Apellido\n");
                    printf("2- Legajo\n");
                    printf("3- Edad\n");
                    printf("4- DNI\n");
                    printf("5- Categoría\n");
                    printf("0- Salir\n");
                    printf("Ingrese la opcion: ");
                    scanf("%d", &opcion);

                    switch (opcion)
                    {
                    case 1:
                        printf("Ingrese el nuevo Nombre y Apellido: ");
                        fflush(stdin);
                        gets(empleado.nombreYApellido);
                        break;
                    case 2:
                        printf("Ingrese el nuevo Legajo: ");
                        scanf("%d", &empleado.legajo);
                        break;
                    case 3:
                        printf("Ingrese la nueva Edad: ");
                        scanf("%d", &empleado.edad);
                        break;
                    case 4:
                        printf("Ingrese el nuevo DNI: ");
                        scanf("%d", &empleado.DNI);
                        break;
                    case 5:
                        printf("Seleccione la nueva categoría:\n");
                        printf("1. Administrativo\n");
                        printf("2. Entrenador\n");
                        printf("3. Recepcionista\n");
                        printf("Ingrese el número correspondiente a la categoría: ");
                        int categoria;
                        scanf("%d", &categoria);
                        switch (categoria)
                        {
                        case 1:
                            strcpy(empleado.categoria, "Administrativo");
                            break;
                        case 2:
                            strcpy(empleado.categoria, "Entrenador");
                            break;
                        case 3:
                            strcpy(empleado.categoria, "Recepcionista");
                            break;
                        }
                    case 0:
                        break; // Salir del bucle
                    default:
                        printf("Opcion invalida, intente nuevamente.\n");
                        break;
                    }
                } while (opcion != 0);

                // Actualizar el registro en el archivo
                fseek(archivo, -sizeof(stEmpleado), SEEK_CUR); // Retrocede un registro para escribir sobre el registro actual
                fwrite(&empleado, sizeof(stEmpleado), 1, archivo);
                printf("Empleado modificado exitosamente.\n");

                break; // No es necesario seguir buscando
            }
        }

        if (!encontrado)
        {
            printf("Empleado no encontrado.\n");
        }

        fclose(archivo);
    }
    else
    {
        printf("Error al abrir el archivo para modificar el empleado.\n");
    }
}


