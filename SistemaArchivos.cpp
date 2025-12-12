#include "SistemaArchivos.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <sstream>

SistemaArchivos::SistemaArchivos(int orden) 
    : orden_arbol(orden), contador_accesos(0), raiz_arbol(nullptr), raiz_grafo(nullptr) {
    
    raiz_arbol = new NodoBHoja(orden);
    crear_directorio_raiz();
}

SistemaArchivos::~SistemaArchivos() {
    limpiar_sistema();
}

void SistemaArchivos::crear_directorio_raiz() {
    NodoDirectorio* raiz = new NodoDirectorio();
    raiz_grafo = raiz;
    insertar_nodo_grafo(raiz->obtener_id(), raiz);
    std::cout << "Directorio raiz creado con ID: " << raiz->obtener_id() << std::endl;
}

NodoGrafo* SistemaArchivos::buscar_en_arbol(int clave, int& accesos) {
    if (raiz_arbol == nullptr) return nullptr;
    
    NodoBPlusBase* nodo_hoja = raiz_arbol->buscar(clave, accesos);
    if (nodo_hoja != nullptr && nodo_hoja->es_nodo_hoja()) {
        NodoBHoja* hoja = dynamic_cast<NodoBHoja*>(nodo_hoja);
        int indice = hoja->buscar_clave_exacta(clave);
        if (indice != -1) {
            return hoja->obtener_dato(indice);
        }
    }
    return nullptr;
}

void SistemaArchivos::insertar_en_arbol(int clave, NodoGrafo* nodo) {
    NodoBPlusBase* nueva_raiz = nullptr;
    raiz_arbol->insertar(clave, nodo, nueva_raiz);
    
    if (nueva_raiz != nullptr) {
        raiz_arbol = nueva_raiz;
    }
    
    contador_accesos++;
}

void SistemaArchivos::insertar_nodo_grafo(int clave, NodoGrafo* nodo_grafo) {
    if (clave <= 0 || nodo_grafo == nullptr) {
        throw std::invalid_argument("Clave invalida o nodo nulo");
    }
    
    int accesos_temp = 0;
    if (buscar_en_arbol(clave, accesos_temp) != nullptr) {
        throw std::runtime_error("La clave ya existe en el sistema");
    }
    
    insertar_en_arbol(clave, nodo_grafo);
    
    std::cout << "Nodo insertado exitosamente. Clave: " << clave << std::endl;
}

NodoGrafo* SistemaArchivos::buscar_nodo_grafo(int clave) {
    int accesos = 0;
    NodoGrafo* resultado = buscar_en_arbol(clave, accesos);
    
    std::cout << "Busqueda completada. Accesos a disco simulados: " 
              << accesos << std::endl;
    
    return resultado;
}

void SistemaArchivos::crear_nodo(int id_padre, bool es_directorio, int tamano, int tipo) {
    NodoGrafo* padre = buscar_nodo_grafo(id_padre);
    
    if (padre == nullptr || !padre->es_directorio()) {
        throw std::runtime_error("ID de padre invalido o no es directorio");
    }
    
    NodoGrafo* nuevo_nodo;
    if (es_directorio) {
        nuevo_nodo = new NodoDirectorio();
    } else {
        nuevo_nodo = new NodoArchivo(tamano, tipo);
    }
    
    int nuevo_id = nuevo_nodo->obtener_id();
    insertar_nodo_grafo(nuevo_id, nuevo_nodo);
    
    NodoDirectorio* dir_padre = dynamic_cast<NodoDirectorio*>(padre);
    dir_padre->agregar_hijo(nuevo_id);
    nuevo_nodo->agregar_padre(id_padre);
    
    std::cout << "Nodo creado exitosamente. ID: " << nuevo_id 
              << " | Tipo: " << (es_directorio ? "Directorio" : "Archivo")
              << std::endl;
}

void SistemaArchivos::eliminar_referencias_cruzadas(int id_archivo, int id_padre) {
    NodoGrafo* archivo = buscar_nodo_grafo(id_archivo);
    if (archivo == nullptr) return;
    
    NodoGrafo* padre = buscar_nodo_grafo(id_padre);
    if (padre == nullptr || !padre->es_directorio()) return;
    
    NodoDirectorio* dir_padre = dynamic_cast<NodoDirectorio*>(padre);
    dir_padre->eliminar_hijo(id_archivo);
    archivo->eliminar_padre(id_padre);
    
    std::cout << "Referencias cruzadas eliminadas entre archivo " 
              << id_archivo << " y directorio " << id_padre << std::endl;
}

void SistemaArchivos::eliminar_archivo(int id_archivo, int id_directorio_padre) {
    NodoGrafo* archivo = buscar_nodo_grafo(id_archivo);
    
    if (archivo == nullptr || archivo->es_directorio()) {
        throw std::runtime_error("ID no corresponde a un archivo valido");
    }
    
    eliminar_referencias_cruzadas(id_archivo, id_directorio_padre);
    
    if (archivo->obtener_padres().empty()) {
        std::cout << "Archivo eliminado completamente del sistema (ID: " 
                  << id_archivo << ")" << std::endl;
        delete archivo;
    } else {
        std::cout << "Referencia eliminada, archivo aun referenciado por otros directorios" 
                  << std::endl;
    }
}

void SistemaArchivos::listar_contenido(int id_directorio) {
    NodoGrafo* directorio = buscar_nodo_grafo(id_directorio);
    
    if (directorio == nullptr || !directorio->es_directorio()) {
        throw std::runtime_error("ID no corresponde a un directorio");
    }
    
    NodoDirectorio* dir = dynamic_cast<NodoDirectorio*>(directorio);
    const auto& hijos = dir->obtener_hijos();
    
    std::cout << "\n=== Contenido del directorio ID " << id_directorio << " ===" << std::endl;
 
    
    if (hijos.empty()) {
        std::cout << "El directorio esta vacio." << std::endl;
        return;
    }
    
    for (int hijo_id : hijos) {
        NodoGrafo* hijo = buscar_nodo_grafo(hijo_id);
        if (hijo != nullptr) {
            std::cout << "ID: " << hijo_id 
                      << "  Tipo: " << (hijo->es_directorio() ? "Directorio" : "Archivo")
                      << "  Descripcion: " << hijo->obtener_tipo();
            
            if (!hijo->es_directorio()) {
                NodoArchivo* archivo = dynamic_cast<NodoArchivo*>(hijo);
                std::cout << "  Tamano: " << archivo->obtener_tamano() << " bytes";
            }
            std::cout << std::endl;
        }
    }
    
   
    std::cout << "Total elementos: " << hijos.size() << std::endl;
}

std::vector<std::string> SistemaArchivos::obtener_rutas_completas(int id_archivo) {
    std::vector<std::string> rutas;
    NodoGrafo* archivo = buscar_nodo_grafo(id_archivo);
    
    if (archivo == nullptr) {
        return rutas;
    }
    
    std::function<void(int, std::string)> construir_ruta_recursiva = 
    [&](int nodo_id, std::string ruta_parcial) {
        NodoGrafo* nodo = buscar_nodo_grafo(nodo_id);
        if (nodo == nullptr) return;
        
        std::string nombre_nodo;
        if (nodo->es_directorio()) {
            nombre_nodo = "dir_" + std::to_string(nodo_id);
        } else {
            nombre_nodo = "file_" + std::to_string(nodo_id);
        }
        
        if (ruta_parcial.empty()) {
            ruta_parcial = "/" + nombre_nodo;
        } else {
            ruta_parcial = "/" + nombre_nodo + ruta_parcial;
        }
        
        if (!nodo->es_directorio() && nodo->obtener_padres().empty()) {
            rutas.push_back(ruta_parcial);
            return;
        }
        
        if (!nodo->obtener_padres().empty()) {
            for (int padre_id : nodo->obtener_padres()) {
                construir_ruta_recursiva(padre_id, ruta_parcial);
            }
        } else {
            rutas.push_back(ruta_parcial);
        }
    };
    
    construir_ruta_recursiva(id_archivo, "");
    return rutas;
}

int SistemaArchivos::calcular_espacio_ocupado(int id_directorio) {
    NodoGrafo* inicio = buscar_nodo_grafo(id_directorio);
    
    if (inicio == nullptr || !inicio->es_directorio()) {
        std::cout << "ERROR: ID no corresponde a un directorio valido" << std::endl;
        return 0;
    }
    
    int espacio_total = 0;
    std::unordered_set<int> visitados;
    std::queue<int> cola;
    
    cola.push(id_directorio);
    visitados.insert(id_directorio);
    
    while (!cola.empty()) {
        int actual_id = cola.front();
        cola.pop();
        
        NodoGrafo* actual = buscar_nodo_grafo(actual_id);
        if (actual == nullptr) continue;
        
        if (!actual->es_directorio()) {
            NodoArchivo* archivo = dynamic_cast<NodoArchivo*>(actual);
            if (archivo != nullptr) {
                espacio_total += archivo->obtener_tamano();
                std::cout << "  + Archivo " << actual_id << ": " 
                          << archivo->obtener_tamano() << " bytes" << std::endl;
            }
        } else {
            NodoDirectorio* dir = dynamic_cast<NodoDirectorio*>(actual);
            if (dir != nullptr) {
                for (int hijo_id : dir->obtener_hijos()) {
                    if (visitados.find(hijo_id) == visitados.end()) {
                        visitados.insert(hijo_id);
                        cola.push(hijo_id);
                    }
                }
            }
        }
    }
    
    return espacio_total;
}

void SistemaArchivos::mostrar_estadisticas() const {
    std::cout << "\n=== Estadisticas del Sistema ===" << std::endl;
    std::cout << "Accesos a disco simulados: " << contador_accesos << std::endl;
    std::cout << "Orden del arbol B+: " << orden_arbol << std::endl;
    std::cout << "Directorio raiz ID: " 
              << (raiz_grafo ? std::to_string(raiz_grafo->obtener_id()) : "Ninguno") 
              << std::endl;
}

void SistemaArchivos::limpiar_sistema() {
    if (raiz_arbol != nullptr) {
        delete raiz_arbol;
        raiz_arbol = nullptr;
    }
    
    contador_accesos = 0;
    raiz_grafo = nullptr;
    
    std::cout << "Sistema limpiado exitosamente." << std::endl;
}

int SistemaArchivos::obtener_total_accesos() const {
    return contador_accesos;
}