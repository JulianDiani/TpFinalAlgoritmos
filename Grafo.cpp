#include "Grafo.h"
#include<unordered_set>

using namespace std;

void Grafo::agregarNodo(Estacion* estacion) {
    Nodo* nodo = new Nodo(estacion);
    nodos.push_back(nodo);
}



 void Grafo::agregarArista(Aristas* arista) {
        aristas.push_back(arista);
    }
// void Grafo::agregarArista(Nodo* origen, Nodo* destino, int costoDeViaje, double horasViaje) {
//     Aristas* arista = new Aristas(origen, destino, costoDeViaje, horasViaje);
//     aristas.push_back(arista);
// }
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
vector<Aristas*> Grafo::getAristas(Nodo* nodo){  //Devuelve un vector con todas las aristas del nodo.
    vector<Aristas*> aristasDeNodo;
    for (const auto& arista : aristas) {
        if (arista->origen->estacion->getCodigo() == nodo->estacion->getCodigo()) {
            aristasDeNodo.push_back(arista);
        }
    }
    
    return aristasDeNodo;
}


int Grafo::getCostoEntre_Y_(Nodo* nodo1,Nodo* nodo2){
    for(auto arista: aristas){
        if(arista->origen->estacion->getCodigo()==nodo1->estacion->getCodigo() && arista->destino->estacion->getCodigo()==nodo2->estacion->getCodigo()){
            return arista->costoDeViaje;
        }    
    }
    return 0;
}
double Grafo::getHorasEntre_Y_(Nodo* nodo1,Nodo* nodo2){
   for(auto arista: aristas){
        if(arista->origen->estacion->getCodigo()==nodo1->estacion->getCodigo() && arista->destino->estacion->getCodigo()==nodo2->estacion->getCodigo()){
            return arista->horasViaje;
        }    
    }
    return 0;
}
vector<Aristas*>Grafo:: getAristas2() {
        return aristas;
    }
bool Grafo::hayCaminoDFS(Nodo* nodoActual, Nodo* nodoDestino, std::unordered_set<Nodo*>& visitados) {
    if (nodoActual == nodoDestino) {
        return true;
    }

    visitados.insert(nodoActual);

    vector<Nodo*> adyacentes = getAdyacencia(nodoActual);
    for (Nodo* adyacente : adyacentes) {
        if (visitados.find(adyacente) == visitados.end()) {
            if (hayCaminoDFS(adyacente, nodoDestino, visitados)) {
                return true;
            }
        }
    }

    return false;
}
#include <queue>
#include <unordered_map>
#include <limits>

struct NodoDistancia {
    Nodo* nodo;
    int distancia;

    bool operator<(const NodoDistancia& other) const {
        return distancia > other.distancia;
    }
};

std::unordered_map<Nodo*, int> Grafo::dijkstra(Nodo* nodoInicial) {
    std::unordered_map<Nodo*, int> distancias;
    for (const auto& nodo : nodos) {
        distancias[nodo] = std::numeric_limits<int>::max();
    }
    distancias[nodoInicial] = 0;

    std::priority_queue<NodoDistancia> cola;
    cola.push({nodoInicial, 0});

    while (!cola.empty()) {
        NodoDistancia actual = cola.top();
        cola.pop();

        if (actual.distancia > distancias[actual.nodo]) {
            continue;
        }

        for (const auto& arista : getAristas(actual.nodo)) {
            int nuevaDistancia = distancias[actual.nodo] + arista->costoDeViaje;
            if (nuevaDistancia < distancias[arista->destino]) {
                distancias[arista->destino] = nuevaDistancia;
                cola.push({arista->destino, nuevaDistancia});
            }
        }
    }

    return distancias;
}





