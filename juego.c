#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "quidditch.h"
#include "sombrero.h"

int const MOVIMIENTOS_HUFF = 2;

int main() {
    char casa;
    char campo[FILAS_CAMPO][COLS_CAMPO];
    srand ((unsigned int)time(NULL)); //Inicializamos seed para el random
    casa = obtener_casa();
    juego_t juego;
    int i = 0;
    char movimiento;
    inicializar_juego(campo, casa, &juego);
    while(!finalizo_juego(&juego)) {
        if(juego.casa == HUFFLEPUFF) {
            i = 0;
            while(i < MOVIMIENTOS_HUFF && !finalizo_juego(&juego)) {
                movimiento = pedir_movimiento(juego.posicion_jugador);
                mover_jugador(campo, movimiento, &juego);
                imprimir_juego(campo, juego);
                i++;
            }
        } else {
            movimiento = pedir_movimiento(juego.posicion_jugador);
            mover_jugador(campo, movimiento, &juego);
        }
        if(!finalizo_juego(&juego)) {
            mover_bludgers(campo, &juego);
            mover_snitch(campo, &juego);
        }
        imprimir_juego(campo, juego);
    }
    mostrar_resultado(juego);
    return 0;
}