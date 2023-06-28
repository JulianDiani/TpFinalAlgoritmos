#ifndef ESTACION_H
#define ESTACION_H

#include <iostream>
#include <string>
using namespace std;

class Estacion {
private:
    string codigo;
    string nombre;
    string ciudad;
    int cantSurtidores;
    double litrosSurtidor;
    string tipoCombustible;

public:
    // Constructores
    Estacion(); // Constructor por defecto

    Estacion(const string codigo, const string nombre, const string ciudad,
             int cantSurtidores, double litrosSurtidor, const string tipoCombustible);

    // Getters y setters
    string getCodigo() const;
    void setCodigo(const string& codigo);

    string getNombre() const;
    void setNombre(const string& nombre);

    string getCiudad() const;
    void setCiudad(const string& ciudad);

    int getCantSurtidores() const;
    void setCantSurtidores(int cantSurtidores);

    double getLitrosSurtidor() const;
    void setLitrosSurtidor(double litrosSurtidor);

    string getTipoCombustible() const;
    void setTipoCombustible(const string& tipoCombustible);

    void getDatosEstacion() const;
};

#endif  // ESTACION_H
