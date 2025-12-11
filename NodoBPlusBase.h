#ifndef NODOBPLUSBASE_H
#define NODOBPLUSBASE_H

#include "NodoGrafo.h"
#include <vector>

class NodoBPlusBase {
protected:
    std::vector<int> claves;
    int orden;
    bool es_hoja;
    
public:
    NodoBPlusBase(int orden, bool es_hoja);
    virtual ~NodoBPlusBase() = default;
    
    virtual NodoBPlusBase* buscar(int clave, int& accesos) = 0;
    virtual void insertar(int clave, NodoGrafo* dato, NodoBPlusBase*& nueva_raiz) = 0;
    virtual void dividir(std::vector<int>& claves_izq, std::vector<int>& claves_der,
                        std::vector<void*>& datos_izq, std::vector<void*>& datos_der) = 0;
    
    bool esta_lleno() const;
    int obtener_orden() const;
    bool es_nodo_hoja() const;
    const std::vector<int>& obtener_claves() const;
};

#endif