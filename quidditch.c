#include <stdio.h>
#include <stdlib.h>
#include "quidditch.h"
#include "sombrero.h"

void rellenar_campo(char campo[FILAS_CAMPO][COLS_CAMPO], juego_t juego) {
    for(int i = 0; i < FILAS_CAMPO; i++) {
        for(int j = 0; j < COLS_CAMPO; j++) {
            campo[i][j] = CELDA_VACIA;
        }
    }

    for(int i = 0; i < juego.bludgers_en_juego; i++) {
        campo[juego.posicion_bludgers[i].fila][juego.posicion_bludgers[i].columna] = BLUDGER;
    }

    for(int i = 0; i < juego.dementores_en_juego; i++) {
        campo[juego.posicion_dementores[i].fila][juego.posicion_dementores[i].columna] = DEMENTOR;
    }

    campo[juego.posicion_snitch.fila][juego.posicion_snitch.columna] = SNITCH;
    campo[juego.posicion_jugador.fila][juego.posicion_jugador.columna] = JUGADOR;
}

void inicializar_juego(char campo[FILAS_CAMPO][COLS_CAMPO], char casa, juego_t *juego) {
    coordenada_t snitch = posicion_inicial_snitch();
    (*juego).posicion_snitch.fila = snitch.fila;
    (*juego).posicion_snitch.columna = snitch.columna;

    (*juego).resistencia = RESISTENCIA_INICIAL;

    coordenada_t posicion_jugador = POSICION_JUGADOR_INICIAL;
    (*juego).posicion_jugador = posicion_jugador;

    (*juego).casa = casa;

    (*juego).estado = EN_EJECUCION;

    (*juego).bludgers_en_juego = CANT_BLUDGERS_INICIAL;
    (*juego).direccion = DIRECCION_DERECHA;

    coordenada_t b1 = BLUDGER_1;
    coordenada_t b2 = BLUDGER_2;
    coordenada_t b3 = BLUDGER_3;
    coordenada_t b4 = BLUDGER_4;
    coordenada_t b5 = BLUDGER_5;

    (*juego).posicion_bludgers[0] = b1;
    (*juego).posicion_bludgers[1] = b2;
    (*juego).posicion_bludgers[2] = b3;
    (*juego).posicion_bludgers[3] = b4;
    (*juego).posicion_bludgers[4] = b5;

    coordenada_t d1 = DEMENTOR_1;
    coordenada_t d2 = DEMENTOR_2;
    coordenada_t d3 = DEMENTOR_3;
    coordenada_t d4 = DEMENTOR_4;


    (*juego).direccion = DIRECCION_DERECHA;
    (*juego).dementores_en_juego = DEMENTORES_INICIAL;
    (*juego).posicion_dementores[0] = d1;
    (*juego).posicion_dementores[1] = d2;
    (*juego).posicion_dementores[2] = d3;
    (*juego).posicion_dementores[3] = d4;

    imprimir_juego(campo, *juego);
}

bool es_coordenada_valida(coordenada_t coordenada) {
    return (coordenada.fila >= 0  && coordenada.columna >= 0) && (coordenada.fila < FILAS_CAMPO && coordenada.columna < COLS_CAMPO);
}

coordenada_t obtener_coordenada(coordenada_t posicion_jugador, char tecla) {
    coordenada_t nueva_coord;
    if(tecla == ARRIBA) {
        nueva_coord.fila = posicion_jugador.fila - 1;
        nueva_coord.columna = posicion_jugador.columna;
    } else if(tecla == ABAJO) {
        nueva_coord.fila = posicion_jugador.fila + 1;
        nueva_coord.columna = posicion_jugador.columna;
    } else if(tecla == DERECHA) {
        nueva_coord.fila = posicion_jugador.fila;
        nueva_coord.columna = posicion_jugador.columna + 1;
    } else if(tecla == IZQUIERDA) {
        nueva_coord.fila = posicion_jugador.fila;
        nueva_coord.columna = posicion_jugador.columna - 1;
    }
    return nueva_coord;
}

bool validar_movimiento(coordenada_t posicion_jugador, char tecla) {
    coordenada_t nueva_coord;
    nueva_coord = obtener_coordenada(posicion_jugador, tecla);
    return es_coordenada_valida(nueva_coord);
}

char pedir_movimiento(coordenada_t posicion_jugador) {
    char movimiento;
    printf("Ingrese un movimiento: \n");
    scanf(" %c", &movimiento);
    if(!validar_movimiento(posicion_jugador, movimiento)) {
        printf("Por favor ingrese un movimiento valido \n");
        return pedir_movimiento(posicion_jugador);
    }
    return movimiento;
}

bool esta_snitch_cerca(juego_t juego) {
    int fila_snitch = juego.posicion_snitch.fila;
    int columna_snitch = juego.posicion_snitch.columna;
    int fila_jugador = juego.posicion_jugador.fila;
    int columna_jugador = juego.posicion_jugador.columna;
    int delta_fila = abs(fila_jugador - fila_snitch);
    int delta_columna = abs(columna_jugador - columna_snitch);
    return (delta_fila <= 1) && (delta_columna <= 1);
}

bool atrapo_snitch(juego_t *juego) {
    if((*juego).casa == RAVENCLAW && esta_snitch_cerca(*juego)) {
        return true;
    }
    return ((*juego).posicion_jugador.fila == (*juego).posicion_snitch.fila && (*juego).posicion_jugador.columna == (*juego).posicion_snitch.columna);
}

void actualizar_estado(juego_t *juego) {
    if(atrapo_snitch(juego)) {
        (*juego).estado = JUGADOR_GANO;
    } else if((*juego).resistencia <= 0) {
        (*juego).estado = JUGADOR_PERDIO;
    }
}

void eliminar_dementor(juego_t *juego, coordenada_t coordenada) {
    bool encontrado = false;
    int i = 0;
    int pos = 0;
    while(i < (*juego).dementores_en_juego && !encontrado) {
        if((*juego).posicion_dementores[i].fila == coordenada.fila && (*juego).posicion_dementores[i].columna == coordenada.columna) {
            encontrado = true;
            pos = i;
        }
        i++;
    }
    if(encontrado) {
        for (int i = pos; i < (*juego).dementores_en_juego - 1; i++) {
            (*juego).posicion_dementores[i] = (*juego).posicion_dementores[i + 1];
        }
        (*juego).dementores_en_juego--;
    }
}

void eliminar_bludger(juego_t *juego, coordenada_t coordenada) {
    bool encontrado = false;
    int i = 0, pos = 0;
    while(i < (*juego).bludgers_en_juego && !encontrado) {
        if((*juego).posicion_bludgers[i].fila == coordenada.fila && (*juego).posicion_bludgers[i].columna == coordenada.columna) {
            encontrado = true;
            pos = i;
        }
        i++;
    }
    if(encontrado) {
        for (int j = pos; j < (*juego).bludgers_en_juego - 1; j++) {
            (*juego).posicion_bludgers[j] = (*juego).posicion_bludgers[j + 1];
        }
        (*juego).bludgers_en_juego -= 1;
        if((*juego).casa != SLYTHERIN) {
            (*juego).resistencia -= BLUDGER_GOLPE_RESISTENCIA;
        }
        actualizar_estado(juego);
    }
}

int distancia_coord_a_jugador(coordenada_t coord, juego_t juego) {
    return abs(coord.fila - juego.posicion_jugador.fila) + abs(coord.columna - juego.posicion_jugador.columna);
}

void obtener_posibles_posiciones_snitch(coordenada_t posicion_actual_snitch, coordenada_t posibles_posiciones[4]) {
    coordenada_t pos1 = {posicion_actual_snitch.fila - 1, posicion_actual_snitch.columna - 1};
    coordenada_t pos2 = {posicion_actual_snitch.fila - 1, posicion_actual_snitch.columna + 1};
    coordenada_t pos3 = {posicion_actual_snitch.fila + 1, posicion_actual_snitch.columna - 1};
    coordenada_t pos4 = {posicion_actual_snitch.fila + 1, posicion_actual_snitch.columna + 1};
    coordenada_t pos5 = {posicion_actual_snitch.fila, posicion_actual_snitch.columna};
    posibles_posiciones[0] = pos1;
    posibles_posiciones[1] = pos2;
    posibles_posiciones[2] = pos3;
    posibles_posiciones[3] = pos4;
    posibles_posiciones[4] = pos5;
}

bool existe_elemento_en_coordenada(char campo[FILAS_CAMPO][COLS_CAMPO], coordenada_t coord) {
    if(campo[coord.fila][coord.columna] != CELDA_VACIA) {
        return true;
    }
    return false;
}

coordenada_t obtener_nueva_coord_snitch(juego_t juego, char campo[FILAS_CAMPO][COLS_CAMPO]) {
    int distancia_mayor = 0;
    int distancia_a_coord;
    bool es_coord_valida;
    bool existe_elemento;

    coordenada_t posicion_actual_snitch;
    coordenada_t nueva_posicion;
    posicion_actual_snitch = juego.posicion_snitch;

    coordenada_t posibles_posiciones[MAX_POSICIONES_SNITCH];

    obtener_posibles_posiciones_snitch(posicion_actual_snitch, posibles_posiciones);
    nueva_posicion.fila = posicion_actual_snitch.fila;
    nueva_posicion.columna = posicion_actual_snitch.columna;

    for(int i = 0; i < POSIBLES_POSICIONES_SNITCH; i++) {
        es_coord_valida = es_coordenada_valida(posibles_posiciones[i]);

        if(es_coord_valida) {
            distancia_a_coord = distancia_coord_a_jugador(posibles_posiciones[i], juego);
            existe_elemento = existe_elemento_en_coordenada(campo, posibles_posiciones[i]);

            if(distancia_a_coord > distancia_mayor && !existe_elemento) {
                distancia_mayor = distancia_a_coord;
                nueva_posicion.fila = posibles_posiciones[i].fila;
                nueva_posicion.columna = posibles_posiciones[i].columna;
            }
        }
    }
    return nueva_posicion;
}

void mover_snitch(char campo[FILAS_CAMPO][COLS_CAMPO], juego_t *juego) {
    coordenada_t pos_snitch;
    pos_snitch.fila = (*juego).posicion_snitch.fila;
    pos_snitch.columna = (*juego).posicion_snitch.columna;
    int distancia = distancia_coord_a_jugador(pos_snitch, *juego);
    if(distancia <= DISTANCIA_MINIMA_SNITCH) {
        coordenada_t nueva_coord = obtener_nueva_coord_snitch(*juego, campo);
        (*juego).posicion_snitch.fila = nueva_coord.fila;
        (*juego).posicion_snitch.columna = nueva_coord.columna;
        rellenar_campo(campo, *juego);
    }
    atrapo_snitch(juego);
}

bool bludger_choca(coordenada_t bludger, coordenada_t jugador, char casa) {
    return bludger.fila == jugador.fila && bludger.columna == jugador.columna;
}

void mover_bludgers(char campo[FILAS_CAMPO][COLS_CAMPO], juego_t *juego) {
    for(int i = 0; i < (*juego).bludgers_en_juego; i++) {
        if ((*juego).direccion == DIRECCION_DERECHA && (*juego).posicion_bludgers[i].columna < COLS_CAMPO - 1) {
            (*juego).posicion_bludgers[i].columna++;
        } else if((*juego).posicion_bludgers[i].columna > 0) {
            (*juego).posicion_bludgers[i].columna--;
        }

        if(bludger_choca((*juego).posicion_bludgers[i], (*juego).posicion_jugador, (*juego).casa)) {
            eliminar_bludger(juego, (*juego).posicion_bludgers[i]);
        }
    }

    if((*juego).resistencia > 0) {
        if((*juego).posicion_bludgers[0].columna  == COLS_CAMPO - 1) {
            (*juego).direccion = DIRECCION_IZQUIERDA;
        } else if((*juego).direccion == DIRECCION_IZQUIERDA && (*juego).posicion_bludgers[0].columna == 0) {
            (*juego).direccion = DIRECCION_DERECHA;
        }
        rellenar_campo(campo, *juego);
    }
}

void mover_jugador(char campo[FILAS_CAMPO][COLS_CAMPO], char direccion, juego_t *juego) {
    coordenada_t nueva_coordenada = obtener_coordenada((*juego).posicion_jugador, direccion);
    (*juego).posicion_jugador.fila = nueva_coordenada.fila;
    (*juego).posicion_jugador.columna = nueva_coordenada.columna;
    (*juego).resistencia--;

    if(atrapo_snitch(juego)) {
        (*juego).estado = JUGADOR_GANO;
    } else if(campo[nueva_coordenada.fila][nueva_coordenada.columna] == BLUDGER) {
        eliminar_bludger(juego, nueva_coordenada);
    } else if(campo[nueva_coordenada.fila][nueva_coordenada.columna] == DEMENTOR && (*juego).casa != GRYFFINDOR) {
        (*juego).resistencia = 0;
        (*juego).estado = JUGADOR_PERDIO;
    } else if(campo[nueva_coordenada.fila][nueva_coordenada.columna] == DEMENTOR && (*juego).casa == GRYFFINDOR) {
        eliminar_dementor(juego, nueva_coordenada);
    } else if(atrapo_snitch(juego)){
        (*juego).estado = JUGADOR_GANO;
    }

    if((*juego).resistencia <= 0) {
        (*juego).estado = JUGADOR_PERDIO;
    }

    rellenar_campo(campo, *juego);
}

void imprimir_campo(char campo[FILAS_CAMPO][COLS_CAMPO]) {
    printf("\033c");
    for(int i = 0; i < FILAS_CAMPO; i++) {
        for(int j = 0; j < COLS_CAMPO; j++) {
            printf("%c", campo[i][j]);
        }
        printf("\n");
    }
}

void imprimir_juego(char campo[FILAS_CAMPO][COLS_CAMPO], juego_t juego) {
    rellenar_campo(campo, juego);
    imprimir_campo(campo);
}

coordenada_t posicion_inicial_snitch() {
    juego_t juego;
    coordenada_t posicion_inicial;
    coordenada_t posicion_inicial_jugador = POSICION_JUGADOR_INICIAL;
    juego.posicion_jugador = posicion_inicial_jugador;
    posicion_inicial.fila = rand() % FILAS_CAMPO;
    posicion_inicial.columna = rand() % COLS_CAMPO;
    if(distancia_coord_a_jugador(posicion_inicial, juego) < 5) { // Si la snitch cayo a esta distancia volvemos a generarlo.
        return posicion_inicial_snitch(juego);
    }
    return posicion_inicial;
}

bool finalizo_juego(juego_t *juego) {
    return (*juego).estado == JUGADOR_GANO || (*juego).estado == JUGADOR_PERDIO;
}

void mostrar_resultado(juego_t juego) {
    if(juego.estado == JUGADOR_GANO) {
        printf("Jugador gano \n");
    } else if(juego.estado == JUGADOR_PERDIO) {
        printf("Jugador perdio \n");
    }
    printf("Resistencia Final: %i \n", juego.resistencia);
}
