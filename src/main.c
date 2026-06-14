/*
    main.c - Punto de entrada de BitQuest
    Responsable: Leo
    -Hola soy leo :D
*/

#include <stdio.h>
#include <stdlib.h>
#include "juego.h"

/*
    AREA DE AIDA - colores y arte visual
    Si deseas cambiar colores, modificar las macros de abajo
*/

/* Codigos de color ANSI MOVIDOS AL .H PORQUE SE SUPONE QUE ASÍ LOS TENÍAN QUE PONER BASTARDITOS */

/* Rutas de mapas — Aida los puso en assets/maps/ */
static const char* rutas_mapas[] = {
    "assets/maps/nivel1.txt",
    "assets/maps/nivel2.txt",
    "assets/maps/nivel3.txt",
    "assets/maps/nivel4.txt"
};

#define TOTAL_NIVELES 4

/*
    AREA DE CARLOS - carga de mapas y pantalla de resumen
    main llama a:
        cargar_mapa_desde_archivo(ruta)
        desplegar_pantalla_resumen(nivel, monedas, total, pasos)
*/

/* ─────────────────────────────────────────────
 * PANTALLA DE INICIO
 * ───────────────────────────────────────────── */
void mostrar_menu_principal()
{
    printf("\033[H\033[J");

    /* Arte ASCII - BITQUEST */
    printf(COLOR_CYAN);
    printf("  ██████╗ ██╗████████╗ ██████╗ ██╗   ██╗███████╗███████╗████████╗\n");
    printf("  ██╔══██╗██║╚══██╔══╝██╔═══██╗██║   ██║██╔════╝██╔════╝╚══██╔══╝\n");
    printf("  ██████╔╝██║   ██║   ██║   ██║██║   ██║█████╗  ███████╗   ██║   \n");
    printf("  ██╔══██╗██║   ██║   ██║▄▄ ██║██║   ██║██╔══╝  ╚════██║   ██║   \n");
    printf("  ██████╔╝██║   ██║   ╚██████╔╝╚██████╔╝███████╗███████║   ██║   \n");
    printf("  ╚═════╝ ╚═╝   ╚═╝    ╚══▀▀═╝  ╚═════╝ ╚══════╝╚══════╝   ╚═╝   \n");
    printf(COLOR_RESET);

    printf("\n");
    printf(COLOR_YELLOW "       Explorador de Matrices con C + NASM x86-64\n" COLOR_RESET);
    printf(COLOR_YELLOW "       Materia: Lenguaje Ensamblador  -  Junio 2026\n" COLOR_RESET);
    printf("\n");
    printf(COLOR_WHITE  "  Equipo: Aida . Leo . Beto . Arthur . Carlos\n" COLOR_RESET);
    printf("\n");
    printf(COLOR_GRAY   "  ══════════════════════════════════════════════\n" COLOR_RESET);
    printf("\n");
    printf(COLOR_WHITE  "  Selecciona un nivel:\n\n" COLOR_RESET);
    printf(COLOR_CYAN   "    [ 1 ]" COLOR_WHITE " Nivel 1\n" COLOR_RESET);
    printf(COLOR_CYAN   "    [ 2 ]" COLOR_WHITE " Nivel 2\n" COLOR_RESET);
    printf(COLOR_CYAN   "    [ 3 ]" COLOR_WHITE " Nivel 3\n" COLOR_RESET);
    printf(COLOR_CYAN   "    [ 4 ]" COLOR_WHITE " Nivel 4\n" COLOR_RESET);
    printf("\n");
    printf(COLOR_GRAY   "    [ Q ] Salir\n" COLOR_RESET);
    printf("\n");
    printf(COLOR_GRAY   "  ══════════════════════════════════════════════\n" COLOR_RESET);
    printf(COLOR_WHITE  "  Opcion: " COLOR_RESET);
    reproducir_audio("menu");
}

/* ─────────────────────────────────────────────
 * PANTALLA FINAL 
 * Llama a calcular_puntaje() — NASM funcion 3
 * ───────────────────────────────────────────── */
void mostrar_pantalla_final(int monedas_totales, int pasos_totales, int niveles_completados)
{
    long long puntaje = calcular_puntaje(monedas_totales, pasos_totales, niveles_completados);

    printf("\033[H\033[J");
    printf(COLOR_YELLOW);
    printf("  ╔══════════════════════════════════════╗\n");
    printf("  ║         VICTORIA - JUEGO COMPLETO    ║\n");
    printf("  ╚══════════════════════════════════════╝\n");
    printf(COLOR_RESET);
    printf("\n");
    printf(COLOR_WHITE "  Niveles completados : " COLOR_CYAN "%d/%d\n"    COLOR_RESET, niveles_completados, TOTAL_NIVELES);
    printf(COLOR_WHITE "  Monedas totales     : " COLOR_CYAN "%d\n"       COLOR_RESET, monedas_totales);
    printf(COLOR_WHITE "  Pasos totales       : " COLOR_CYAN "%d\n"       COLOR_RESET, pasos_totales);
    printf(COLOR_WHITE "  Puntaje final       : " COLOR_YELLOW "%lld\n"   COLOR_RESET, puntaje);
    printf("\n");
    printf(COLOR_GRAY "  Presiona cualquier tecla para salir...\n" COLOR_RESET);
    getchar();
    reproducir_audio("victoria"); //Audio final
}

/* ─────────────────────────────────────────────
            MAIN
───────────────────────────────────────────── */
int main()
{
    char opcion;
    int nivel_inicio        = 1;
    int monedas_acumuladas  = 0;
    int pasos_acumulados    = 0;
    int niveles_completados = 0;

    mostrar_menu_principal();
    opcion = getchar();

    if (opcion == 'q' || opcion == 'Q') return 0;

    if (opcion >= '1' && opcion <= '4')
        nivel_inicio = opcion - '0';
    else
        nivel_inicio = 1;

    /* Flujo de niveles */
    for (int nivel = nivel_inicio; nivel <= TOTAL_NIVELES; nivel++)
    {
        /* AREA DE CARLOS: cargar mapa desde archivo */
        cargar_mapa_desde_archivo(rutas_mapas[nivel - 1]);

        inicializar_estado(nivel);
        ejecutar_juego();

        monedas_acumuladas  += estado.monedas_recogidas;
        pasos_acumulados    += estado.pasos;
        niveles_completados++;

        /* AREA DE CARLOS: resumen entre niveles */
        if (nivel < TOTAL_NIVELES)
            desplegar_pantalla_resumen(nivel, estado.monedas_recogidas, estado.total_monedas, estado.pasos);
    }

    mostrar_pantalla_final(monedas_acumuladas, pasos_acumulados, niveles_completados);

    return 0;
}