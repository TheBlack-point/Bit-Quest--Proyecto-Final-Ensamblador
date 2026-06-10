# assets/audio/ — Recursos de Audio
Responsable: Aída
Prioridad: Punto extra — implementar solo si el proyecto base ya funciona

---

## Eventos de audio planeados

| Evento              | Tipo        |
|---------------------|-------------|
| Recoger moneda `©`  | Efecto corto |
| Recoger llave `¶`   | Efecto corto |
| Cruzar puerta `Ð`   | Efecto corto |
| Completar nivel     | Melodía corta|
| Pantalla de victoria| Melodía larga|
| Salir (`Q`)         | Efecto corto |

---

## Implementación sugerida según sistema operativo

### Windows — opción más simple
```c
#include <windows.h>

// Reproduce un tono sin archivos externos
Beep(880, 150);   // moneda  (880 Hz, 150 ms)
Beep(1047, 250);  // llave   (Do alto, 250 ms)
Beep(659, 400);   // puerta  (Mi, 400 ms)
```
No requiere archivos de audio ni librerías extra.

### Linux — opción con archivos .wav
```c
// Requiere que el sistema tenga aplay instalado (viene por defecto en Ubuntu)
system("aplay -q assets/audio/moneda.wav &");
```
El `&` al final hace que no bloquee el juego mientras suena.

---

## Si se usan archivos .wav

Colocarlos aquí con estos nombres exactos para que el código los encuentre:

| Archivo          | Evento              |
|------------------|---------------------|
| `moneda.wav`     | Recoger moneda      |
| `llave.wav`      | Recoger llave       |
| `puerta.wav`     | Cruzar puerta       |
| `nivel_ok.wav`   | Completar nivel     |
| `victoria.wav`   | Pantalla de victoria|
| `salir.wav`      | Salir del juego     |

Requisitos de los archivos:
- Formato: WAV (PCM, sin compresión)
- Tamaño: menos de 200 KB cada uno
- Duración: efectos cortos menos de 1 segundo, melodías menos de 5 segundos

---

## Recordatorio

El audio es mejora opcional. El proyecto base debe compilar y funcionar
correctamente sin esta carpeta. No bloquear el avance del equipo
esperando que el audio esté listo.
