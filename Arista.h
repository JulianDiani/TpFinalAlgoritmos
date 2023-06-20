#ifndef ARISTAS_H
#define ARISTAS_H

#include "Nodo.h"

class Aristas {
public:
    Nodo origen;
    Nodo destino;
    int costoDeViaje;
    double horasViaje;

    // Constructor de la clase Aristas
    Aristas(const Nodo& src, const Nodo& dest, int w,double h);
};

#endif
