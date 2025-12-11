#ifndef NODOBINTERNO_H
#define NODOBINTERNO_H

#include "NodoBPlusBase.h"
#include <vector>

class NodoBInterno : public NodoBPlusBase {
private:
    std::vector<NodoBPlusBase*> punteros;
    
public:
    NodoBInterno(int orden);
    ~NodoBInterno();
    
    NodoBPlusBase* buscar(int clave, int& accesos) override;
    void insertar(int clave, NodoGrafo* dato, NodoBPlusBase*& nueva_raiz) override;
    void dividir(std::vector<int>& claves_izq, std::vector<int>& claves_der,
                std::vector<void*>& datos_izq, std::vector<void*>& datos_der) override;
    
    int buscar_siguiente(int clave);
    bool esta_vacio() const;
    
    void agregar_puntero_al_final(NodoBPlusBase* puntero);
    NodoBPlusBase* obtener_puntero(int indice) const;
    void establecer_puntero(int indice, NodoBPlusBase* puntero);
    
    NodoBInterno* dividir_nodo(int clave_media);
};

#endif