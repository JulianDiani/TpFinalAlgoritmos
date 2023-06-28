#include "Grafo.h"
#include<unordered_set>
#include <stack>
#include <queue>
#include <unordered_map>
#include <limits>

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
vector<Aristas*> Grafo::getAristas(Nodo* nodo) {
    vector<Aristas*> aristasDeNodo;
    for (const auto& arista : aristas) {
        if (arista->origen->estacion->getCodigo() == nodo->estacion->getCodigo()) {
            aristasDeNodo.push_back(arista);
        }
    }

    cout << "Aristas del nodo " << nodo->estacion->getCodigo() << ": ";
    for (const auto& arista : aristasDeNodo) {
        cout << arista->origen->estacion->getCodigo() << " -> " << arista->destino->estacion->getCodigo() << " ";
    }
    cout << endl;

    return aristasDeNodo;
}
void Grafo::recorridoEnProfundidad(Nodo* origen) {
    std::unordered_set<Nodo*> visitados;
    std::stack<Nodo*> pila;
    pila.push(origen);

    while (!pila.empty()) {
        Nodo* actual = pila.top();
        pila.pop();

        if (visitados.find(actual) == visitados.end()) {
            visitados.insert(actual);
            cout << "Visited node: " << actual->estacion->getCodigo() << endl;

            vector<Nodo*> adyacentes = getAdyacencia(actual);
            for (Nodo* adyacente : adyacentes) {
                pila.push(adyacente);
            }
        }
    }
}


struct NodoDistancia {
    Nodo* nodo;
    int distancia;

    bool operator<(const NodoDistancia& other) const {
        return distancia > other.distancia;
    }
};

std::unordered_map<string, int> Grafo::dijkstra(Nodo* nodoInicial) {
    std::unordered_map<string, int> distancias;
    for (const auto& nodo : nodos) {
        distancias[nodo->estacion->getCodigo()] = std::numeric_limits<int>::max();
    }
    distancias[nodoInicial->estacion->getCodigo()] = 0;
    for(auto distancia:distancias){
        cout<<"CLAVES"<<distancia.first<<endl;
    }

    std::priority_queue<NodoDistancia> cola;
    cola.push({nodoInicial, 0});

    while (!cola.empty()) {
        NodoDistancia actual = cola.top();
        cola.pop();

        if (actual.distancia > distancias[actual.nodo->estacion->getCodigo()]) {
            cout<<"emtre al if"<<endl;
            continue;
        }

        for (const auto& arista : getAristas(actual.nodo)) {
            int nuevaDistancia = distancias[actual.nodo->estacion->getCodigo()] + arista->costoDeViaje;
            cout<<"nueva distancia: "<<nuevaDistancia<<endl;
            cout<<"Distancia destino: "<<distancias[arista->destino->estacion->getCodigo()]<<"NODO"<<arista->destino->estacion->getCodigo()<<endl;
            if (nuevaDistancia < distancias[arista->destino->estacion->getCodigo()]) {
                cout << "Updating distance of node " << arista->destino->estacion->getCodigo() << " from " << distancias[arista->destino->estacion->getCodigo()] << " to " << nuevaDistancia << endl;
                distancias[arista->destino->estacion->getCodigo()] = nuevaDistancia;
                cola.push({arista->destino, nuevaDistancia});
            }
        }
    }

    return distancias;
}










