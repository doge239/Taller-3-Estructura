# TALLER 3 - Sistema de Archivos con Grafo y Árbol B+

## Integrantes del Grupo
- **Nicolás Cortes Vergara** - 21.193.893-5
- **Enzo Moroso Inostroza** - 20.938.335-7

Repositorio
- URL: https://github.com/doge239/Taller-3-Estructura
- Rama principal: main

## Descripción del Proyecto
Implementación de un sistema de archivos híbrido que combina un **grafo dirigido** (para la estructura lógica) con un **árbol B+** (para el índice físico). El sistema simula el acceso a archivos y directorios en un entorno donde cada operación de lectura/escritura implica acceso a disco, optimizando los tiempos mediante estructuras de datos avanzadas.

## Características Principales
- **Modelado con Grafos**: Los nodos representan archivos/directorios; las aristas representan relaciones "contiene".
- **Índice con Árbol B+**: Clave única = ID del nodo, para búsquedas rápidas con bajo costo de E/S simuladas.
- **Operaciones Completas**: Inserción, búsqueda, eliminación, listado de contenido, rutas completas y cálculo de espacio ocupado.
- **Conteo de Accesos**: Cada búsqueda en el árbol B+ incrementa un contador que simula lecturas de disco.

## Compilación y Ejecución
El proyecto está desarrollado en C++ estándar. Para compilar:

```bash
# Compilación con todos los archivos fuente
g++ -std=c++14 -o sistema_archivos *.cpp

# Ejecución
./sistema_archivos

#Otro metodo para compilar de Manera ordenada

g++ -std=c++14 -Wall -Wextra -o sistema_archivos \
    NodoGrafo.cpp \
    NodoDirectorio.cpp \
    NodoArchivo.cpp \
    NodoBPlusBase.cpp \
    NodoBInterno.cpp \
    NodoBHoja.cpp \
    SistemaArchivos.cpp \
    main.cpp

Archivos Principales

SistemaArchivos.h/cpp: Clase principal que coordina grafo + árbol B+.

NodoGrafo.h/cpp: Clase base abstracta para archivos/directorios.

NodoDirectorio.h/cpp: Implementación de directorios.

NodoArchivo.h/cpp: Implementación de archivos.

NodoBPlusBase.h/cpp: Clase base abstracta del árbol B+.

NodoBInterno.h/cpp: Nodos internos del árbol B+.

NodoBHoja.h/cpp: Hojas del árbol B+.

Funciones Implementadas (según enunciado)
insertar_nodo_grafo() – Inserta nodo en árbol B+ con manejo de overflow.

buscar_nodo_grafo() – Búsqueda desde raíz con conteo de accesos.

crear_nodo() – Crea archivo/directorio y actualiza referencias.

eliminar_archivo() – Elimina referencias y nodo si no hay más padres.

listar_contenido() – Lista hijos de un directorio (cada acceso vía B+).

obtener_rutas_completas() – Genera todas las rutas desde raíz a archivo.

calcular_espacio_ocupado() – Calcula espacio recursivo (BFS/DFS).
