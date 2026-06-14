@echo off
REM Script para compilar el juego BitQuest en Windows usando NASM y GCC.
REM Responsable: Aída la oztia Cons

echo Ensamblando Rutinas...
nasm -f win64 src\rutinas_win.asm -o src\rutinas.obj
if errorlevel 1 (
    echo Error al ensamblar rutinas_win.asm
    pause
    exit /b 1
)

echo Compilando archivos de C...
REM Usamos -Iinclude para que no marque error con las cabeceras
gcc -c -Iinclude src\main.c -o src\main.obj
gcc -c -Iinclude src\juego.c -o src\juego.obj
gcc -c -Iinclude src\audio.c -o src\audio.obj
if errorlevel 1 (
    echo Error al compilar archivos de C
    pause
    exit /b 1
)

echo Creando Ejecutable...
REM Juntamos los objetos de C y el de ensamblador, -lwinmm para el audio
gcc src\main.obj src\juego.obj src\audio.obj src\rutinas.obj -o bitquest.exe -lwinmm
if errorlevel 1 (
    echo Error al crear el ejecutable
    pause
    exit /b 1
)

REM Borramos la basura (los .obj) para que no hagan bola en la carpeta
del src\*.obj

echo.
echo EJECUTABLE CREADO: bitquest.exe
echo ----------------------------------------
bitquest.exe
pause