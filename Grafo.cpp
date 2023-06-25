#include "Grafo.h"

using namespace std;

void Grafo::agregarNodo(Estacion* estacion) {
    Nodo* nodo = new Nodo(estacion);
    nodos.push_back(nodo);
}



void Grafo::agregarArista(Nodo* origen, Nodo* destino, int costoDeViaje, double horasViaje) {
    Aristas* arista = new Aristas(origen, destino, costoDeViaje, horasViaje);
    aristas.push_back(arista);
}
bool Grafo::encontreNodo(const string& codigo) {
    for (const auto& nodoPtr : nodos) {
        if (nodoPtr->estacion->getCodigo() == codigo) {
            return true;
        }
    }
    return false;
}




Nodo* Grafo::encontreNodo2(string codigo){
    Nodo* salida=nullptr;
    for (const auto& nodo:nodos){
        if(nodo->estacion->getCodigo()==codigo){
            salida=nodo;
        }
    }
    return salida;
}


void Grafo::mostrarNodos() {
    std::cout << "Nodos en el grafo:" << std::endl;
    for (const auto& nodo : nodos) {
        std::cout << "Nodo " << nodo->estacion->getCodigo() << std::endl;
    }
}


void Grafo::mostrarAristas() {
    std::cout << "Aristas en el grafo:" << std::endl;
    for (const auto& nodo : nodos) {
        std::cout << "Nodo " << nodo->estacion->getCodigo() << ":" << std::endl;
        for (const auto& arista : aristas) {
            if (arista->origen->estacion->getCodigo() == nodo->estacion->getCodigo()) {
                std::cout << " (Nodo origen: " << arista->origen->estacion->getCodigo() << " -> Nodo destino: " << arista->destino->estacion->getCodigo() << " -> Costo de viaje: " << arista->costoDeViaje << " -> Horas de viaje: " << arista->horasViaje << ")" << std::endl;
            }
        }
        std::cout << std::endl;
    }
}

vector<Nodo*> Grafo::getAdyacencia(Nodo* nodo) {
    vector<Nodo*> adyacentes;
    
    for (const auto& arista : aristas) {
        if (arista->origen->estacion->getCodigo() == nodo->estacion->getCodigo()) {
            adyacentes.push_back(arista->destino);
        }
    }
    
    return adyacentes;
}

