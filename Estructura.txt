# Bit-Quest--Proyecto-Final-Ensamblador
Repositorio destinado al desarrollo del proyecto final "Bit Quest" para la materia de Lenguaje Ensamblador

A continuación se detalla la estructura preeliminar que buscaremos implementar en el proyecto

BitQuest/
├── src/                  # Código fuente
│   ├── main.c            # Control general, menús e inicialización 
│   ├── juego.c           # Lógica del viewport, movimiento y renderizado 
│   └── rutinas.asm       # Las 5 funciones obligatorias en NASM 
├── include/              # Cabeceras
│   ├── juego.h           # Prototipos de C 
│   └── mapas.h           # Declaración de los 4 mapas (60x60) 
├── assets/               # Recursos extra (tus tareas)
│   └── audio/            # Archivos de música y efectos de sonido
├── docs/                 # Documentación
│   └── reporte_final.pdf # El reporte para el profesor Irving
├── build.bat             # Script de compilación para Windows 
└── README.md             # Instrucciones de compilación y ejecución
