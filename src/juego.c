/*
    juego.c - El motor del juego BitQuest
    Responsable de esto: Leo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif


#include "juego.h"


/*Estado global*/

EstadoJuego estado;

/*Modo Raw unicamente para Linux*/

#ifndef _WIN32
static struct termios config_original;

void activar_modo_raw() 
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &config_original);
    raw = config_original;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void restaurar_terminal() 
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &config_original);
}
#endif


char leer_tecla()
{
#ifdef _WIN32
    return (char)_getch();
#else
    return (char)getchar();
#endif
}


/*
    Viewport (mi parte -leo)
    Esto es para centrar la ventana 20*20 en el jugador 'P'
    restringir para no salirse del mapa 60*60
*/

void calcular_origen_viewport(int jugador_fila, int jugador_col, int *origen_fila, int *origen_col)
{
    *origen_fila = jugador_fila - (VISTA_FILAS / 2);
    *origen_col = jugador_col - (VISTA_COLS / 2);
    
    if (*origen_fila < 0) { *origen_fila = 0;}
    if (*origen_col < 0) { *origen_col = 0;}
    if(*origen_fila > FILAS - VISTA_FILAS) { *origen_fila = FILAS - VISTA_FILAS;}
    if(*origen_col > COLS - VISTA_COLS) { *origen_col = COLS - VISTA_COLS;}
}

//FUNCIÓN DE TRADUCCIÓN DE SÍMBOLOS PARA LA IMPRESIÓN DEL MAPA -AÍDA
const char* traducir_simbolo(char c) {
    switch (c){
        case '#': return COLOR_PARED   "█" COLOR_RESET;   
        case '.': return COLOR_CAMINO  "░" COLOR_RESET;
        case 'P': return COLOR_JUGADOR "X" COLOR_RESET;    
        case 'M': return COLOR_MONEDA  "©" COLOR_RESET;    
        case 'K': return COLOR_LLAVE   "¶" COLOR_RESET;      
        case 'D': return COLOR_PUERTA  "│" COLOR_RESET;  //se cambió pq la regué juasjuas   
        case 'E': return COLOR_SALIDA  "█" COLOR_RESET;     
        default:  return COLOR_CAMINO  "?" COLOR_RESET;     
    }
}



void renderizar_ventana_visible(int jugador_fila, int jugador_col)
{
    int origen_fila, origen_col;
    calcular_origen_viewport(jugador_fila, jugador_col, &origen_fila, &origen_col);

    printf("\033[H\033[J"); //Este print limpia la pantalla
    printf(" BitQuest | Nivel: %d | Monedas: %d/%d | Pasos: %d\n", 
        estado.nivel_actual,
        estado.monedas_recogidas,
        estado.total_monedas,
        estado.pasos);

    printf(" +--------------------+\n");

    for (int f = 0; f < VISTA_FILAS; f++)
    {
        printf(" |");
        for (int c = 0; c < VISTA_COLS; c++)
        {
            int fila_real = origen_fila + f;
            int col_real = origen_col + c;

            char celda = (fila_real == jugador_fila && col_real == jugador_col)
            ? 'P' //Jugador
            : estado.mapa[fila_real][col_real]; //Nuesto bello mapa
            printf("%s", traducir_simbolo(celda));
        }
        printf(" |\n");
    }
    printf(" +--------------------+\n");
    printf(" [W/A/S/D] Mover | [Q] Salir\n");
}


/*
    Esta es la parte del MOVIMIENTO del jugador
    LLamar a 'validar_movimiento()' de Beto
    antes de que se actualice la posicion
*/

void mover_jugador(char tecla){
    int nueva_fila = estado.jugador_fila;
    int nueva_col = estado.jugador_col;

    switch (tecla) //Valida la tecla precionada para moverse
    {
        case 'W': case 'w': nueva_fila--; break;
        case 'S': case 's': nueva_fila++; break;
        case 'A': case 'a': nueva_col--; break;
        case 'D': case 'd': nueva_col++; break;
        default: return; //Si no es una tecla de movimiento, no hace nada (Oviamente)
    }

    if (nueva_fila < 0 || nueva_fila >= FILAS)
        return; //Movimiento fuera de los límites del mapa en las filas
    if (nueva_col < 0 || nueva_col >= COLS)
        return; //Movimiento fuera de los límites del mapa en las columnas



    /*NASM funcion 2 de beto*/

    if(!validar_movimiento((char*)estado.mapa, COLS, nueva_fila, nueva_col)) return; //Movimiento no válido según las reglas del juego

    estado.jugador_fila = nueva_fila;
    estado.jugador_col = nueva_col;
    estado.pasos++;

    char celda = estado.mapa[nueva_fila][nueva_col];

    /*Esta parte que sigue son las "Casillas Especiales" -leo*/

    if(celda == 'M') //Si el jugador se mueve a una celda con moneda
    {
        estado.monedas_recogidas++;//esto aumenta tus monedas
        estado.mapa[nueva_fila][nueva_col] = ' '; //Remueve la moneda del mapa
    }

    if(celda == 'K') //Si el jugador se mueve a una celda con llave
    {
        estado.tiene_llave = 1; //El jugador ahora tiene la llave
        estado.mapa[nueva_fila][nueva_col] = ' '; //Remueve la llave del mapa
    }

    if(celda == 'D' && estado.tiene_llave)//Si el jugador se mueve a una celda con puerta y tiene la llave
    {
        estado.puerta_abierta = 1; //El jugador ha abierto la puerta
        estado.mapa[nueva_fila][nueva_col] = ' '; //Remueve la puerta 
    }

}

/*
    INICIALIZAR ESTADO
    Esta area le toca a carlos: cargar_mapa_desde_archivo()
    tiene que llenar estado.mapa, estado.jugador_fila
    y estado.jugador_col antes de llamar esto

*/

void inicializar_estado(int nivel) {

    estado.nivel_actual         = nivel;
    estado.monedas_recogidas    = 0;
    estado.pasos                = 0;
    estado.tiene_llave          = 0;
    estado.puerta_abierta       = 0;

    /*NASM funcion 1 de beto*/

    estado.total_monedas = (int)contar_caracteres((char*)estado.mapa, FILAS * COLS, 'M'); //Cuenta el total de monedas en el mapa para el nivel actual

}


/*  LOOP PRINCIPAL
    Esto le vuelve a tocar a Carlos
    Al terminar el nivel llamar
    'desplegar_pantalla_resumen() desde aqui
*/

void ejecutar_juego() {
    #ifndef _WIN32
        activar_modo_raw();
    #endif
        int corriendo = 1;
        char tecla;

        while (corriendo) {
            renderizar_ventana_visible(estado.jugador_fila, estado.jugador_col);//Dibuja la ventana cada vez que se mueve el jugador

            tecla = leer_tecla(); //Lee la tecla duh

            if (tecla == 'Q' || tecla == 'q')
            {
                corriendo = 0; //Salir del juego al precionar Q/q
                break;
            }

            mover_jugador(tecla); //Intenta mover al jugador según la tecla precionada

            if (estado.mapa[estado.jugador_fila][estado.jugador_col] == 'E' && estado.puerta_abierta) //Si el jugador llega a la salida y la puerta está abierta
            {
                corriendo = 0; //Termina el juego

                /*  aqui va lo de carlos
                'desplegar_pantalla_resumen(...)' */
            }
        }



    #ifndef _WIN32
        restaurar_terminal();
    #endif
}
