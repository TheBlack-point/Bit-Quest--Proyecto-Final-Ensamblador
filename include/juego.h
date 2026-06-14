#ifndef JUEGO_H
#define JUEGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* CAMBIO DE LUGAR PARA DEFINIR LOS COLORES DE MANERA GLOBAL */
/* Codigos de color ANSI DE LOS MENÚ */
#define COLOR_RESET   "\033[0m"
#define COLOR_CYAN    "\033[96m"
#define COLOR_YELLOW  "\033[93m"
#define COLOR_WHITE   "\033[97m"
#define COLOR_GRAY    "\033[90m"

/* COLORES PARA EL MAPA (AÍDA)*/
#define COLOR_PARED   "\033[90m"   /* gris oscuro  */
#define COLOR_CAMINO  "\033[37m"   /* blanco suave */
#define COLOR_JUGADOR "\033[96m"   /* cian brillante */
#define COLOR_MONEDA  "\033[93m"   /* amarillo     */
#define COLOR_LLAVE   "\033[95m"   /* magenta      */
#define COLOR_PUERTA  "\033[91m"   /* rojo         */
#define COLOR_SALIDA  "\033[92m"   /* verde        */


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


/*NASM MODULO B -ARTUR*/

extern int       detectar_objeto(char* mapa, int columnas, int fila, int col, char objeto);
extern long long contar_celdas_libres(char* mapa, int total_celdas);
extern long long calcular_puntaje(int monedas, int pasos, int niveles);


/*AREA DE CARLOS - Persistencia*/
void cargar_mapa_desde_archivo(const char* ruta);
void desplegar_pantalla_resumen(int nivel, int monedas, int total_monedas, int pasos);



/*Funciones -Leo -juego.c */
void ejecutar_juego();
void inicializar_estado(int nivel);
void renderizar_ventana_visible(int jugador_fila, int jugador_col);
void mover_jugador(char tecla);

/*Funciones de audio AÍDA*/
void reproducir_audio(const char* evento);

#endif