#include "NodoBInterno.h"
#include "NodoBHoja.h"
#include <iostream>
#include <algorithm>

NodoBInterno::NodoBInterno(int orden) 
    : NodoBPlusBase(orden, false) {}

NodoBInterno::~NodoBInterno() {
   
}

NodoBPlusBase* NodoBInterno::buscar(int clave, int& accesos) {
    accesos++;
    if (claves.empty()) {
        return nullptr;
    }
    
    int indice = buscar_siguiente(clave);
    
    if (indice >= 0 && indice < (int)punteros.size() && punteros[indice] != nullptr) {
        return punteros[indice]->buscar(clave, accesos);
    }
    return nullptr;
}

int NodoBInterno::buscar_siguiente(int clave) {
    if (claves.empty()) {
        return 0;
    }
    
    for (int i = 0; i < (int)claves.size(); i++) {
        if (clave < claves[i]) {
            return i;
        }
    }
    return (int)claves.size();
}

void NodoBInterno::insertar(int clave, NodoGrafo* dato, NodoBPlusBase*& nueva_raiz) {
    
    (void)clave;
    (void)dato;
    (void)nueva_raiz;
    
    std::cout << "Inserción en nodo interno" << std::endl;
   
}

void NodoBInterno::dividir(std::vector<int>& claves_izq, std::vector<int>& claves_der,
                          std::vector<void*>& datos_izq, std::vector<void*>& datos_der) {
  
    (void)claves_izq;
    (void)claves_der;
    (void)datos_izq;
    (void)datos_der;
    
    throw std::runtime_error("Metodo dividir no implementado para nodos internos");
}

bool NodoBInterno::esta_vacio() const {
    return claves.empty() && punteros.empty();
}

void NodoBInterno::agregar_puntero_al_final(NodoBPlusBase* puntero) {
    punteros.push_back(puntero);
}

NodoBPlusBase* NodoBInterno::obtener_puntero(int indice) const {
    if (indice >= 0 && indice < (int)punteros.size()) {
        return punteros[indice];
    }
    return nullptr;
}

void NodoBInterno::establecer_puntero(int indice, NodoBPlusBase* puntero) {
    if (indice >= 0 && indice < (int)punteros.size()) {
        punteros[indice] = puntero;
    }
}

NodoBInterno* NodoBInterno::dividir_nodo(int clave_media) {
    
    (void)clave_media;
    
    return new NodoBInterno(orden);
}