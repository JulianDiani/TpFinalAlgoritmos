#include "Arista.h"

// Implementación del constructor de la clase Aristas
Aristas::Aristas(const Nodo& src, const Nodo& dest, int w) : origen(src), destino(dest), costoDeViaje(w) {}
