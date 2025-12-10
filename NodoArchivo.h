#ifndef NODOARCHIVO_H
#define NODOARCHIVO_H

#include "NodoGrafo.h"

class NodoArchivo : public NodoGrafo {
private:
    int tamano;
    int tipo;  // 0: Imagen; 1: Documento; 2: ejecutable; 3: Video; 4: Comprimido
    
public:
    NodoArchivo(int tam, int tipo_archivo);
    bool es_directorio() const override;
    std::string obtener_tipo() const override;
    int obtener_tamano() const;
};

#endif