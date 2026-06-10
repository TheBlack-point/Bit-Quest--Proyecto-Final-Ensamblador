# docs/ — Documentación
Responsable: Aída (reporte final en PDF)

---

## Archivos esperados

| Archivo             | Estado       |
|---------------------|--------------|
| `reporte_final.pdf` | Entrega final|

---

## Secciones obligatorias del reporte (según especificación del profesor Irving)

1. **Portada** — nombre del proyecto, curso, integrantes, fecha
2. **Enlace al repositorio de GitHub** — debe ser público y funcionar
3. **Introducción**
4. **Objetivo del proyecto**
5. **Descripción general del juego**
6. **Explicación de la representación del mapa**
   - Mencionar que internamente se usa ASCII (`#`, `.`, `P`, `M`, `K`, `D`, `E`)
   - Explicar la función de traducción visual a Unicode (`║`, `░`, `X`, `©`, `¶`, `Ð`, `█`)
7. **Explicación del funcionamiento de la ventana visible de 20×20**
8. **Explicación de las funciones implementadas en C**
9. **Explicación detallada de las 5 funciones en NASM**
   - Para cada una: qué recibe, qué devuelve, cómo funciona el ciclo interno
10. **Explicación de la fórmula del puntaje** (la que eligió Arthur)
11. **Capturas de pantalla de los 3 niveles obligatorios**
12. **Captura del resumen final del juego**
13. **Instrucciones de compilación y ejecución**
14. **Conclusiones**

---

## Reglas del reporte

- **No pegar todo el código fuente.** El código está en GitHub.
  En el reporte solo van fragmentos pequeños para ilustrar explicaciones.
- Las capturas deben mostrar el juego corriendo en consola con los
  símbolos visuales Unicode (`║`, `░`, `©`, etc.), no el ASCII interno.
- El enlace a GitHub debe estar en la página 1 o 2, visible y clickeable.
- El repositorio debe estar público antes de imprimir el PDF.

---

## Evidencia de puntos extra a documentar (si aplica)

| Mejora implementada              | Dónde documentarla en el reporte     |
|----------------------------------|---------------------------------------|
| Colores ANSI en consola          | Sección de funciones C (Aída)        |
| Pantalla de inicio y victoria    | Capturas de pantalla                 |
| Lectura de mapas desde .txt      | Sección de funciones C (Carlos)      |
| 4 niveles funcionales            | Capturas del nivel 4                 |
| Símbolos Unicode / bloques ASCII | Sección de representación del mapa   |

---

## Cronograma del reporte

| Fecha       | Actividad                                              |
|-------------|--------------------------------------------------------|
| 12 de junio | Aída empieza a redactar mientras el equipo integra     |
| 13 de junio | Agregar capturas de pantalla conforme pasan las pruebas|
| 14 de junio | Revisión final, exportar a PDF, verificar enlace GitHub|
