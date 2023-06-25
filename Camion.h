#ifndef CAMION_H
#define CAMION_H

#include <iostream>
#include <string>
using namespace std;

class Camion {
private: 
    string nombreChofer = "";
    double litrosDeCombustible = 25000.0;
    string tipoCombustible = "";

public:
    Camion();  // Constructor

    void setNombreChofer(string nombre);
    string getNombreChofer();

    void setLitrosDeCombustible(double litros);
    double getLitrosCombustible();

    void setTipoCombustible(string tipo);
    string getTipoCombustible();
    
    
};

#endif