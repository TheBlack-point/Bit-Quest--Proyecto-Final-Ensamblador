# assets/maps/ — Archivos de Mapa
Responsable: Aída (diseño de los 4 mapas)
Coordinación: Carlos (parser que los lee)

---

## Archivos esperados

| Archivo      | Nivel | Dificultad                        |
|--------------|-------|-----------------------------------|
| `nivel1.txt` | 1     | Sencillo, para aprender mecánicas |
| `nivel2.txt` | 2     | Intermedio, más caminos y monedas |
| `nivel3.txt` | 3     | Retador, distribución más compleja|
| `nivel4.txt` | 4     | Extra, para los puntos adicionales|

---

## Formato obligatorio del archivo

- Exactamente **60 líneas**
- Exactamente **60 caracteres por línea** (sin contar el salto de línea)
- Codificación: **ASCII puro** (sin tildes, sin acentos, sin Unicode)
- Terminación de línea: LF (`\n`) — si usas Windows, configura tu editor
  para guardar con LF o Carlos tendrá que limpiar los `\r` en el parser

---

## Símbolos válidos (ASCII interno)

| Char | Significado  | Se verá en pantalla como |
|------|--------------|--------------------------|
| `#`  | Pared        | `█`                      |
| `.`  | Camino libre | `░`                      |
| `P`  | Jugador      | `X`                      |
| `M`  | Moneda       | `©`                      |
| `K`  | Llave        | `¶`                      |
| `D`  | Puerta       | `│`                      |
| `E`  | Salida       | `█`                      |

**Los archivos .txt usan los chars ASCII, NO los símbolos visuales.**
La conversión visual la hace Aída en el código al momento de imprimir.

---

## Reglas de diseño por nivel

Cada mapa debe tener:
- Exactamente **1 llave** (`K`)
- Exactamente **1 puerta** (`D`)
- Exactamente **1 salida** (`E`)
- Al menos **1 jugador** (`P`) que marca la posición inicial
- Varias monedas (`M`) distribuidas por el mapa
- Bordes cerrados con paredes (`#`) para que el jugador no se salga

El jugador (`P`) en el archivo solo indica dónde empieza.
Carlos lo lee, guarda las coordenadas y reemplaza esa celda por `.` en memoria.

---

## Cómo verifica Carlos que el mapa es válido

Al cargar cada archivo Carlos valida:
1. Que tenga exactamente 60 líneas
2. Que cada línea tenga exactamente 60 caracteres
3. Que exista al menos una `K`, una `D`, una `E` y una `P`
4. Que no haya caracteres fuera de los 7 válidos

Si alguna validación falla, el programa imprime el error y se detiene.

---

## Herramienta sugerida para diseñar los mapas

Cualquier editor de texto plano sirve (VS Code, Notepad++, Vim).
En VS Code puedes ver el contador de columnas abajo a la derecha
para asegurarte de que cada línea tenga exactamente 60 caracteres.

Tip: diseña primero en papel o en una hoja de cálculo con celdas
cuadradas, luego transcríbelo al archivo de texto.
