#include <iostream>
#include <unordered_set>
#include <queue>

struct Estacion {
    int id;
    // Añade aquí cualquier otra información relacionada con una estación
};

struct Nodo {
    Estacion* estacion;
    std::unordered_set<Nodo*> adyacentes;
};

using Grafo = std::unordered_set<Nodo*>;

bool hayCaminoDFS(Grafo& grafo, Nodo* nodoActual, Nodo* nodoDestino, std::unordered_set<Nodo*>& visitados) {
    if (nodoActual == nodoDestino) {
        return true;
    }

    visitados.insert(nodoActual);

    for (Nodo* adyacente : nodoActual->adyacentes) {
        if (visitados.find(adyacente) == visitados.end()) {
            if (hayCaminoDFS(grafo, adyacente, nodoDestino, visitados)) {
                return true;
            }
        }
    }

    return false;
}

bool hayCaminoBFS(Grafo& grafo, Nodo* nodoOrigen, Nodo* nodoDestino) {
    std::queue<Nodo*> cola;
    std::unordered_set<Nodo*> visitados;

    cola.push(nodoOrigen);
    visitados.insert(nodoOrigen);

    while (!cola.empty()) {
        Nodo* nodoActual = cola.front();
        cola.pop();

        if (nodoActual == nodoDestino) {
            return true;
        }

        for (Nodo* adyacente : nodoActual->adyacentes) {
            if (visitados.find(adyacente) == visitados.end()) {
                cola.push(adyacente);
                visitados.insert(adyacente);
            }
        }
    }

    return false;
}

int main() {
    // Crea las estaciones
    Estacion* estacionA = new Estacion{1};
    Estacion* estacionB = new Estacion{2};
    Estacion* estacionC = new Estacion{3};
    Estacion* estacionD = new Estacion{4};

    // Crea los nodos
    Nodo* nodoA = new Nodo{estacionA};
    Nodo* nodoB = new Nodo{estacionB};
    Nodo* nodoC = new Nodo{estacionC};
    Nodo* nodoD = new Nodo{estacionD};

    // Crea las aristas
    nodoA->adyacentes.insert(nodoB);
    nodoA->adyacentes.insert(nodoD);
    //nodoC->adyacentes.insert(nodoD);
    nodoD->adyacentes.insert(nodoA);

    // Crea el grafo
    Grafo grafo;
    grafo.insert(nodoA);
    grafo.insert(nodoB);
    grafo.insert(nodoC);
    grafo.insert(nodoD);

    // Prueba la función de búsqueda DFS
    std::unordered_set<Nodo*> visitadosDFS;
    bool resultadoDFS = hayCaminoDFS(grafo, nodoA, nodoD, visitadosDFS);

    if (resultadoDFS) {
        std::cout << "Existe un camino entre el nodo A y el nodo D (DFS)" << std::endl;
    } else {
        std::cout << "No existe un camino entre el nodo A y el nodo D (DFS)" << std::endl;
    }

    // Prueba la función de búsqueda BFS
    bool resultadoBFS = hayCaminoBFS(grafo, nodoA, nodoD);

    if (resultadoBFS) {
        std::cout << "Existe un camino entre el nodo A y el nodo D (BFS)" << std::endl;
    } else {
        std::cout << "No existe un camino entre el nodo A y el nodo D (BFS)" << std::endl;
    }

    // Libera la memoria
    delete estacionA;
    delete estacionB;
    delete estacionC;
    delete estacionD;
    delete nodoA;
    delete nodoB;
    delete nodoC;
    delete nodoD;

    return 0;
}
