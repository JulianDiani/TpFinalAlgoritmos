#include "Grafo.h"

void Grafo::agregarNodo(const Nodo& nodo) {
    nodes.push_back(nodo);
}

void Grafo::agregarArista(const Nodo& origen, const Nodo& destino, int costoDeViaje) {
    Aristas edge(origen, destino, costoDeViaje);
    edges.push_back(edge);
}

void Grafo::mostrarNodos() {
    std::cout << "Nodos en el grafo:" << std::endl;
    for (const auto& nodo : nodes) {
        std::cout << "Nodo " << nodo.codigoOrigen << std::endl;
    }
}

void Grafo::mostrarAristas() {
    std::cout << "Aristas en el grafo:" << std::endl;
    for (const auto& nodo : nodes) {
        std::cout << "Nodo " << nodo.codigoOrigen << ":" << std::endl;
        for (const auto& edge : edges) {
            if (edge.origen.codigoOrigen == nodo.codigoOrigen) {
                std::cout << " (Nodo origen: " << edge.origen.codigoOrigen << " -> Nodo destino: " << edge.destino.codigoOrigen << "), Costo de viaje: " << edge.costoDeViaje << std::endl;
            }
        }
        std::cout << std::endl;
    }
}
