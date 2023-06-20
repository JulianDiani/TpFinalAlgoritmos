#include "Grafo.h"

void Grafo::agregarNodo(const Nodo& nodo) {
    nodos.push_back(nodo);
}

void Grafo::agregarArista(const Nodo& origen, const Nodo& destino, int costoDeViaje,double horasViaje) {
    Aristas arista(origen, destino, costoDeViaje,horasViaje);
    aristas.push_back(arista);
}

void Grafo::mostrarNodos() {
    std::cout << "Nodos en el grafo:" << std::endl;
    for (const auto& nodo : nodos) {
        std::cout << "Nodo " << nodo.codigoOrigen << std::endl;
    }
}

void Grafo::mostrarAristas() {
    std::cout << "Aristas en el grafo:" << std::endl;
    for (const auto& nodo : nodos) {
        std::cout << "Nodo " << nodo.codigoOrigen << ":" << std::endl;
        for (const auto& arista : aristas) {
            if (arista.origen.codigoOrigen == nodo.codigoOrigen) {
                std::cout << " (Nodo origen: " << arista.origen.codigoOrigen << " -> Nodo destino: " << arista.destino.codigoOrigen << "), Costo de viaje: " << arista.costoDeViaje << std::endl;
            }
        }
        std::cout << std::endl;
    }
}
