#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "const.h"
#include "controlAdmin.h"
#include "controlEmpleado.h"
#include "controlCliente.h"
#include "manejoDeClientes.h"
#include "manejoDePagos.h"
#include "manejoEmpleado.h"
#include "tipoUsuario.h"

void controlCliente()
{


    float peso;
    float estatura;
    float IMC;
    int decision = 1;
    while(decision == 1)
    {
        marcoEsteticoSwitch("ACCIONES DE CLIENTE");
reset:
        mostrarLinea(40);
        printf("1- Calcular IMC (indice de masa corporal)\n");
        printf("2- Contar asistencia\n");
        printf("0- Salir\n");
        mostrarLinea(40);

        printf("Su decision: ");
        fflush(stdin);
        scanf(" %d", &decision);

        switch (decision)
        {
        case 0:
            return;
            break;
        case 1:
            marcoEsteticoSwitch("CLIENTES > CALCULO DE IMC"); //
            printf("El IMC es un calculo hecho por la OMS para determinar si una persona\ntiene bajo peso, peso normal, sobrepeso, u obesidad,\npara calcularlo necesitamos el peso y la estatura de la persona\n");
            mostrarLinea(50);

            printf("Introduzca el peso(en kg): ");
            scanf("%f", &peso);

            printf("Ahora, la altura(en cm): ");
            scanf("%f", &estatura);

            IMC = calcularIMC(peso, estatura);

            printf("Tu IMC es: %f.2, eso quiere decir: ", IMC);

            if(IMC < 18.5)
            {
                printf("Bajo peso\n");
            }
            else if(IMC >= 18.5 && IMC < 25)
            {
                printf("Peos Normal\n");
            }
            else if(IMC >= 25 && IMC < 30)
            {
                printf("Sobrepeso\n");
            }
            else if(IMC >= 30)
            {
                printf("Obesidad\n");
            }
            limpiarPantalla();
            break;
        case 2:
            marcoEsteticoSwitch("CLIENTES > CONTAR ASISTENCIA");
            dniTmp = preguntarDNI();
            nodoTmp1 = buscarDNIEnADA(ADAPlanes, valADAPlanes, dniTmp);
            if(nodoTmp1)
            {
                contarAsistencia(ADAPlanes, valADAPlanes, dniTmp);
                ///sigue pasando lo mismo de siempre, no podemos usar variable de otra lib. sin hacer autenticas BARBARIDADES :|
            }
            else
            {
                printf("El cliente no existe en el sistema.");
            }
            limpiarPantalla();
            break;
        default:
            limpiarPantalla(); /// maybe???
            printf("Opcion invalida\n");
            goto reset;
            break;
        }
    }
}







