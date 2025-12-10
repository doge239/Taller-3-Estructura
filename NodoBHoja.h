#ifndef NODOBHOJA_H
#define NODOBHOJA_H

#include "NodoBPlusBase.h"
#include <vector>

class NodoBHoja : public NodoBPlusBase {
private:
    std::vector<NodoGrafo*> datos;
    NodoBHoja* siguiente;
    
public:
    NodoBHoja(int orden);
    ~NodoBHoja();
    
    NodoBPlusBase* buscar(int clave, int& accesos) override;
    void insertar(int clave, NodoGrafo* dato, NodoBPlusBase*& nueva_raiz) override;
    void dividir(std::vector<int>& claves_izq, std::vector<int>& claves_der,
                std::vector<void*>& datos_izq, std::vector<void*>& datos_der) override;
    
    NodoGrafo* obtener_dato(int indice) const;
    NodoBHoja* obtener_siguiente() const;
    void establecer_siguiente(NodoBHoja* sig);
    
    int buscar_clave_exacta(int clave) const;
    void insertar_ordenado(int clave, NodoGrafo* dato);
};

#endif