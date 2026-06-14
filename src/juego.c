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
        case '.': return COLOR_FONDO_CAFE COLOR_CAMINO  "░" COLOR_RESET;
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

    printf(COLOR_GRAY" ╔═════════════════════╗\n");

    for (int f = 0; f < VISTA_FILAS; f++)
    {
        printf(COLOR_GRAY" ║");
        for (int c = 0; c < VISTA_COLS; c++)
        {
            int fila_real = origen_fila + f;
            int col_real = origen_col + c;

            char celda = (fila_real == jugador_fila && col_real == jugador_col)
            ? 'P' //Jugador
            : estado.mapa[fila_real][col_real]; //Nuesto bello mapa
            printf("%s", traducir_simbolo(celda));
        }
        printf(COLOR_GRAY" ║\n");
    }
    printf(COLOR_GRAY" ╚═════════════════════╝\n");
    printf("[W/A/S/D] Mover | [P] Pausa\n");
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

    if(!validar_movimiento((char*)estado.mapa, COLS, nueva_fila, nueva_col)) return;

        /* Revisar puerta ANTES de mover */
        char celda = estado.mapa[nueva_fila][nueva_col];
        if (celda == 'D' && !estado.tiene_llave) return;

        /* Ahora sí actualizar posición */
        estado.jugador_fila = nueva_fila;
        estado.jugador_col = nueva_col;
        estado.pasos++;

        if(celda == 'M')
        {
            estado.monedas_recogidas++;
            estado.mapa[nueva_fila][nueva_col] = '.';
        }
        if(celda == 'K')
        {
            estado.tiene_llave = 1;
            estado.mapa[nueva_fila][nueva_col] = '.';
        }
        if(celda == 'D' && estado.tiene_llave)
        {
            estado.puerta_abierta = 1;
            estado.mapa[nueva_fila][nueva_col] = '.';
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
extern int salir_al_menu;

int ejecutar_juego() {

    #ifndef _WIN32
        activar_modo_raw();
    #endif

        //Cambia la musica del juego
        reproducir_audio("detener");
        reproducir_audio("juego");

        int corriendo = 1;
        char tecla;

        while (corriendo) {
            renderizar_ventana_visible(estado.jugador_fila, estado.jugador_col);//Dibuja la ventana cada vez que se mueve el jugador

            tecla = leer_tecla(); //Lee la tecla duh


            if (tecla == 'P' || tecla == 'p')
            {
                reproducir_audio("detener");
                reproducir_audio("pausa");
                mostrar_menu_pausa();

                if(salir_al_menu)
                {
                    salir_al_menu = 0; //Resetea la bandera para no afectar el siguiente juego
                    return 0; //Regresa al menu principal
                }

                
            }
            
            if (tecla == 'Q' || tecla == 'q')
            {
                reproducir_audio("detener");
                reproducir_audio("menu");
                return 0; //Regresa al menu principal salio con Q
            }

            mover_jugador(tecla); //Intenta mover al jugador según la tecla precionada

            if (estado.mapa[estado.jugador_fila][estado.jugador_col] == 'E' && estado.puerta_abierta) //Si el jugador llega a la salida y la puerta está abierta
            {
                corriendo = 0; //Termina el juego
                desplegar_pantalla_resumen(estado.nivel_actual, estado.monedas_recogidas, estado.total_monedas, estado.pasos); /* AREA DE CARLOS */
                reproducir_audio("detener");
                return 1; //Retorna 1 si se completo el nivel
            }
        }



    #ifndef _WIN32
        restaurar_terminal();
    #endif


    reproducir_audio("detener");
}


/*
    AREA DE CARLOS - Persistencia
    cargar_mapa_desde_archivo()
    Lee el archivo .txt del nivel y llena estado.mapa
    También busca la posición inicial del jugador (P)
*/
void cargar_mapa_desde_archivo(const char* ruta)
{
    FILE* archivo = fopen(ruta, "r");

    if (archivo == NULL)
    {
        printf("Error: no se pudo abrir el mapa: %s\n", ruta);
        exit(1);
    }

    char linea[128];
    int fila = 0;

    while (fila < FILAS && fgets(linea, sizeof(linea), archivo))
    {
        int len = (int)strlen(linea);

        /* Quitar salto de linea */
        while (len > 0 && (linea[len-1] == '\n' || linea[len-1] == '\r'))
            linea[--len] = '\0';

        for (int col = 0; col < COLS; col++)
            estado.mapa[fila][col] = (col < len) ? linea[col] : '.';

        fila++;
    }

    /* Rellenar filas faltantes con paredes por si el archivo es corto */
    for (; fila < FILAS; fila++)
        for (int col = 0; col < COLS; col++)
            estado.mapa[fila][col] = '#';

    fclose(archivo);

    /* Buscar posicion inicial del jugador (P) y reemplazarla por camino */
    estado.jugador_fila = 1;
    estado.jugador_col  = 1;

    for (int f = 0; f < FILAS; f++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (estado.mapa[f][c] == 'P')
            {
                estado.jugador_fila = f;
                estado.jugador_col  = c;
                estado.mapa[f][c]   = '.'; /* Se dibuja aparte en renderizar */
                goto jugador_encontrado;
            }
        }
    }
jugador_encontrado:;
}


/*
    AREA DE CARLOS - Persistencia
    desplegar_pantalla_resumen()
    Muestra el resumen entre niveles antes de continuar
*/
void desplegar_pantalla_resumen(int nivel, int monedas, int total_monedas, int pasos)
{
    printf("\033[H\033[J");
    printf(COLOR_FONDO_CAFE);
    printf("  ╔════════════════════════════════════════════╗\n");
    printf("  ║              NIVEL %d COMPLETADO            ║\n", nivel);
    printf("  ╚════════════════════════════════════════════╝\n");
    printf(COLOR_RESET);
    printf("\n");
    printf(COLOR_WHITE "  Monedas recogidas : " COLOR_CYAN "%d/%d\n" COLOR_RESET, monedas, total_monedas);
    printf(COLOR_WHITE "  Pasos dados       : " COLOR_CYAN "%d\n"    COLOR_RESET, pasos);
    printf("\n");
    printf(COLOR_GRAY  "  Presiona cualquier tecla para continuar...\n" COLOR_RESET);

    #ifdef _WIN32
        _getch();
    #else
        getchar();
    #endif
}