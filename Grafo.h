#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <iostream>
#include "Nodo.h"
#include "Arista.h"

class Grafo {
private:
    std::vector<Nodo> nodes; // Vector de nodos
    std::vector<Aristas> edges; // Vector de aristas

public:
    // Función para agregar un nodo al grafo
    void agregarNodo(const Nodo& nodo);

    // Función para agregar una arista al grafo
    void agregarArista(const Nodo& origen, const Nodo& destino, int costoDeViaje);

    // Función para mostrar los nodos del grafo
    void mostrarNodos();

    // Función para mostrar las aristas del grafo
    void mostrarAristas();
};

#endif
