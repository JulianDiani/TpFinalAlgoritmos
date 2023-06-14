#include "Viaje.h"

using namespace std;
// Implementación de los constructores
Viaje::Viaje() {}

Viaje::Viaje(const std::string &codigoPartida, const std::string &codigoDestino, const double costoViaje, const double horasViaje)
{
}

// Implementación de los getters y setters
string Viaje::getCodigoPartida() const {
    return codigoPartida;
}

void Viaje::setCodigoPartida(const string& codigoPartida) {
    this->codigoPartida = codigoPartida;
}

string Viaje::getCodigoDestino() const {
    return codigoDestino;
}

void Viaje::setCostoViaje(double costoViaje) {
    this->costoViaje = costoViaje;
}

double Viaje::getHorasViaje() const {
    return horasViaje;
}

void Viaje::setHorasViaje(const double horasViaje) {
    this->horasViaje = horasViaje;
}