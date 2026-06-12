#ifndef JUEGO_H
#define JUEGO_H

/* Dimensiones del mapa */

#define FILAS 60
#define COLS 60
#define VISTA_FILAS 20
#define VISTA_COLS 20

/* Estado global -leo*/

typedef struct {
    char mapa[FILAS][COLS];
    int jugador_fila;
    int jugador_col;
    int nivel_actual;
    int monedas_recogidas;
    int total_monedas;
    int pasos;
    int tiene_llave;
    int puerta_abierta;
} EstadoJuego;

extern EstadoJuego estado;


/*NASM MODULO A -Beto*/
extern long long contar_caracteres(char* mapa, int total_celdas, char caracter);

extern int validar_movimiento(char* mapa, int columnas, int nueva_fila,int nueva_col);


/* AREA DE AIDA - Traduccion visual*/



/*AREA DE CARLOS - persistencia*/


/*Funciones -Leo -juego.c */
void ejecutar_juego();
void inicializar_estado(int nivel);
void renderizar_ventana_visible(int jugador_fila, int jugador_col);
void mover_jugador(char tecla);

#endif