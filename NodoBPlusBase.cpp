#include "NodoBPlusBase.h"
#include <algorithm>

NodoBPlusBase::NodoBPlusBase(int orden, bool es_hoja) 
    : orden(orden), es_hoja(es_hoja) {}

bool NodoBPlusBase::esta_lleno() const {
    return (int)claves.size() >= orden * 2;
}

int NodoBPlusBase::obtener_orden() const {
    return orden;
}

bool NodoBPlusBase::es_nodo_hoja() const {
    return es_hoja;
}

const std::vector<int>& NodoBPlusBase::obtener_claves() const {
    return claves;
}