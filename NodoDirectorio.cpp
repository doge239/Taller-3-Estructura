#include "NodoDirectorio.h"
#include <algorithm>

NodoDirectorio::NodoDirectorio() {}

bool NodoDirectorio::es_directorio() const {
    return true;
}

std::string NodoDirectorio::obtener_tipo() const {
    return "Directorio";
}

void NodoDirectorio::agregar_hijo(int id_hijo) {
    if (std::find(hijos.begin(), hijos.end(), id_hijo) == hijos.end()) {
        hijos.push_back(id_hijo);
    }
}

void NodoDirectorio::eliminar_hijo(int id_hijo) {
    auto it = std::find(hijos.begin(), hijos.end(), id_hijo);
    if (it != hijos.end()) {
        hijos.erase(it);
    }
}

const std::vector<int>& NodoDirectorio::obtener_hijos() const {
    return hijos;
}