#ifndef QUIDDITCH_H
#define QUIDDITCH_H
#include <stdbool.h>

#define RESISTENCIA_INICIAL 50
#define EN_EJECUCION 0
#define JUGADOR_GANO 1
#define JUGADOR_PERDIO 2
#define MAX_BLUDGERS  6
#define CANT_BLUDGERS_INICIAL  5
#define DISTANCIA_MINIMA_SNITCH 10
#define MAX_DEMENTORES 5
#define DEMENTORES_INICIAL 4
#define FILAS_CAMPO 25
#define COLS_CAMPO 15
#define ARRIBA 'w'
#define ABAJO 's'
#define DERECHA 'd'
#define IZQUIERDA 'a'
#define CELDA_VACIA ' '
#define BLUDGER 'B'
#define JUGADOR 'J'
#define DEMENTOR 'D'
#define SNITCH 'S'
#define MAX_POSICIONES_SNITCH 5
#define POSIBLES_POSICIONES_SNITCH 5
#define DIRECCION_DERECHA 'D'
#define DIRECCION_IZQUIERDA 'I'
#define CENTRO_FILA 12
#define CENTRO_COLUMNA 7
#define POSICION_JUGADOR_INICIAL {CENTRO_FILA, CENTRO_COLUMNA}
#define BLUDGER_1 {2,0}
#define BLUDGER_2 {7,0}
#define BLUDGER_3 {12,0}
#define BLUDGER_4 {17,0}
#define BLUDGER_5 {22,0}
#define DEMENTOR_1 {5, 3}
#define DEMENTOR_2 {5, 11}
#define DEMENTOR_3 {19, 3}
#define DEMENTOR_4 {19, 11}
#define BLUDGER_GOLPE_RESISTENCIA 10

typedef struct coordenada {
	int fila;
	int columna;
} coordenada_t;


typedef struct juego {
	coordenada_t posicion_jugador;
	char casa;
	int resistencia;
	coordenada_t posicion_snitch;

	int bludgers_en_juego; // tope del vector posicion_bludgers
	coordenada_t posicion_bludgers[MAX_BLUDGERS];
	char direccion; // 'D': derecha – 'I': izquierda

	int dementores_en_juego; // tope del vector posicion_dementores
	coordenada_t posicion_dementores[MAX_DEMENTORES];
	
	int estado; // 0: en ejecucion – 1: jugador gano – 2: jugador perdio
} juego_t;

/*
 * pre: Recibe la matriz campo y el puntero a la informacion del juego
 * post: inicializa el jugador, bludger, dementores, snitch y el estado del juego
 */
void inicializar_juego(char campo[FILAS_CAMPO][COLS_CAMPO], char casa, juego_t *juego);

/*
 * pre: Recibe la posicion actual del jugador
 * post: Solicita al usuario un nuevo movimiento
 */
char pedir_movimiento(coordenada_t posicion_jugador);

/*
 * pre: Recibe la matriz campo con la data inicializada, la tecla de movimiento y el struct de juego
 * post: actualiza el campo con la nueva posicion del jugador y los demás elementos
 */
void mover_jugador(char campo[FILAS_CAMPO][COLS_CAMPO], char direccion, juego_t *juego);

/*
 * pre: Recibe el campo y el struct de juego
 * post: Posiciona el snitch en su nueva ubicacion en la matriz de campo
 */
void mover_snitch(char campo[FILAS_CAMPO][COLS_CAMPO], juego_t *juego);

/*
 * pre: Recibe el campo y el struct de juego
 * post: Posiciona todas las bludgers en su nuevo lugar en la matriz campo
 */
void mover_bludgers(char campo[FILAS_CAMPO][COLS_CAMPO], juego_t *juego);

/*
 * pre: Posicion de jugador inicializada y la semilla del random seteada
 * post: Posicion aleatoria del snitch con distancia mayor a 5 del jugador
 */
coordenada_t posicion_inicial_snitch();

/*
 * pre: Recibe el struct del juego con el estado seteado
 * post: Verifica si el jugador gano/perdio
 */
bool finalizo_juego(juego_t *juego);

/*
 * pre: Recibe el struct del juego con el estado seteado
 * post: Imprime resultado. Jugador gano/perdio
 */
void mostrar_resultado(juego_t juego);

/*
 * pre: Matriz campo con la data inicializada
 * post: Imprime la matriz de forma grafica
 */
void imprimir_juego(char campo[FILAS_CAMPO][COLS_CAMPO], juego_t juego);


#endif /* QUIDDITCH_H */