#include "NodoGrafo.h"
#include <algorithm>

// Inicializar el contador estático
int NodoGrafo::contadorIDs = 1;

NodoGrafo::NodoGrafo() : id(generar_nuevo_id()) {}

int NodoGrafo::generar_nuevo_id() {
    return contadorIDs++;
}

void NodoGrafo::agregar_padre(int id_padre) {
    if (std::find(padres.begin(), padres.end(), id_padre) == padres.end()) {
        padres.push_back(id_padre);
    }
}

void NodoGrafo::eliminar_padre(int id_padre) {
    auto it = std::find(padres.begin(), padres.end(), id_padre);
    if (it != padres.end()) {
        padres.erase(it);
    }
}

const std::vector<int>& NodoGrafo::obtener_padres() const {
    return padres;
}

int NodoGrafo::obtener_id() const {
    return id;
}