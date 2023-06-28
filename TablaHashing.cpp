#include <iostream>
#include <string>
#include <vector>
#include "Estacion.h"

using namespace std;
TablaHashing::TablaHashing() {
    int cantidadDeClaves; 
    int tamanioDeTabla;  
    vector<Estacion> tablaHashing(tamanioDeTabla); 
}

void TablaHashing::setCantidadClavesEstimadas(int cant) {
    cantidadDeClaves = cant;
}
int TablaHashing::getCantidadClavesEstimadas() {
    return cantidadDeClaves;
}

void TablaHashing::setTamanioTabla(int tamanioTabla) {
    tamanioDeTabla = tamanioTabla;
}
int TablaHashing::getTamanioTabla() {
    return tamanioDeTabla;
}
