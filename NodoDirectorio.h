#ifndef NODODIRECTORIO_H
#define NODODIRECTORIO_H

#include "NodoGrafo.h"
#include <vector>

class NodoDirectorio : public NodoGrafo {
private:
    std::vector<int> hijos;
    
public:
    NodoDirectorio();
    bool es_directorio() const override;
    std::string obtener_tipo() const override;
    
    void agregar_hijo(int id_hijo);
    void eliminar_hijo(int id_hijo);
    const std::vector<int>& obtener_hijos() const;
};

#endif