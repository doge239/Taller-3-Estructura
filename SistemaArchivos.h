#ifndef SISTEMAARCHIVOS_H
#define SISTEMAARCHIVOS_H

#include "NodoBInterno.h"
#include "NodoBHoja.h"
#include "NodoDirectorio.h"
#include "NodoArchivo.h"
#include <unordered_set>
#include <queue>
#include <functional>
#include <memory>

class SistemaArchivos {
private:
    NodoBPlusBase* raiz_arbol;
    int orden_arbol;
    int contador_accesos;
    NodoGrafo* raiz_grafo;
    
    // Métodos auxiliares privados (en español)
    NodoGrafo* buscar_en_arbol(int clave, int& accesos);
    void insertar_en_arbol(int clave, NodoGrafo* nodo);
    void eliminar_referencias_cruzadas(int id_archivo, int id_padre);
    
public:
    SistemaArchivos(int orden = 3);
    ~SistemaArchivos();
    
    // Funciones requeridas para el taller (en inglés como pide el PDF)
    void insertar_nodo_grafo(int clave, NodoGrafo* nodo_grafo);
    NodoGrafo* buscar_nodo_grafo(int clave);
    void crear_nodo(int id_padre, bool es_directorio = false, 
                   int tamano = 0, int tipo = 0);
    void eliminar_archivo(int id_archivo, int id_directorio_padre);
    void listar_contenido(int id_directorio);
    std::vector<std::string> obtener_rutas_completas(int id_archivo);
    int calcular_espacio_ocupado(int id_directorio);
    
    // Métodos adicionales (en español)
    void mostrar_estadisticas() const;
    void limpiar_sistema();
    int obtener_total_accesos() const;
    void crear_directorio_raiz();
};

#endif