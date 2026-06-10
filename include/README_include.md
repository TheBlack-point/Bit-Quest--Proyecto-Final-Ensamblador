# include/ — Archivos de Cabecera
Responsable: Leo (mantiene juego.h actualizado)

---

## Archivos en esta carpeta

### juego.h
Header principal del proyecto. **Todos los archivos `.c` deben incluirlo:**
```c
#include "juego.h"
```

Contiene:
- Constantes globales (`FILAS_MAPA`, `COLS_MAPA`, `FILAS_VISTA`, `COLS_VISTA`)
- `extern` de los arreglos de mapa (`mapa_nivel1[]` ... `mapa_nivel4[]`)
- Rutas a los archivos `.txt` de los mapas
- Prototipos de las 5 funciones NASM (`extern`)
- Prototipos de las funciones de C (`juego.c` y `main.c`)

---

## Reglas para modificar juego.h

- Solo Leo modifica este archivo para evitar conflictos en Git.
- Si Beto o Arthur necesitan cambiar la firma de una función NASM,
  le avisan a Leo para que actualice el prototipo `extern` correspondiente.
- Si Carlos necesita agregar una función de carga o transición, le avisa a Leo.

---

## Prototipos de las funciones NASM (referencia rápida)

```c
// Función 1 - Beto
extern long long contar_caracteres(char* mapa, int total_celdas, char caracter);

// Función 2 - Beto
extern int validar_movimiento(char* mapa, int columnas, int nueva_fila, int nueva_col);

// Función 3 - Arthur
extern long long calcular_puntaje(int monedas, int pasos, int niveles);

// Función 4 - Arthur
extern int detectar_objeto(char* mapa, int columnas, int fila, int col, char objeto);

// Función 5 - Arthur
extern long long contar_celdas_libres(char* mapa, int total_celdas);
```

---

## Constantes importantes

```c
#define FILAS_MAPA   60
#define COLS_MAPA    60
#define FILAS_VISTA  20
#define COLS_VISTA   20
#define TOTAL_CELDAS (FILAS_MAPA * COLS_MAPA)  // 3600
#define NUM_NIVELES  4

#define RUTA_NIVEL1  "assets/maps/nivel1.txt"
#define RUTA_NIVEL2  "assets/maps/nivel2.txt"
#define RUTA_NIVEL3  "assets/maps/nivel3.txt"
#define RUTA_NIVEL4  "assets/maps/nivel4.txt"
```

---

## ¿Por qué ya no hay mapas.h?

Los mapas se cargan desde archivos `.txt` en tiempo de ejecución.
No hay arreglos hardcodeados en ningún header. Los arreglos en memoria
(`mapa_nivel1[]`, etc.) están definidos en `juego.c` y declarados
como `extern` aquí en `juego.h`.
