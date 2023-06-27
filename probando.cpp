#include <iostream>
#include <unordered_set>
#include <queue>
#include <vector>
#include <string>

class Nodo {
public:
    std::string codigo;

    Nodo(std::string codigo) : codigo(codigo) {}
};

class Arista {
public:
    Nodo* origen;
    Nodo* destino;

    Arista(Nodo* origen, Nodo* destino) : origen(origen), destino(destino) {}
};

class Grafo {
private:
    std::vector<Nodo*> nodos;
    std::vector<Arista*> aristas;

public:
    void agregarNodo(Nodo* nodo) {
        nodos.push_back(nodo);
    }

    void agregarArista(Arista* arista) {
        aristas.push_back(arista);
    }

    std::vector<Nodo*> getNodos() {
        return nodos;
    }

    std::vector<Arista*> getAristas() {
        return aristas;
    }
};

bool hayCaminoDFS(Grafo& grafo, Nodo* nodoActual, Nodo* nodoDestino, std::unordered_set<Nodo*> visitados) {
    if (nodoActual == nodoDestino) {
        return true;
    }

    visitados.insert(nodoActual);

    std::vector<Arista*> aristas = grafo.getAristas();
    for (Arista* arista : aristas) {
        if (arista->origen == nodoActual && visitados.find(arista->destino) == visitados.end()) {
            if (hayCaminoDFS(grafo, arista->destino, nodoDestino, visitados)) {
                return true;
            }
        }
    }

    return false;
}

bool hayCaminoBFS(Grafo& grafo, Nodo* nodoOrigen, Nodo* nodoDestino) {
    std::unordered_set<Nodo*> visitados;
    std::queue<Nodo*> cola;

    cola.push(nodoOrigen);
    visitados.insert(nodoOrigen);

    while (!cola.empty()) {
        Nodo* nodoActual = cola.front();
        cola.pop();

        if (nodoActual == nodoDestino) {
            return true;
        }

        std::vector<Arista*> aristas = grafo.getAristas();
        for (Arista* arista : aristas) {
            if (arista->origen == nodoActual && visitados.find(arista->destino) == visitados.end()) {
                cola.push(arista->destino);
                visitados.insert(arista->destino);
            }
        }
    }

    return false;
}

int main() {
    Grafo grafo;

    Nodo* nodoA = new Nodo("A");
    Nodo* nodoB = new Nodo("B");
    Nodo* nodoC = new Nodo("C");

    grafo.agregarNodo(nodoA);
    grafo.agregarNodo(nodoB);
    grafo.agregarNodo(nodoC);

    grafo.agregarArista(new Arista(nodoA, nodoB));
    grafo.agregarArista(new Arista(nodoB, nodoC));

    Nodo* nodoOrigen = nodoA;
    Nodo* nodoDestino = nodoC;

    if (hayCaminoDFS(grafo, nodoOrigen, nodoDestino, std::unordered_set<Nodo*>())) {
        std::cout << "Hay un camino entre el nodo origen y el nodo destino utilizando DFS." << std::endl;
    } else {
        std::cout << "No hay un camino entre el nodo origen y el nodo destino utilizando DFS." << std::endl;
    }

    if (hayCaminoBFS(grafo, nodoOrigen, nodoDestino)) {
        std::cout << "Hay un camino entre el nodo origen y el nodo destino utilizando BFS." << std::endl;
    } else {
        std::cout << "No hay un camino entre el nodo origen y el nodo destino utilizando BFS." << std::endl;
    }

    // Liberar memoria de los nodos y aristas
    for (Nodo* nodo : grafo.getNodos()) {
        delete nodo;
    }

    for (Arista* arista : grafo.getAristas()) {
        delete arista;
    }

    return 0;
}
