#include "Camion.h"
#include <string>
using namespace std;
Camion::Camion() {
    string nombreChofer;
    double litrosDeCombustible;
    string tipoCombustible;
}

void Camion::setNombreChofer(string nombre) {
    nombreChofer = nombre;
}
string Camion::getNombreChofer() {
    return nombreChofer;
}

void Camion::setTipoCombustible(string tipo) {
    tipoCombustible = tipo;
}
string Camion::getTipoCombustible() {
    return tipoCombustible;
}

void Camion::setLitrosDeCombustible(double litros){
    litrosDeCombustible = litros;
}
double Camion::getLitrosCombustible(){
    return litrosDeCombustible;
}
