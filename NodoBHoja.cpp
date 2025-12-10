#include "NodoBHoja.h"
#include <iostream>
#include <algorithm>

NodoBHoja::NodoBHoja(int orden) 
    : NodoBPlusBase(orden, true), siguiente(nullptr) {}

NodoBHoja::~NodoBHoja() {
    
}

NodoBPlusBase* NodoBHoja::buscar(int clave, int& accesos) {
    accesos++;
    int indice = buscar_clave_exacta(clave);
    if (indice != -1) {
        return this;
    }
    return nullptr;
}

int NodoBHoja::buscar_clave_exacta(int clave) const {
    auto it = std::find(claves.begin(), claves.end(), clave);
    if (it != claves.end()) {
        return std::distance(claves.begin(), it);
    }
    return -1;
}

void NodoBHoja::insertar(int clave, NodoGrafo* dato, NodoBPlusBase*& nueva_raiz) {
    if ((int)claves.size() < orden * 2) {
        insertar_ordenado(clave, dato);
        nueva_raiz = nullptr;
    } else {
        std::cout << "Nodo hoja lleno, dividiendo..." << std::endl;
        
        std::vector<int> claves_izq, claves_der;
        std::vector<void*> datos_izq, datos_der;
        
        dividir(claves_izq, claves_der, datos_izq, datos_der);
        
        NodoBHoja* nuevo_nodo = new NodoBHoja(orden);
        nuevo_nodo->establecer_siguiente(nullptr);
        nueva_raiz = this;
    }
}

void NodoBHoja::insertar_ordenado(int clave, NodoGrafo* dato) {
    auto it = std::lower_bound(claves.begin(), claves.end(), clave);
    int pos = std::distance(claves.begin(), it);
    
    claves.insert(it, clave);
    datos.insert(datos.begin() + pos, dato);
}

void NodoBHoja::dividir(std::vector<int>& claves_izq, std::vector<int>& claves_der,
                       std::vector<void*>& datos_izq, std::vector<void*>& datos_der) {
    int mitad = (int)claves.size() / 2;
    
    for (int i = 0; i < mitad; i++) {
        claves_izq.push_back(claves[i]);
        datos_izq.push_back(datos[i]);
    }
    
    for (int i = mitad; i < (int)claves.size(); i++) {
        claves_der.push_back(claves[i]);
        datos_der.push_back(datos[i]);
    }
}

NodoGrafo* NodoBHoja::obtener_dato(int indice) const {
    if (indice >= 0 && indice < (int)datos.size()) {
        return datos[indice];
    }
    return nullptr;
}

NodoBHoja* NodoBHoja::obtener_siguiente() const {
    return siguiente;
}

void NodoBHoja::establecer_siguiente(NodoBHoja* sig) {
    siguiente = sig;
}