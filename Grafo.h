#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <iostream>
#include "Nodo.h"
#include "Arista.h"
#include<unordered_set>

using namespace std;
class Grafo {
private:
    vector<Nodo*> nodos; // Vector de punteros a Nodo
    vector<Aristas*> aristas;// Vector de aristas

public:

    // Función para agregar un nodo al grafo
    void agregarNodo(Estacion* estacion);

    bool encontreNodo(const string& codigo);
    Nodo* encontreNodo2( string codigo);

    // Función para agregar una arista al grafo
    void agregarArista(Aristas* arista);

    // Función para mostrar los nodos del grafo
    void mostrarNodos();

    // Función para mostrar las aristas del grafo
    void mostrarAristas();
    
    // Función para obtener los nodos adyacentes a un nodo dado
    vector<Nodo*> getAdyacencia(Nodo* nodo);
    int getCostoEntre_Y_(Nodo* nodo1,Nodo* nodo2);
    vector<Aristas*> getAristas(Nodo* nodo);
    double getHorasEntre_Y_(Nodo* nodo1,Nodo* nodo2);
    vector<Aristas*>getAristas2();
    bool hayCaminoDFS(Nodo* nodoActual, Nodo* nodoDestino, std::unordered_set<Nodo*>& visitados);
};

#endif
