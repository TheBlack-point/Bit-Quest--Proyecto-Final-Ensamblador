# src/ — Código Fuente
Responsables: Leo (main.c, juego.c) · Beto (rutinas.asm F1 y F2) · Arthur (rutinas.asm F3, F4 y F5)

---

## Archivos en esta carpeta

### main.c — Leo
Punto de entrada del programa. Contiene:
- Menú principal y pantalla de inicio (coordinado con Aída para los colores)
- Control del flujo general: cargar nivel → jugar → resumen → siguiente nivel
- Resumen final al terminar los 4 niveles
- Llamada a `calcular_puntaje()` de NASM para el puntaje final

### juego.c — Leo
Motor del juego. Contiene:
- `renderizar_ventana_visible()` → imprime la ventana 20x20 usando los símbolos Unicode
- `mover_jugador()` → procesa W/A/S/D y llama a las funciones NASM antes de mover
- `desplegar_pantalla_resumen()` → resumen al terminar cada nivel
- Definición de los arreglos `mapa_nivel1[]` ... `mapa_nivel4[]`

**Importante para Leo:** el mapa interno siempre usa ASCII puro (`#`, `.`, `P`, `M`, `K`, `D`, `E`).
La conversión a símbolos visuales Unicode ocurre únicamente dentro de `renderizar_ventana_visible()`,
usando la función `traducir_simbolo()` que implementa Aída.

### rutinas.asm — Beto y Arthur
Las 5 funciones obligatorias en NASM de 64 bits. Todas trabajan sobre el mapa
interno en ASCII, nunca sobre los símbolos Unicode visuales.

| Función                | Responsable | Descripción                                      |
|------------------------|-------------|--------------------------------------------------|
| `contar_caracteres`    | Beto        | Cuenta cuántas veces aparece un char en el mapa  |
| `validar_movimiento`   | Beto        | Verifica si una celda es transitable (no es `#`) |
| `calcular_puntaje`     | Arthur      | Calcula el puntaje con monedas, pasos y niveles  |
| `detectar_objeto`      | Arthur      | Detecta si hay un objeto en una celda específica |
| `contar_celdas_libres` | Arthur      | Cuenta todas las celdas `.` del mapa             |

---

## Tabla de símbolos internos (ASCII) — todos deben usar esta tabla

| Char interno | Significado  | Visual en pantalla |
|--------------|--------------|--------------------|
| `#`          | Pared        | `║` (y variantes)  |
| `.`          | Camino libre | `░`                |
| `P`          | Jugador      | `X`                |
| `M`          | Moneda       | `©`                |
| `K`          | Llave        | `¶`                |
| `D`          | Puerta       | `Ð`                |
| `E`          | Salida       | `█`                |

**Regla de oro:** Beto y Arthur comparan contra los chars ASCII (`#`, `M`, `K`, etc.),
nunca contra los símbolos Unicode. Leo también opera sobre ASCII internamente.
Solo Aída traduce al imprimir.

---

## Convención de llamadas NASM (Linux — System V AMD64)

Los parámetros se pasan en este orden:
```
RDI → 1er parámetro
RSI → 2do parámetro
RDX → 3er parámetro
RCX → 4to parámetro
R8  → 5to parámetro
RAX → valor de retorno
```

En Windows la convención cambia (RCX, RDX, R8, R9). Revisar con Aída qué
sistema se usará como principal para no mezclar convenciones.

---

## Indexación del mapa (para Beto, Arthur y Leo)

El mapa es un arreglo lineal de `char` de 3600 elementos (60 × 60).
Para acceder a la celda en fila `f`, columna `c`:
```c
mapa[f * 60 + c]
```
En NASM:
```asm
imul rdx, rsi    ; fila * num_columnas
add  rdx, rcx   ; + columna
mov  al, byte [rdi + rdx]
```
