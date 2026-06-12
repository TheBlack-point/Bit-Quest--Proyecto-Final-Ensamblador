# BitQuest: Explorador de Matrices con C y NASM

BitQuest es un videojuego de consola desarrollado mediante programación híbrida en C y Ensamblador (NASM de 64 bits). En este juego, el jugador explora un laberinto representado por una matriz, recolectando monedas, buscando una llave y encontrando la salida para avanzar al siguiente nivel.

Materia: Lenguaje Ensamblador Fecha de entrega: 15 de junio de 2026

## Cómo compilar y ejecutar

### Windows (MinGW-w64 + NASM)

1. Instala [NASM](https://www.nasm.us/) y [MinGW-w64](https://winlibs.com/) y agrégalos al PATH.
2. Desde la raíz del proyecto, ejecuta:

```
build.bat
```

Opciones adicionales:
```
build.bat compile   # Solo compila, no ejecuta
build.bat run       # Solo ejecuta (requiere compilación previa)
build.bat clean     # Elimina archivos objeto y ejecutable
```

### Linux / Ubuntu (GCC + NASM)

1. Instala las dependencias:
```bash
sudo apt install nasm gcc
```

2. Dale permisos al script y ejecútalo:
```bash
chmod +x build.sh
./build.sh
```

Opciones adicionales:
```bash
./build.sh compile   # Solo compila
./build.sh run       # Solo ejecuta
./build.sh clean     # Limpia archivos generados
```

---

## Controles del juego

| Tecla | Acción              |
|-------|---------------------|
| W     | Mover hacia arriba  |
| A     | Mover a la izquierda|
| S     | Mover hacia abajo   |
| D     | Mover a la derecha  |
| Q     | Salir del juego     | (Menú de pausa para confirmación)

---

## Símbolos del mapa

| Símbolo | Significado |
|---------|-------------|
| `█`     | Pared       | (Y variantes)
| `░`     | Camino libre|
| `X`     | Jugador     |
| `©`     | Moneda      |
| `¶`     | Llave       |
| `│`     | Puerta      |
| `█`    | Salida       |

Referencia: https://elcodigoascii.com.ar/codigos-ascii-extendidos/bloque-negro-solido-caracter-grafico-codigo-ascii-219.html
---

## Estructura del proyecto y repartición de labores

```
BitQuest_Team/
├── src/
│   ├── main.c          # Menú y control general (Leo)
│   ├── juego.c         # Viewport, movimiento, renderizado (Leo)
│   └── rutinas.asm     # 5 funciones obligatorias NASM (Beto, Arthur)
├── include/
│   ├── juego.h         # Prototipos de C y NASM
├── assets/
│   ├── maps/           # Archivos nivel1.txt ... nivel4.txt (Aída)
│   └── audio/          # Música y efectos de sonido (Aída)
├── docs/
│   ├──Plan de trabajo Oficial.pdf
│   └── reporte_final.pdf
│ 
├── build.bat           # Compilación Windows (Aída)
├── build.sh            # Compilación Linux (Aída)
└── README.md
```

---

## Equipo

| Integrante | Rol                              |
|------------|----------------------------------|
| Aída       | Líder, DevOps, Arte Visual, Audio|
| Leo        | Motor del juego (C)              |
| Beto       | NASM Módulo A (Funciones 1 y 2)  |
| Arthur     | NASM Módulo B (Funciones 3, 4, 5)|
| Carlos     | Persistencia y transiciones (C)  |
