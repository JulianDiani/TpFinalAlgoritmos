#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

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
    Estacion() {} // Constructor por defecto

    Estacion(const string& codigo, const string& nombre, const string& ciudad,
               int cantSurtidores, double litrosSurtidor, const string& tipoCombustible)
        : codigo(codigo), nombre(nombre), ciudad(ciudad), cantSurtidores(cantSurtidores),
          litrosSurtidor(litrosSurtidor), tipoCombustible(tipoCombustible) {
    }

    // Getters y setters
    string getCodigo() const {
        return codigo;
    }

    void setCodigo(const string& codigo) {
        this->codigo = codigo;
    }

    string getNombre() const {
        return nombre;
    }

    void setNombre(const string& nombre) {
        this->nombre = nombre;
    }

    string getCiudad() const {
        return ciudad;
    }

    void setCiudad(const string& ciudad) {
        this->ciudad = ciudad;
    }

    int getCantSurtidores() const {
        return cantSurtidores;
    }

    void setCantSurtidores(int cantSurtidores) {
        this->cantSurtidores = cantSurtidores;
    }

    double getLitrosSurtidor() const {
        return litrosSurtidor;
    }

    void setLitrosSurtidor(double litrosSurtidor) {
        this->litrosSurtidor = litrosSurtidor;
    }

    string getTipoCombustible() const {
        return tipoCombustible;
    }

    void setTipoCombustible(const string& tipoCombustible) {
        this->tipoCombustible = tipoCombustible;
    }
    void getDatosEstacion() const {
        cout<<"Codigo de la estacion: "<< codigo<<endl<<"Nombre: "<< nombre<<endl<<"Ciudad: "<< ciudad<<endl<<
    "Cantidad de surtidores: "<< cantSurtidores<<endl<< "Litros por surtidor: "<<litrosSurtidor<<endl<<"Tipo de combustible: "<<tipoCombustible<<endl;
    }
};