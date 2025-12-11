#ifndef NODOGRAFO_H
#define NODOGRAFO_H

#include <vector>
#include <string>
#include <memory>

class NodoGrafo {
protected:
    int id;
    std::vector<int> padres;
    static int contadorIDs;
    
public:
    NodoGrafo();
    virtual ~NodoGrafo() = default;
    
    virtual bool es_directorio() const = 0;
    virtual std::string obtener_tipo() const = 0;
    
    void agregar_padre(int id_padre);
    void eliminar_padre(int id_padre);
    const std::vector<int>& obtener_padres() const;
    int obtener_id() const;
    
    static int generar_nuevo_id();
};

#endif