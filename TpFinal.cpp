#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Estacion.h"
#include"Grafo.h"
#include"Arista.h"
#include"Nodo.h"

using namespace std;

int cantidadDeClaves = 100; // Tamaño de registros estimados
int tamanioDeTabla = 127;  // Tamaño de tabla

// struct Estaciones { // Estructura de estaciones
//     string codigo;
//     string nombre;
//     string ciudad;
//     int cantSurtidores;
//     double litrosSurtidor;
//     string tipoCombustible;
// };


string archivoEstaciones = "estaciones.txt"; // Archivo incial de estaciones
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

// void mostrarDatosEstacion(Estacion estacion){
//     cout<<"Codigo de la estacion: "<< estacion.getCodigo<<endl<<"Nombre: "<< estacion.getNombre<<endl<<"Ciudad: "<< estacion.getCiudad<<endl<<
//     "Cantidad de surtidores: "<< estacion.cantSurtidores<<endl<< "Litros por surtidor: "<<estacion.litrosSurtidor<<endl<<"Tipo de combustible: "<<estacion.tipoCombustible<<endl;
// }

bool noEstaOcupado (int posicion){
    return tablaHashing[posicion].getCodigo().empty();
}

// Estaciones crearEstacion (string codigo, string nombre, string ciudad, int cantSurtidores, 
// double litrosSurtidor, string tipoCombustible) {
//     Estaciones estacionAux;
//     estacionAux.codigo = codigo;  estacionAux.nombre = nombre;  
//     estacionAux.ciudad = ciudad;  estacionAux.cantSurtidores = cantSurtidores;  
//     estacionAux.litrosSurtidor = litrosSurtidor; estacionAux.tipoCombustible = tipoCombustible;
//     return estacionAux;
// }

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
int tratarColisionInsertar(int posicion, int tamanio) {
    int posicionAux, salida = -1;
    for (int i = 1; i < tamanio; i++) {
        posicionAux = posicion + (i * i);
        if (noEstaOcupado(posicionAux)) {
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
    Estacion datoAComparar;   // PREGUNTAR SI PODEMOS INSTANCIAR ESTACIONES ASI O SI QUIERE QUE SI O SI SEAN CON EL NEW.
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
    if (noEstaOcupado(posicionInicial)) {
        //Sumar el codigo agregado al txt en esta iteracion o a armar lista que guarde los codigos para el mostrar despues
        tablaHashing[posicionInicial] = estacion;
        //cout << "Soy la estacion: " << estacion.nombre << " Entre en pos Inicial: " << "Pos: " << posicionInicial << endl;
    }
    else {
        posicionColision = tratarColisionInsertar(posicionInicial, tamanio);
        if (posicionColision != (-1)) {
            //Sumar el codigo agregado al txt en esta iteracion o a armar lista que guarde los codigos para el mostrar despues
            tablaHashing[posicionColision] = estacion;
            //cout << "Soy la estacion: " << estacion.nombre << " Entre en pos Colision: " << "PosCos: " << posicionColision << endl;
        }
        else {
            cout << "No se pudo insertar la estacion en ningun lugar." << endl;
        }
    }
    cout << "Estacion registrada correctamente." << endl;
}

// Dar de alta con hashing
void darDeAltaEstacionV2() {
    Estacion estacionNueva;
    string opc,codigo,nombre,ciudad,tipoCombustible;
    int cantSurtidores,litrosPorSurtidor;

    while (opc != "salir"){
        cout<<"Escribi salir para terminar. "<<endl;
        cout << "Ingrese el CODIGO de 6 digitos de la estacion nueva: " << endl;
        cin >> codigo;
        while (!verificarCodigo(codigo) && verificarSalir(codigo)) {
            cout << "El CODIGO debe ser de 6 digitos ej: ABC123, vuelve a intentarlo: " << endl;
            //cout <<"Escribi salir para terminar. "<<endl;
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
        // mostrarDatosEstacion(estacionAux);
        estacionAux.getDatosEstacion();
    }
    else if(!noEstaOcupado(posicionInicial)) {
        //cout <<"Entre al else if: "<<endl;
        posicionColision = tratarColisionBuscar(posicionInicial, tamanio, codigo);

        if (posicionColision != (-1)) {
            //cout <<"Entre al if: "<<endl;
            estacionAux = tablaHashing[posicionColision];
            cout <<"La estacion encontrada es: "<<endl;
            // mostrarDatosEstacion(estacionAux);
            estacionAux.getDatosEstacion();
        }
        else {
            cout << "No se pudo encontrar ninguna estacion con ese codigo" << endl;
        }
    }else {
        cout << "No se pudo encontrar ninguna estacion con ese codigo" << endl;
    }
}

void buscarEstacionPorCodigoV2() {  
    // PREGUNTAR SI TIENE SENTIDO QUE HAYA ESTACIONES CON EL MISMO CODIGO,DUDA PARA BUSCAR POR CODIGO 
    // SOLO O POR NOMBRE TAMBIEN
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

void eliminarEstacionPorCodigoV2(){  
// Definir si al borrar tambien que sacarlo del txt
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

// Cargar estaciones desde el txt.
void cargarEstacionesIniciales() {
    ifstream archivo(archivoEstaciones); // Reemplaza "datos.txt" por el nombre de tu archivo
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
                // estacionNueva.codigo = codigo;
                // estacionNueva.nombre = nombre;
                // estacionNueva.ciudad = ciudad;
                // estacionNueva.cantSurtidores = cantSurtidores;
                // estacionNueva.litrosSurtidor = litrosSurtidor;
                // estacionNueva.tipoCombustible = tipoCombustible;
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

// Mostrar estaciones por hashing
void buscarEstacionesYMostrar(string codigo, int tamanio){
    int posicionColision, posicionInicial = funcionDeHashing(codigo, tamanio);
    Estacion estacionAux = tablaHashing[posicionInicial];
    
    if (!noEstaOcupado(posicionInicial) && estacionAux.getCodigo() == codigo) {
        // mostrarDatosEstacion(estacionAux);
        estacionAux.getDatosEstacion();        
    }
    else if(!noEstaOcupado(posicionInicial)) {
        posicionColision = tratarColisionBuscar(posicionInicial, tamanio, codigo);
        
        if (posicionColision != (-1)) {
            estacionAux = tablaHashing[posicionColision];
            // mostrarDatosEstacion(estacionAux);
            estacionAux.getDatosEstacion();  
        }
        else {
            cout << "No se pudo encontrar ninguna estacion con ese codigo" << endl;
        }
    }else {
        cout << "No se pudo encontrar ninguna estacion con ese codigo" << endl;
    }
}

void mostrarEstaciones3(){ // Aca estoy recorriendo toda la tabla de hash, buscar la forma de no recorrerla toda.
    for (Estacion estacion : tablaHashing) {
        if(estacion.getCodigo()!="000000" && estacion.getCodigo()!=""){
            estacion.getDatosEstacion();
        }
        
}
}

void mostrarEstacionesV2() {
    // PROBLEMA: Aca tenemos que agregar las estaciones insertadas al txt porque sino se van a mostrar las nuevas
    // o la otra opcion es crear una lista de codigos a partir de txt en primera instancia y si insertas una nueva por 
    // interface la agregas a esa lista. Despues leemos esa lista de codigos.
    ifstream archivo(archivoEstaciones); // Reemplaza "datos.txt" por el nombre de tu archivo 
    if (archivo.is_open()) { // ACA ESTO ME PARECE Q NO HACE FALTA,XQ NOSOTROS INSTANCIAMOS TODAS LAS ESTACIONES DEL TXT EN OBJETOS,ACA TENDRIAMOS QUE RECORRER LA TABLA DE HASH Y MOSTRARLOS NOMAS
        string linea, codigo;
        cout<<"Las estaciones registradas son: "<<endl;
        while (getline(archivo, linea)) {
            istringstream iss(linea);
            if (iss >> codigo){
                buscarEstacionesYMostrar(codigo, tamanioDeTabla);
                cout<<"\n";
            }
        }
        archivo.close();
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

// DEPRECADO DE ACA PARA ABAJO
void buscarEstacionPorCodigo()
{
    ifstream archivo(archivoEstaciones); // Reemplaza "datos.txt" por el nombre de tu archivo
    string codigo;
    cout << "Ingrese el codigo de la estacion que desea buscar: " << endl;
    cin >> codigo;

    if (archivo.is_open())
    {
        string linea;
        int nroLinea = 0;
        bool encontrado = false;

        while (getline(archivo, linea) && !encontrado)
        {
            // Procesa la línea leída según tus necesidades
            nroLinea++;
            if (linea.find(codigo) != string::npos)
            {
                cout << "Elemento encontrado en la línea " << codigo << ": " << linea << endl;
                encontrado = true;
                // Puedes realizar cualquier acción adicional que desees cuando encuentres el elemento
            }
        }
        if (!encontrado)
        {
            cout << "La estacion ingresada no es valida" << endl;
        }

        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

void eliminarEstacionPorCodigo()
{
    ifstream archivo(archivoEstaciones); // Reemplaza "datos.txt" por el nombre de tu archivo
    bool encontrado = false;
    string codigo;
    cout << "Ingrese el codigo de la estacion a eliminar: " << endl;
    cin >> codigo;
    if (archivo.is_open())
    {
        string linea;
        int nroLinea = 0;

        while (getline(archivo, linea) && !encontrado)
        {
            // Procesa la línea leída según tus necesidades
            nroLinea++;
            if (linea.find(codigo) != string::npos)
            {
                cout << "Elemento encontrado en la línea " << codigo << ": " << linea << std::endl;
                encontrado = true;
                // Puedes realizar cualquier acción adicional que desees cuando encuentres el elemento
            }
        }

        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
bool encontrarEstacion(string codigo)
{
    ifstream archivo(archivoEstaciones);
    bool encontrado = false;

    if (archivo.is_open())
    {
        string linea;
        int nroLinea = 0;
        while (getline(archivo, linea))
        {
            nroLinea++;
            if (linea.find(codigo) != string::npos)
            {
                encontrado = true;
            }
        }
        archivo.close();
    }
    else
    {
        cout << "no se puede abrir" << endl;
    }
    return encontrado;
}

void darDeAltaEstacion()
{
    ofstream archivo(archivoEstaciones, ios::app); // Reemplaza "datos.txt" por el nombre de tu archivo
    bool encontrado = false;
    if (archivo.is_open())
    {
        string codigo, ciudad, datos;
        cout << "Ingrese el codigo de la estacion: " << endl;
        cin >> codigo;
        while (encontrarEstacion(codigo))
        {
            cout << "El codigo ingresado ya existe\nIngresa otro codigo: " << endl;
            cin >> codigo;
        }
        cout << "Ingrese la ciudad de la estacion: " << endl;
        cin >> ciudad;
        datos = codigo + " " + ciudad;
        archivo << datos << endl;
        archivo.close();
        cout << "Datos escritos en el archivo correctamente." << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

// DEPRECADO DE ACA PARA ARRIBA



void mostrarMenu()
{
    char opc;
    cout << "Bienvenido al Menu de opciones, elija la opcion: " << endl;
    while (opc != 'n') {
        cout << "1-Consultar informacion de una estacion en particular \n2-Dar de alta una nueva estacion \n3-Dar de baja estaciones \n4-Mostrar todas las estaciones \n5-Salir" << endl;
        cin >> opc;
        if (opc == '1') {
            buscarEstacionPorCodigoV2();
            cout << endl;
            opc = deseaContinuar();
        }
        else if (opc == '2') {
            darDeAltaEstacionV2();
            cout << endl;
            opc = deseaContinuar();
        }
        else if (opc == '3') {
            eliminarEstacionPorCodigoV2();
            cout << endl;
            opc = deseaContinuar();
        }
        else if (opc == '4'){
            // mostrarEstacionesV2();
            mostrarEstaciones3();
            opc = deseaContinuar();
        }
        else if (opc == '5'){
            cout << endl; 
            opc = 'n';
                      
        }
    }
    cout << "Gracias por utilizar nuestro sistema!" << endl;
}

int main() {   
    cargarEstacionesIniciales();
    

    //cout << "Data" << tablaHashing[18].codigo << endl;
    //cout << "Data01" << tablaHashing[19].codigo << endl;
    //cout << "Data02" << tablaHashing[22].codigo << endl;
    //buscarEstacion(tablaHashing[19].codigo, tamanioDeTabla);
    mostrarMenu();

    return 0;
}
