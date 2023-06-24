#ifndef NODO_H
#define NODO_H

#include "Estacion.h"

class Nodo {
public:
    Estacion* estacion;  // Puntero a Estacion

    // Constructor de la clase Nodo
    Nodo(Estacion* estacion);
};

#endif

