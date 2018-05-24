#include <stdio.h>
#include <stdbool.h>
#include "sombrero.h"

#define F_SUPER_ATRIBUTO 8

void procesar_atributo(int *atributo) {
    scanf("%i", atributo);
    if (*atributo < 0 || *atributo > 10) {
        printf("Por favor ingrese un numero dentro del rango (Entre 0 y 10) \n");
        procesar_atributo(atributo);
    }
}

/*pre: Funcion que recibe los atributos de la persona*/
/*post: Comprueba que no tenga mas de 2 super atributos*/
bool excede_super_atributos(int fuerza, int valor, int inteligencia, int ingenio, int dedicacion) {
    int cantidad_super_atributos = 0;
    if (fuerza > F_SUPER_ATRIBUTO) {
        cantidad_super_atributos++;
    }
    if (valor > F_SUPER_ATRIBUTO) {
        cantidad_super_atributos++;
    }
    if (inteligencia > F_SUPER_ATRIBUTO) {
        cantidad_super_atributos++;
    }
    if (ingenio > F_SUPER_ATRIBUTO) {
        cantidad_super_atributos++;
    }
    if (dedicacion > F_SUPER_ATRIBUTO) {
        cantidad_super_atributos++;
    }
    return cantidad_super_atributos > 2;
}

void solicitar_atributos (int  *fuerza, int  *valor, int  *inteligencia, int  *ingenio, int  *dedicacion) {
    printf("Ingrese la fuerza \n");
    procesar_atributo(fuerza);

    printf("Ingrese el valor \n");
    procesar_atributo(valor);

    printf("Ingrese la inteligencia \n");
    procesar_atributo(inteligencia);

    printf("Ingrese el ingenio \n");
    procesar_atributo(ingenio);

    printf("Ingrese la dedicacion \n");
    procesar_atributo(dedicacion);

    if (excede_super_atributos(*fuerza, *valor, *inteligencia, *ingenio, *dedicacion)) {
        printf("Solo pueden haber 3 super atributos como maximo (Atributos mayores a 8). Por favor ingrese los valores nuevamente \n");
        solicitar_atributos(fuerza, valor, inteligencia, ingenio, dedicacion);
    }
}

/*pre: Funcion que recibe los atributos de la persona*/
/*post: retorna la inicial de que casa pertenece */
char decidir_casa(int fuerza, int valor, int inteligencia, int ingenio, int dedicacion) {
    if(inteligencia > 8 && ingenio > 8) {
        return RAVENCLAW;
    } else if(fuerza > 8 && valor > 8 && ingenio < 5) {
        return GRYFFINDOR;
    } else if(inteligencia > 5 && inteligencia < 8 && ingenio > 8) {
        return SLYTHERIN;
    } else {
        return HUFFLEPUFF;
    }
}

char obtener_casa() {
    int fuerza = 0, valor = 0, inteligencia = 0;
    int ingenio = 0, dedicacion = 0;
    solicitar_atributos(&fuerza, &valor, &inteligencia, &ingenio, &dedicacion);
    return decidir_casa(fuerza, valor, inteligencia, ingenio, dedicacion);
}