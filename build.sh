#!/bin/bash
# Script para compilar el juego BitQuest en Linux usando NASM y GCC.
# Responsable: Aída la oztia Cons



echo "Ensamblando Rutinas..."
nasm -f elf64 src/rutinas.asm -o src/rutinas.o
if [ $? -ne 0 ]; then
    echo "Error al ensamblar rutinas.asm"
    exit 1
fi

echo "Compilando archivos de C..."
# Usamos -Iinclude para que no marque error con las cabeceras
gcc -c -Iinclude src/main.c -o src/main.o
gcc -c -Iinclude src/juego.c -o src/juego.o
gcc -c -Iinclude src/audio.c -o src/audio.o
if [ $? -ne 0 ]; then
    echo "Error al compilar archivos de C"
    exit 1
fi

echo "Creando Ejecutable..."
# Juntamos los objetos de C y el de ensamblador
gcc src/main.o src/juego.o src/audio.o src/rutinas.o -o bitquest -no-pie
if [ $? -ne 0 ]; then
    echo "Error al crear el ejecutable"
    exit 1
fi

# Borramos la basura (los .o) para que no hagan bola en la carpeta
rm src/*.o

echo ""
echo "EJECUTABLE CREADO: bitquest"
echo "----------------------------------------"
./bitquest