#ifndef VIAJE_H
#define VIAJE_H
#include <string>
using namespace std;
class Viaje {
private:
    string codigoPartida;
    string codigoDestino;
    double costoViaje;
    double horasViaje;
public:
Viaje(); // Constructor por defecto

    Viaje(const std::string codigoPartida, const std::string codigoDestino, const int costoViaje,
             const double horasViaje);

    // Getters y setters
    std::string getCodigoPartida() const;
    void setCodigoPartida(const std::string codigo);

    std::string getCodigoDestino() const;
    void setCodigoDestino(const std::string codigoDestino);

    int getCostoViaje() const;
    void setCostoViaje(const int costoViaje);
    double getHorasViaje() const;
    void setHorasViaje(const double horasViaje);

    
}; 

#endif 