#ifndef ESTACION_H
#define ESTACION_H

#include <iostream>
#include <string>

class Estacion {
private:
    std::string codigo;
    std::string nombre;
    std::string ciudad;
    int cantSurtidores;
    double litrosSurtidor;
    std::string tipoCombustible;

public:
    // Constructores
    Estacion(); // Constructor por defecto

    Estacion(const std::string& codigo, const std::string& nombre, const std::string& ciudad,
             int cantSurtidores, double litrosSurtidor, const std::string& tipoCombustible);

    // Getters y setters
    std::string getCodigo() const;
    void setCodigo(const std::string& codigo);

    std::string getNombre() const;
    void setNombre(const std::string& nombre);

    std::string getCiudad() const;
    void setCiudad(const std::string& ciudad);

    int getCantSurtidores() const;
    void setCantSurtidores(int cantSurtidores);

    double getLitrosSurtidor() const;
    void setLitrosSurtidor(double litrosSurtidor);

    std::string getTipoCombustible() const;
    void setTipoCombustible(const std::string& tipoCombustible);

    void getDatosEstacion() const;
};

#endif  // ESTACION_H
