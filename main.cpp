#include "SistemaArchivos.h"
#include <iostream>
#include <vector>

void mostrar_menu() {
    std::cout << "\n*** Sistema de Archivos Hibrido ***" << std::endl;
    std::cout << "1. Crear directorio" << std::endl;
    std::cout << "2. Crear archivo" << std::endl;
    std::cout << "3. Listar contenido de directorio" << std::endl;
    std::cout << "4. Buscar nodo por ID" << std::endl;
    std::cout << "5. Eliminar archivo" << std::endl;
    std::cout << "6. Obtener rutas completas de archivo" << std::endl;
    std::cout << "7. Calcular espacio ocupado por directorio" << std::endl;
    std::cout << "8. Mostrar estadisticas" << std::endl;
    std::cout << "9. Salir" << std::endl;
    std::cout << "Seleccione una opcion: ";
}

void limpiar_buffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

int main() {
    SistemaArchivos sistema;
    int opcion;
    
    std::cout << "Sistema de Archivos con Grafos y Arbol B+" << std::endl;
    std::cout << "******************************************" << std::endl;
    std::cout << "Directorio raiz creado automaticamente con ID: 1" << std::endl;
    
    do {
        mostrar_menu();
        std::cin >> opcion;
        
        if (std::cin.fail()) {
            std::cin.clear();
            limpiar_buffer();
            std::cout << "Entrada invalida. Por favor ingrese un numero del 1 al 9." << std::endl;
            continue;
        }
        
        try {
            switch(opcion) {
                case 1: {
                    int id_padre;
                    std::cout << "ID del directorio padre: ";
                    std::cin >> id_padre;
                    if (std::cin.fail()) {
                        std::cout << "ID invalido." << std::endl;
                        limpiar_buffer();
                        break;
                    }
                    sistema.crear_nodo(id_padre, true);
                    break;
                }
                    
                case 2: {
                    int id_padre, tamano, tipo;
                    std::cout << "ID del directorio padre: ";
                    std::cin >> id_padre;
                    std::cout << "Tamano del archivo (bytes): ";
                    std::cin >> tamano;
                    std::cout << "Tipo (0: Imagen, 1: Documento, 2: Ejecutable, 3: Video, 4: Comprimido): ";
                    std::cin >> tipo;
                    
                    if (std::cin.fail() || tipo < 0 || tipo > 4 || tamano < 0) {
                        std::cout << "Datos invalidos." << std::endl;
                        limpiar_buffer();
                        break;
                    }
                    
                    sistema.crear_nodo(id_padre, false, tamano, tipo);
                    break;
                }
                    
                case 3: {
                    int id_directorio;
                    std::cout << "ID del directorio a listar: ";
                    std::cin >> id_directorio;
                    if (std::cin.fail()) {
                        std::cout << "ID invalido." << std::endl;
                        limpiar_buffer();
                        break;
                    }
                    sistema.listar_contenido(id_directorio);
                    break;
                }
                    
                case 4: {
                    int id_buscar;
                    std::cout << "ID del nodo a buscar: ";
                    std::cin >> id_buscar;
                    if (std::cin.fail()) {
                        std::cout << "ID invalido." << std::endl;
                        limpiar_buffer();
                        break;
                    }
                    
                    NodoGrafo* nodo = sistema.buscar_nodo_grafo(id_buscar);
                    if (nodo != nullptr) {
                        std::cout << "\n*** Nodo encontrado ***" << std::endl;
                        std::cout << "ID: " << nodo->obtener_id() << std::endl;
                        std::cout << "Tipo: " << (nodo->es_directorio() ? "Directorio" : "Archivo") << std::endl;
                        std::cout << "Descripcion: " << nodo->obtener_tipo() << std::endl;
                        
                        if (nodo->es_directorio()) {
                            NodoDirectorio* dir = (NodoDirectorio*)nodo;
                            std::cout << "Numero de hijos: " << dir->obtener_hijos().size() << std::endl;
                        }
                    } else {
                        std::cout << "Nodo no encontrado." << std::endl;
                    }
                    break;
                }
                    
                case 5: {
                    int id_archivo, id_padre;
                    std::cout << "ID del archivo a eliminar: ";
                    std::cin >> id_archivo;
                    std::cout << "ID del directorio padre: ";
                    std::cin >> id_padre;
                    
                    if (std::cin.fail()) {
                        std::cout << "IDs invalidos." << std::endl;
                        limpiar_buffer();
                        break;
                    }
                    
                    sistema.eliminar_archivo(id_archivo, id_padre);
                    break;
                }
                    
                case 6: {
                    int id_archivo;
                    std::cout << "ID del archivo: ";
                    std::cin >> id_archivo;
                    
                    if (std::cin.fail()) {
                        std::cout << "ID invalido." << std::endl;
                        limpiar_buffer();
                        break;
                    }
                    
                    std::vector<std::string> rutas = sistema.obtener_rutas_completas(id_archivo);
                    if (rutas.empty()) {
                        std::cout << "No se encontraron rutas para el archivo ID: " << id_archivo << std::endl;
                    } else {
                        std::cout << "\n*** Rutas encontradas (" << rutas.size() << ") ***" << std::endl;
                        for (size_t i = 0; i < rutas.size(); i++) {
                            std::cout << i+1 << ". " << rutas[i] << std::endl;
                        }
                    }
                    break;
                }
                    
                case 7: {
                    int id_directorio;
                    std::cout << "ID del directorio: ";
                    std::cin >> id_directorio;
                    
                    if (std::cin.fail()) {
                        std::cout << "ID invalido." << std::endl;
                        limpiar_buffer();
                        break;
                    }
                    
                    int espacio = sistema.calcular_espacio_ocupado(id_directorio);
                    std::cout << "Espacio total ocupado: " << espacio << " bytes" << std::endl;
                    
                    if (espacio >= 1024 * 1024) {
                        std::cout << "Equivalente a: " << espacio / (1024 * 1024) << " MB" << std::endl;
                    } else if (espacio >= 1024) {
                        std::cout << "Equivalente a: " << espacio / 1024 << " KB" << std::endl;
                    }
                    break;
                }
                    
                case 8: {
                    sistema.mostrar_estadisticas();
                    break;
                }
                    
                case 9: {
                    std::cout << "\n*** Gracias por usar el Sistema de Archivos Hibrido ***" << std::endl;
                    std::cout << "Resumen final:" << std::endl;
                    sistema.mostrar_estadisticas();
                    std::cout << "Saliendo..." << std::endl;
                    break;
                }
                    
                default: {
                    std::cout << "Opcion invalida. Por favor seleccione una opcion del 1 al 9." << std::endl;
                    break;
                }
            }
            
            limpiar_buffer();
            
        } catch (const std::exception& e) {
            std::cout << "\n*** ERROR ***" << std::endl;
            std::cout << "Mensaje: " << e.what() << std::endl;
            std::cout << "Por favor, intente nuevamente." << std::endl;
            limpiar_buffer();
        }
        
    } while (opcion != 9);
    
    return 0;
}