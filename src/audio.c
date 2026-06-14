/*
    audio.c - Manejo de audio de BitQuest
    Sonidos:
        menu.wav     - Menu principal y pausa
        juego.wav    - Durante el juego (loop)
        victoria.wav - Victoria final
*/

#include "juego.h"

#ifdef _WIN32
    #include <windows.h>
    #include <mmsystem.h>
#endif

/*
    reproducir_audio()
    Recibe el nombre del evento y reproduce el .wav correspondiente.
    En Windows usa PlaySound, en Linux usa aplay por consola.
*/
void reproducir_audio(const char* evento)
{
    #ifdef _WIN32

        if (strcmp(evento, "menu") == 0)
            PlaySound("assets/audio/menu.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

        else if (strcmp(evento, "juego") == 0)
            PlaySound("assets/audio/juego.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

        else if (strcmp(evento, "victoria") == 0)
            PlaySound("assets/audio/victoria.wav", NULL, SND_FILENAME | SND_ASYNC);

        else if (strcmp(evento, "detener") == 0)
            PlaySound(NULL, NULL, 0); /* Detiene cualquier sonido activo */

    #else

        if (strcmp(evento, "menu") == 0)
            system("aplay -q assets/audio/menu.wav &");

        else if (strcmp(evento, "juego") == 0)
            system("aplay -q assets/audio/juego.wav &");

        else if (strcmp(evento, "victoria") == 0)
            system("aplay -q assets/audio/victoria.wav");

        else if (strcmp(evento, "detener") == 0)
            system("pkill aplay 2>/dev/null");

    #endif
}

/*FUNCIONES PARA QUE USEN LOS AUDIOS
reproducir_audio("menu");      /* Al abrir el menu        
reproducir_audio("juego");     /* Al iniciar un nivel     
reproducir_audio("victoria");  /* Al ganar                
reproducir_audio("detener");   /* Al cambiar de pantalla  (después de cada que salgan)*/