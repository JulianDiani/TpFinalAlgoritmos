#ifndef TABLAHASHING_H
#define TABLAHASHING_H

#include <iostream>
#include <string>
#include <vector>
#include "Estacion.h"

using namespace std;

class TablaHashing {
private: 
    int cantidadDeClaves = 100; // Tamaño de registros estimados
    int tamanioDeTabla = 127;  // Tamaño de tabla
    vector<Estacion> tablaHashing; 

public:
    TablaHashing();  // Constructor

    void setCantidadClavesEstimadas(int cant);
    int getCantidadClavesEstimadas();

    void setTamanioTabla(int tamanioTabla);
    int getTamanioTabla();
    
};

#endif