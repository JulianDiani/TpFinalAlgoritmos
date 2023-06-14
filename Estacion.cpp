#include "Estacion.h"

using namespace std;
// Implementación de los constructores
Estacion::Estacion() {}

Estacion::Estacion(const string& codigo, const string& nombre, const string& ciudad,
                   int cantSurtidores, double litrosSurtidor, const string& tipoCombustible)
    : codigo(codigo), nombre(nombre), ciudad(ciudad), cantSurtidores(cantSurtidores),
      litrosSurtidor(litrosSurtidor), tipoCombustible(tipoCombustible) {
}

// Implementación de los getters y setters
string Estacion::getCodigo() const {
    return codigo;
}

void Estacion::setCodigo(const string& codigo) {
    this->codigo = codigo;
}

string Estacion::getNombre() const {
    return nombre;
}

void Estacion::setNombre(const string& nombre) {
    this->nombre = nombre;
}

string Estacion::getCiudad() const {
    return ciudad;
}

void Estacion::setCiudad(const string& ciudad) {
    this->ciudad = ciudad;
}

int Estacion::getCantSurtidores() const {
    return cantSurtidores;
}

void Estacion::setCantSurtidores(int cantSurtidores) {
    this->cantSurtidores = cantSurtidores;
}

double Estacion::getLitrosSurtidor() const {
    return litrosSurtidor;
}

void Estacion::setLitrosSurtidor(double litrosSurtidor) {
    this->litrosSurtidor = litrosSurtidor;
}

string Estacion::getTipoCombustible() const {
    return tipoCombustible;
}

void Estacion::setTipoCombustible(const string& tipoCombustible) {
    this->tipoCombustible = tipoCombustible;
}

void Estacion::getDatosEstacion() const {
    cout << "Codigo de la estacion: " << codigo << endl
              << "Nombre: " << nombre << endl
              << "Ciudad: " << ciudad << endl
              << "Cantidad de surtidores: " << cantSurtidores << endl
              << "Litros por surtidor: " << litrosSurtidor << endl
              << "Tipo de combustible: " << tipoCombustible << endl;
}
