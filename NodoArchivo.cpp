#include "NodoArchivo.h"
#include <stdexcept>

NodoArchivo::NodoArchivo(int tam, int tipo_archivo) : tamano(tam), tipo(tipo_archivo) {
    if (tipo < 0 || tipo > 4) {
        throw std::invalid_argument("Tipo de archivo invalido. Debe ser 0-4");
    }
}

bool NodoArchivo::es_directorio() const {
    return false;
}

std::string NodoArchivo::obtener_tipo() const {
    switch(tipo) {
        case 0: return "Imagen";
        case 1: return "Documento";
        case 2: return "Ejecutable";
        case 3: return "Video";
        case 4: return "Comprimido";
        default: return "Desconocido";
    }
}

int NodoArchivo::obtener_tamano() const {
    return tamano;
}