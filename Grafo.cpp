#include <iostream>
#include <vector>

using namespace std;
 // namespace std;

// Clase para representar un nodo en el grafo
class Nodo {
public:
    string codigoOrigen;
    // Constructor de la clase Nodo
    Nodo(string codigoOrigen) : codigoOrigen(codigoOrigen) {}
};

// Clase para representar una arista en el grafo
class Aristas {
public:
    Nodo origen;
    Nodo destino;
    int costoDeViaje;
    // Constructor de la clase Aristas
    Aristas(const Nodo& src, const Nodo& dest, int w) : origen(src), destino(dest), costoDeViaje(w) {}
};

// Clase para representar un grafo
class Grafo {
private:
    std::vector<Nodo> nodes; // Vector de nodos
    std::vector<Aristas> edges; // Vector de aristas

public:
    // Función para agregar un nodo al grafo
    void agregarNodo(const Nodo& nodo) {
        nodes.push_back(nodo);
    }

    // Función para agregar una arista al grafo
    void agregarArista(const Nodo& origen, const Nodo& destino, int costoDeViaje) {
        Aristas edge(origen, destino, costoDeViaje);
        edges.push_back(edge);
    }

    // Función para mostrar los nodos del grafo
    void mostrarNodos() {
        std::cout << "Nodos en el grafo:" << std::endl;
        for (const auto& nodo : nodes) {
            std::cout << "Nodo " << nodo.codigoOrigen << std::endl;
        }
    }

    // Función para mostrar las aristas del grafo
    // Función para mostrar las aristas del grafo
void mostrarAristas() {
    std::cout << "Aristas en el grafo:" << std::endl;
    for (const auto& nodo : nodes) {
        std::cout << "Nodo " << nodo.codigoOrigen << ":"<<endl;
        for (const auto& edge : edges) {
            if (edge.origen.codigoOrigen == nodo.codigoOrigen) {
                std::cout << " (" <<"Nodo origen: " <<edge.origen.codigoOrigen << " -> " <<"Nodo destino: " <<edge.destino.codigoOrigen << "), Costo de viaje: " << edge.costoDeViaje<<endl;
            }
        }
        std::cout << std::endl;
    }
}

};

int main() {
    // Crear nodos
    Nodo node0("cerp");
    Nodo node1("uno");
    Nodo node2("dos");

    // Crear grafo
    Grafo grafo;

    // Agregar nodos al grafo
    grafo.agregarNodo(node0);
    grafo.agregarNodo(node1);
    grafo.agregarNodo(node2);

    // Agregar aristas al grafo
    grafo.agregarArista(node0, node1, 10);
    grafo.agregarArista(node1, node2, 5);
    grafo.agregarArista(node0,node2,4);
    // Mostrar los nodos y aristas del grafo
    grafo.mostrarNodos();
    grafo.mostrarAristas();

    return 0;
}
