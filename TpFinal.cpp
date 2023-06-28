#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Estacion.h"
#include "Grafo.h"
#include "Arista.h"
#include "Nodo.h"
#include "Camion.h"

using namespace std;

int cantidadDeClaves = 100; // Tamaño de registros estimados
int tamanioDeTabla = 127;  // Tamaño de tabla
string archivoEstaciones = "estaciones.txt"; // Archivo incial de estaciones
string archivoViajes= "viajes.txt";
vector<Estacion> tablaHashing(tamanioDeTabla); // Tabla de hashing

// Funciones auxiliares
bool verificarTipoComb (string tipo) {
    return tipo == "SUP" || tipo == "INF" || tipo == "NIT";
}

bool verificarCodigo(string codigo){
    return codigo.size()==6;
}

bool verificarSalir(string dato) {
    return dato != "salir";
}

bool noEstaOcupado (int posicion){
    return tablaHashing[posicion].getCodigo().empty();
}

char deseaContinuar() {
    char dato;
    cout << "Si desea continuar ingrese cualquier dato." << endl;
    cout << "Si desea salir ingrese n/N." << endl;
    cout << "Respuesta: ";
    cin >> dato;
    cout << endl;
    if (dato == 'n' || dato == 'N'){
        return 'n';
    }
    else{
        return '0';
    }
}

// Funciones de hashing
// Hashing Modulo
int funcionModulo(int key, int tamanio) {
    return key % tamanio;
}

// Hashing Folding ultimos 3 + Divicion
// Devuele posicion

int funcionDeHashing(string codigo, int tamanio) {
    int salida = 0, posicion;
    for (int i = codigo.size() - 3; i < codigo.size(); i++)
    {
        salida += codigo[i];
        // cout <<"Salida= "<< salida <<"Codigo= "<< codigo[i] << endl;
    }
    posicion = funcionModulo(salida, tamanio);
    return posicion;
}

// Colision Quadratic probing
// Si da -1 no encontro posicion
// Tratamiento colicion para insertar
int tratarColisionInsertar(int posicion, int tamanio) { //// REVISAR SI ANDA BIEN X LAS DUDAS
    int posicionAux, salida = -1;
    for (int i = 1; i < tamanio; i++) {
        posicionAux = posicion + (i * i);
        if (noEstaOcupado(posicionAux)|| tablaHashing[posicionAux].getCodigo()=="000000") {
            salida = posicionAux;
            break;
        }
    }
    return salida;
}

// Tratamiento colicion para buscar
int tratarColisionBuscar(int posicion, int tamanio, string codigo) {
    int i = 1, salida = -1;
    int posicionAux = posicion + i;
    Estacion datoAComparar; 
    while (!noEstaOcupado(posicionAux) && i < tamanio) {           
        datoAComparar = tablaHashing[posicionAux];
        //cout << datoAComparar.codigo << endl;
        if (datoAComparar.getCodigo() == codigo) {
            salida = posicionAux;
            break;
        }
        i += 1;
        posicionAux = posicion + i * i;
    }
    return salida;
}

// Funciones Generales
// Insercion
void insertarEstacion(Estacion estacion, int tamanio) {
    int posicionColision, posicionInicial = funcionDeHashing(estacion.getCodigo(), tamanio);
    //cout << "Pos ini" << posicionInicial << endl;
    if (noEstaOcupado(posicionInicial) || tablaHashing[posicionInicial].getCodigo()=="000000") {    
        tablaHashing[posicionInicial] = estacion;
        //cout << "Soy la estacion: " << estacion.nombre << " Entre en pos Inicial: " << "Pos: " << posicionInicial << endl;
    }
    else {
        posicionColision = tratarColisionInsertar(posicionInicial, tamanio);
        if (posicionColision != (-1)) {            
            tablaHashing[posicionColision] = estacion;
            //cout << "Soy la estacion: " << estacion.nombre << " Entre en pos Colision: " << "PosCos: " << posicionColision << endl;
        }
        else {
            cout << "No se pudo insertar la estacion en ningun lugar." << endl;
        }
    }
    //cout << "Estacion registrada correctamente." << endl;
}

// Dar de alta con hashing
void darDeAltaEstacion() {
    Estacion estacionNueva;
    string opc,codigo,nombre,ciudad,tipoCombustible;
    int cantSurtidores,litrosPorSurtidor;

    while (opc != "salir"){
        cout<<"Escribi salir para terminar. "<<endl;
        cout << "Ingrese el CODIGO de 6 digitos de la estacion nueva: " << endl;
        cin >> codigo;
        while (!verificarCodigo(codigo) && verificarSalir(codigo)) {
            cout << "El CODIGO debe ser de 6 digitos ej: ABC123, vuelve a intentarlo: " << endl;            
            cin >> codigo;
        }
        if (!verificarSalir(codigo)){
            break;
        }
        estacionNueva.setCodigo(codigo);
        cout << "Ingrese el nombre: " << endl;
        cin >> nombre;
        if (!verificarSalir(nombre)){
            break;
        }
        estacionNueva.setNombre(nombre);
        cout << "Ingrese la ciudad: " << endl;
        cin >> ciudad;
        if (!verificarSalir(ciudad)){
            break;
        }
        estacionNueva.setCiudad(ciudad);
        cout << "Ingrese el tipo de combustible: " << endl;
        cin >> tipoCombustible;
        while (!verificarTipoComb(tipoCombustible) && verificarSalir(tipoCombustible)) { 
            cout << "Los tipos de combustible validos son SUP-INF-NIT: " << endl;
            cin >> tipoCombustible;
        }
        if (!verificarSalir(tipoCombustible)){
            break;
        }
        estacionNueva.setTipoCombustible(tipoCombustible);

        cout << "Ingrese la cantidad de surtidores: " << endl;
        cin >> cantSurtidores;
        estacionNueva.setCantSurtidores(cantSurtidores);
        cout << "Ingrese los litros que tiene cada surtidor: " << endl;
        cin >> litrosPorSurtidor;
        estacionNueva.setLitrosSurtidor(litrosPorSurtidor);
        cout << "Todos los datos fueron ingresados correctamente" << endl;
        
        insertarEstacion(estacionNueva, tamanioDeTabla);
        opc = "salir";
    }
}

// Buscar estacion con hashing
void buscarEstacion(string codigo, int tamanio){
    int posicionColision, posicionInicial = funcionDeHashing(codigo, tamanio);
    Estacion estacionAux = tablaHashing[posicionInicial];
     
    if (!noEstaOcupado(posicionInicial) && estacionAux.getCodigo() == codigo) {
        cout <<"La estacion encontrada es: "<<endl;   
        estacionAux.getDatosEstacion();
    }
    else if(!noEstaOcupado(posicionInicial)) {
        //cout <<"Entre al else if: "<<endl;
        posicionColision = tratarColisionBuscar(posicionInicial, tamanio, codigo);

        if (posicionColision != (-1)) {
            //cout <<"Entre al if: "<<endl;
            estacionAux = tablaHashing[posicionColision];
            cout <<"La estacion encontrada es: "<<endl;            
            estacionAux.getDatosEstacion();
        }
        else {
            cout << "No se pudo encontrar ninguna estacion con ese codigo" << endl;
        }
    }else {
        cout << "No se pudo encontrar ninguna estacion con ese codigo" << endl;
    }
}

// Buscar estacion con hashing devuelve estacion validar contra empty
Estacion* retornarEstacion(string codigo, int tamanio) {
    int posicionColision, posicionInicial = funcionDeHashing(codigo, tamanio);
    
    Estacion* estacionAux = nullptr;
    
    if (!noEstaOcupado(posicionInicial)) {
        estacionAux = &tablaHashing[posicionInicial];
        if (estacionAux->getCodigo() != codigo) {
            posicionColision = tratarColisionBuscar(posicionInicial, tamanio, codigo);
            if (posicionColision != -1) {
                estacionAux = &tablaHashing[posicionColision];
            } else {
                estacionAux = nullptr;
            }
        }
    }   
    return estacionAux;
}

void buscarEstacionPorCodigo() {  
    string codigo;
    cout<<"Ingrese el codigo de la estacion a buscar: "<<endl;
    cin>>codigo;
    while(!verificarCodigo(codigo) && verificarSalir(codigo)) { 
        cout<<"El CODIGO debe ser de 6 digitos ej: ABC123, vuelve a intentarlo: "<<endl;
        cout<<"Escribi salir para terminar. "<<endl;
        cin>>codigo;
    }
    if (verificarSalir(codigo)){
        buscarEstacion(codigo, tamanioDeTabla);
    }
}

// Eliminar estacion con hashing
void eliminarEstacion(string codigo, int tamanio) {
    int posicionColision, posicionInicial = funcionDeHashing(codigo, tamanio);
    Estacion estacionAux = tablaHashing[posicionInicial];
    Estacion estacionEliminada("000000", "Estacion eliminada", "Estacion eliminada", 0, 0.0, "Estacion eliminada");
    //cout << "Estacion elim: "<< estacionEliminada.codigo << endl;
    if (!noEstaOcupado(posicionInicial) && estacionAux.getCodigo() == codigo) {            
        cout <<"La estacion codigo: "<< estacionAux.getCodigo() << "\nNombre: "<< estacionAux.getNombre() << "\nFue eliminada."<<endl;
        tablaHashing[posicionInicial] = estacionEliminada;
        //cout <<"Entre al if "<< endl;
    }
    else if(!noEstaOcupado(posicionInicial)) {
        posicionColision = tratarColisionBuscar(posicionInicial, tamanio, codigo);
        //cout <<"Entre al else if "<< endl;
                
        if (posicionColision != (-1)) {
            estacionAux = tablaHashing[posicionColision];
            cout <<"La estacion codigo: "<< estacionAux.getCodigo()<< "\nNombre: "<< estacionAux.getNombre() << "\nFue eliminada."<<endl;
            tablaHashing[posicionColision] = estacionEliminada;
            //cout <<"La estacion codigo 02 "<< estacionAux.codigo << " - nombre "<< estacionAux.nombre << endl;
            //cout <<"La estacion codigo 03 "<< tablaHashing[posicionColision].codigo << " - nombre "<< tablaHashing[posicionColision].nombre << endl;
        }
        else {
            cout << "No se pudo encontrar ninguna estacion con ese codigo" << endl;
        }
    }else {
        cout << "No se pudo encontrar ninguna estacion con ese codigo" << endl;
    }
}

// Cargar txts estaciones - viajes.
void cargarEstacionesIniciales() {
    ifstream archivo(archivoEstaciones); 
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream iss(linea);
            string codigo;
            string nombre;
            string ciudad;
            int cantSurtidores;
            double litrosSurtidor;
            string tipoCombustible;
            Estacion estacionNueva;

            if (iss >> codigo >> nombre >> ciudad >> cantSurtidores >> litrosSurtidor >> tipoCombustible) {
                estacionNueva.setCodigo(codigo);
                estacionNueva.setNombre(nombre);
                estacionNueva.setCiudad(ciudad);
                estacionNueva.setCantSurtidores(cantSurtidores);
                estacionNueva.setLitrosSurtidor(litrosSurtidor);
                estacionNueva.setTipoCombustible(tipoCombustible);
            }
            insertarEstacion(estacionNueva, tamanioDeTabla);
        }
        archivo.close();
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

//VIGENTE CARGAR VIAJES INICIALES
Grafo cargarViajesInicialesEnGrafo() {
    ifstream archivo(archivoViajes);
    bool cargarEnGrafo=true; 
    Grafo grafoNuevo;
    Nodo* nodoOrigen;
    Nodo* nodoDestino;
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream iss(linea);
            string codigoOrigen;
            string codigoDestino;
            int costoViaje;
            double horasViaje;
            cargarEnGrafo = true;     
            if (iss >> codigoOrigen >> codigoDestino >> costoViaje >> horasViaje) {
                if (!verificarCodigo(codigoOrigen)||retornarEstacion(codigoOrigen,tamanioDeTabla)==nullptr){ //Si no esta en la tabla de hasing) { 
                    cout<<"La estacion origen no se puede referenciar porque no existe estacion con ese codigo "<<endl;
                    cargarEnGrafo = false;
                }
                if (!verificarCodigo(codigoDestino)||retornarEstacion(codigoDestino,tamanioDeTabla)==nullptr){ //Si no esta en la tabla de hasing) { 
                    cout<<"La estacion destino no se puede referenciar porque no existe estacion con ese codigo "<<endl;
                    cargarEnGrafo = false;
                }
                if (cargarEnGrafo) {
                    if (grafoNuevo.encontreNodo(codigoOrigen) && grafoNuevo.encontreNodo(codigoDestino)) {
        
                    nodoOrigen=grafoNuevo.encontreNodo2(codigoOrigen);
                    nodoDestino=grafoNuevo.encontreNodo2(codigoDestino);
                    grafoNuevo.agregarArista(new Aristas(nodoOrigen, nodoDestino, costoViaje, horasViaje));
                    } else if (grafoNuevo.encontreNodo(codigoOrigen) && !grafoNuevo.encontreNodo(codigoDestino)) {
                        
                        nodoOrigen=grafoNuevo.encontreNodo2(codigoOrigen);
                        nodoDestino = new Nodo(retornarEstacion(codigoDestino, tamanioDeTabla));
                        grafoNuevo.agregarNodo(nodoDestino->estacion);
                        //cout<<"entrealsegundo"<<endl;
                        grafoNuevo.agregarArista(new Aristas(nodoOrigen, nodoDestino, costoViaje, horasViaje));
                     
                    } else if (!grafoNuevo.encontreNodo(codigoOrigen) && grafoNuevo.encontreNodo(codigoDestino)) {
                        
                        nodoOrigen = new Nodo(retornarEstacion(codigoOrigen, tamanioDeTabla));
                        nodoDestino=grafoNuevo.encontreNodo2(codigoDestino);
                        grafoNuevo.agregarNodo(nodoOrigen->estacion);
                        grafoNuevo.agregarArista(new Aristas(nodoOrigen, nodoDestino, costoViaje, horasViaje));
                        
                    } else if(!grafoNuevo.encontreNodo(codigoOrigen) && !grafoNuevo.encontreNodo(codigoDestino)) {           
                        
                      
                        nodoOrigen = new Nodo(retornarEstacion(codigoOrigen, tamanioDeTabla));
                        nodoDestino = new Nodo(retornarEstacion(codigoDestino, tamanioDeTabla));
                        //cout<<"entre al cuarto con codigo"<<"partida"<<nodoOrigen->estacion->getCodigo()<<"Dest:"<<nodoDestino->estacion->getCodigo()<<endl;
                        grafoNuevo.agregarNodo(nodoOrigen->estacion);
                        grafoNuevo.agregarNodo(nodoDestino->estacion);
                        grafoNuevo.agregarArista(new Aristas(nodoOrigen, nodoDestino, costoViaje, horasViaje));
                       
                    }                                        
                }
            }
        }           
    delete nodoOrigen;
    delete nodoDestino;
    archivo.close();     
    }
    return grafoNuevo;
}

// Mostras estaciones en tabla de hashing
void mostrarEstaciones(){
    for (Estacion estacion : tablaHashing) {
        if(estacion.getCodigo()!="000000" && estacion.getCodigo()!=""){
            estacion.getDatosEstacion();
            cout<<endl;
        }
    }
}

// Menu principal y funciones
void busquedaGrafoPorCosto(Grafo grafo){
    string codigoEstacionOrigen;
    string codigoEstacionDestino;

    cout<<"Debera ingresar una estacion de origen y destino, para calcular el tiempo que tardaria"<<endl;
    cout<<"Ingrese el codigo de la estacion origen: "<<endl;
    cin>>codigoEstacionOrigen;
    while(!verificarCodigo(codigoEstacionOrigen) && verificarSalir(codigoEstacionOrigen)) { 
        cout<<"El codigo de la estacion origen debe ser de 6 digitos ej: ABC123, vuelve a intentarlo: "<<endl;
        cout<<"Escribi salir para terminar. "<<endl;
        cin>>codigoEstacionOrigen;
    }
    
    cout<<"Ingrese el codigo de la estacion destino: "<<endl;
    cin>>codigoEstacionDestino;
    while(!verificarCodigo(codigoEstacionDestino) && verificarSalir(codigoEstacionDestino)) { 
        cout<<"El codigo de la estacion destino debe ser de 6 digitos ej: ABC123, vuelve a intentarlo: "<<endl;
        cout<<"Escribi salir para terminar. "<<endl;
        cin>>codigoEstacionDestino;
    }
    if (verificarSalir(codigoEstacionOrigen) && verificarSalir(codigoEstacionDestino)){
        grafo.mostrarDestinosDisponiblesPorCosto(codigoEstacionOrigen,codigoEstacionDestino);
    }
}

void busquedaGrafoPorTiempo(Grafo grafo){
    string codigoEstacionOrigen;
    string codigoEstacionDestino;

    cout<<"Debera ingresar una estacion de origen y destino, para calcular el tiempo que tardaria"<<endl;
    cout<<"Ingrese el codigo de la estacion origen: "<<endl;
    cin>>codigoEstacionOrigen;
    while(!verificarCodigo(codigoEstacionOrigen) && verificarSalir(codigoEstacionOrigen)) { 
        cout<<"El codigo de la estacion origen debe ser de 6 digitos ej: ABC123, vuelve a intentarlo: "<<endl;
        cout<<"Escribi salir para terminar. "<<endl;
        cin>>codigoEstacionOrigen;
    }
    
    cout<<"Ingrese el codigo de la estacion destino: "<<endl;
    cin>>codigoEstacionDestino;
    while(!verificarCodigo(codigoEstacionDestino) && verificarSalir(codigoEstacionDestino)) { 
        cout<<"El codigo de la estacion destino debe ser de 6 digitos ej: ABC123, vuelve a intentarlo: "<<endl;
        cout<<"Escribi salir para terminar. "<<endl;
        cin>>codigoEstacionDestino;
    }
    if (verificarSalir(codigoEstacionOrigen) && verificarSalir(codigoEstacionDestino)){
        grafo.mostrarDestinosDisponiblesPorTiempo(codigoEstacionOrigen,codigoEstacionDestino);
    }
}

void eliminarEstacionPorCodigo(){
    string codigo;
    cout<<"Ingrese el codigo de la estacion que desea eliminar: "<<endl;
    cin>>codigo;
    while(!verificarCodigo(codigo) && verificarSalir(codigo)) { 
        cout<<"El CODIGO debe ser de 6 digitos ej: ABC123, vuelve a intentarlo: "<<endl;
        cout<<"Escribi salir para terminar. "<<endl;
        cin>>codigo;
    }
    if (verificarSalir(codigo)){
        eliminarEstacion(codigo, tamanioDeTabla);
    }
}

void mostrarMenu()
{
    char opc;
    cargarEstacionesIniciales();
    Grafo grafoInicial = cargarViajesInicialesEnGrafo();
    cout << "Bienvenido al Menu de opciones, elija la opcion: " << endl;
    while (opc != 'n') {
        cout << "1-Consultar informacion de una estacion en particular \n2-Dar de alta una nueva estacion \n3-Dar de baja estaciones \n4-Mostrar todas las estaciones \n5-Busqueda de viaje por costo \n6-Busqueda de viaje por tiempo \n7-Salir" << endl;
        cin >> opc;
        if (opc == '1') {
            buscarEstacionPorCodigo();
            cout << endl;
            opc = deseaContinuar();
        }
        else if (opc == '2') {
            darDeAltaEstacion();
            cout << endl;
            opc = deseaContinuar();
        }
        else if (opc == '3') {
            eliminarEstacionPorCodigo();
            cout << endl;
            opc = deseaContinuar();
        }
        else if (opc == '4'){
            mostrarEstaciones();
            opc = deseaContinuar();
        }
         else if (opc == '5'){        
            busquedaGrafoPorCosto(grafoInicial);             
            cout << endl; 
            opc = deseaContinuar();                      
        }
         else if (opc == '6'){
            busquedaGrafoPorTiempo(grafoInicial); 
            cout << endl;            
            opc = deseaContinuar();                      
        }
        else if (opc == '7'){
            cout << endl; 
            opc = 'n';
                      
        }
    }
    cout << "Gracias por utilizar nuestro sistema!" << endl;
}

int main() {   
    mostrarMenu();
    return 0;
        
}