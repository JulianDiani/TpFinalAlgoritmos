#ifndef ARISTAS_H
#define ARISTAS_H

#include "Nodo.h"

class Aristas {
public:
    Nodo origen;
    Nodo destino;
    int costoDeViaje;

    // Constructor de la clase Aristas
    Aristas(const Nodo& src, const Nodo& dest, int w);
};

#endif
