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
    cout << "Nodos en el grafo:" << endl;
    for (const auto& nodo : nodos) {
        cout << "Nodo " << nodo->estacion->getCodigo() << endl;
    }
}

void Grafo::mostrarAristas() {
    cout << "Aristas en el grafo:" << endl;
    for (const auto& nodo : nodos) {
        cout << "Nodo " << nodo->estacion->getCodigo() << ":" << endl;
        for (const auto& arista : aristas) {
            if (arista->origen->estacion->getCodigo() == nodo->estacion->getCodigo()) {
                cout << " (Nodo origen: " << arista->origen->estacion->getCodigo() << " -> Nodo destino: " << arista->destino->estacion->getCodigo() << " -> Costo de viaje: " << arista->costoDeViaje << " -> Horas de viaje: " << arista->horasViaje << ")" << std::endl;
            }
        }
        cout << endl;
    }
}

vector<Aristas*> Grafo::getAristas(Nodo* nodo) {
    vector<Aristas*> aristasDeNodo;
    for (const auto& arista : aristas) {
        if (arista->origen->estacion->getCodigo() == nodo->estacion->getCodigo()) {
            aristasDeNodo.push_back(arista);
        }
    }
    //cout << "Aristas del nodo " << nodo->estacion->getCodigo() << ": ";
    for (const auto& arista : aristasDeNodo) {
        //cout << arista->origen->estacion->getCodigo() << " -> " << arista->destino->estacion->getCodigo() << " ";
    }
    //cout << endl;

    return aristasDeNodo;
}

//Funciones para dijkstra

vector<Nodo*> Grafo::getAdyacencia(Nodo* nodo) {
    vector<Nodo*> adyacentes;
    
    for (const auto& arista : aristas) {
        if (arista->origen->estacion->getCodigo() == nodo->estacion->getCodigo()) {
            adyacentes.push_back(arista->destino);
        }
    }
    
    return adyacentes;
}
void Grafo::recorridoEnProfundidad(Nodo* origen) {
    unordered_set<Nodo*> visitados;
    stack<Nodo*> pila;
    pila.push(origen);

    while (!pila.empty()) {
        Nodo* actual = pila.top();
        pila.pop();

        if (visitados.find(actual) == visitados.end()) {
            visitados.insert(actual);
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

struct NodoDistanciaHoras {
    Nodo* nodo;
    double horas;
    bool operator<(const NodoDistanciaHoras& other) const {
        return horas > other.horas;
    }
};

struct NodoExtra {
    string nodoOrigen;
    string nodoDestino;
    int coste;
    bool operator<(const NodoExtra& other) const {
        return coste > other.coste;
    }
};

//Dijkstra por costo
unordered_map<string, int> Grafo::dijkstraPorCosto(Nodo* nodoInicial, string codigoDestino) {
    unordered_map<string, int> distancias;
    priority_queue<NodoDistancia> cola;
    priority_queue<NodoExtra> cola2;

    for (const auto& nodo : nodos) {
        distancias[nodo->estacion->getCodigo()] = numeric_limits<int>::max();
    }
    distancias[nodoInicial->estacion->getCodigo()] = 0;
    cola.push({nodoInicial, 0});
    while (!cola.empty()) {
        NodoDistancia actual = cola.top();
        cola.pop();
        if (actual.distancia > distancias[actual.nodo->estacion->getCodigo()]) {
            //cout<<"emtre al if"<<endl;
            continue;
        }
        for (const auto& arista : getAristas(actual.nodo)) {
            int nuevaDistancia = distancias[actual.nodo->estacion->getCodigo()] + arista->costoDeViaje;
            if (codigoDestino == arista->destino->estacion->getCodigo()){
            cout << "El costo para llegar de " << actual.nodo->estacion->getCodigo()<< " a " << arista->destino->estacion->getCodigo() << " es de " << nuevaDistancia <<endl;
            }
            if (nuevaDistancia < distancias[arista->destino->estacion->getCodigo()]) {
                distancias[arista->destino->estacion->getCodigo()] = nuevaDistancia;
                cola.push({arista->destino, nuevaDistancia});
                
            }
        }
    }
    return distancias;
}

void Grafo::mostrarDestinosDisponiblesPorCosto (string codigoOrigen, string codigoDestino){
    Nodo* origen = encontreNodo2(codigoOrigen);
    unordered_map<string, int> destinosDisponibles;
    bool encontroDestino = false;
    if (origen != nullptr){
        destinosDisponibles = dijkstraPorCosto(origen,codigoDestino);  
        for (auto destinos : destinosDisponibles){
            if (destinos.first == codigoDestino && destinos.second != 2147483647) {
                cout << "El costo minimo para llegar de " << origen -> estacion -> getCodigo() << " a " << codigoDestino << " es " << destinos.second << endl;
                encontroDestino = true;
            }
        }
    }
    if (encontroDestino == false) {
        cout << "No se encontro ningun destino desde la estacion origen: " << codigoOrigen << " a la estacion destino: " << codigoDestino << endl;
    }
}

//Dijkstra por tiempo
unordered_map<string, double> Grafo::dijkstraPorTiempo(Nodo* nodoInicial,string codigoDestino) {
    unordered_map<string, double> distancias;
    priority_queue<NodoDistanciaHoras> cola;
    //cout << "MAXIMO NUMERO EN DOBLE: " <<numeric_limits<double>::max() << endl;

    for (const auto& nodo : nodos) {
        distancias[nodo->estacion->getCodigo()] = numeric_limits<double>::max();
    }

    distancias[nodoInicial->estacion->getCodigo()] = 0.0;

    cola.push({nodoInicial, 0.0});

    while (!cola.empty()) {
        NodoDistanciaHoras actual = cola.top();
        cola.pop();
        if (actual.horas > distancias[actual.nodo->estacion->getCodigo()]) {
            //cout<<"emtre al if"<<endl;
            continue;
        }
        for (const auto& arista : getAristas(actual.nodo)) {
            double nuevoTiempoDeViaje = distancias[actual.nodo->estacion->getCodigo()] + arista->horasViaje;
            if (codigoDestino == arista->destino->estacion->getCodigo()){
            cout << "El costo en tiempo para llegar de " << actual.nodo->estacion->getCodigo()<< " a " << arista->destino->estacion->getCodigo() << " es de " << nuevoTiempoDeViaje <<endl;
            }
            // cout<<"nueva distancia: "<<nuevaDistancia<<endl;
            // cout<<"Distancia destino: "<<distancias[arista->destino->estacion->getCodigo()]<<"NODO"<<arista->destino->estacion->getCodigo()<<endl;
            if (nuevoTiempoDeViaje < distancias[arista->destino->estacion->getCodigo()]) {
                distancias[arista->destino->estacion->getCodigo()] = nuevoTiempoDeViaje;
                cola.push({arista->destino, nuevoTiempoDeViaje});
            }
        }
    }
    return distancias;
}

void Grafo::mostrarDestinosDisponiblesPorTiempo (string codigoOrigen, string codigoDestino){
    Nodo* origen = encontreNodo2(codigoOrigen);
    unordered_map<string, double> destinosDisponibles;
    bool encontroDestino = false;
    if (origen != nullptr){
        destinosDisponibles = dijkstraPorTiempo(origen,codigoDestino);    
        for (auto destinos : destinosDisponibles){
            if (destinos.first == codigoDestino && destinos.second != 2147483647) {
                cout << "El costo minimo por tiempo para llegar de " << origen -> estacion -> getCodigo() << " a " << codigoDestino << " es " << destinos.second << endl;
                encontroDestino = true;
            }
        }
    }
    if (encontroDestino == false) {
        cout << "No se encontro ningun destino desde la estacion origen: " << codigoOrigen << " a la estacion destino: " << codigoDestino << endl;
    }
}







