#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
//Para borrar podemos usar una estacion predefinida con un codigo que indica que se borro un dato.
//Busqueda corta porque encontro uno, esta vacio o seguis buscando y llegaste al len.

using namespace std;

int cantidadDeClaves = 100; // Tamaño de registros estimados
int tamanioDeTabla = 127;  // Tamaño de tabla

// Estructura de estaciones
struct Estaciones
{
    string codigo;
    string nombre;
    string ciudad;
    int cantSurtidores;
    double litrosSurtidor;
    string tipoCombustible;
    //bool colicione;
};

string archivoEstaciones = "estaciones.txt"; // Archivo incial de estaciones
vector<Estaciones> tablaHashing(tamanioDeTabla);     // Tabla de hashing

//Funciones auxiliares
bool verificarTipoComb (string tipo) {
    return tipo == "SUP" || tipo == "INF" || tipo == "NIT";
}

// Funciones de hashing
// Hashing Modulo
int funcionModulo(int key, int tamanio)
{
    return key % tamanio;
}

// Hashing Folding ultimos 3 + Divicion
// Devuele posicion

int funcionDeHashing(string codigo, int tamanio)
{
    int salida = 0, posicion;
    for (int i = codigo.size() - 3; i < codigo.size(); i++)
    {
        salida += codigo[i];
        // cout <<"Salida= "<< salida <<"Codigo= "<< codigo[i] << endl;
    }
    posicion = funcionModulo(salida, tamanio);
    return posicion;
}

bool noEstaOcupado(int posicion)
{
    return tablaHashing[posicion].codigo.empty();
}

// Colision Quadratic probing
// Si da -1 no encontro posicion
int tratarColision(int posicion, int tamanio)
{
    int posicionAux, salida = -1;
    for (int i = 1; i < tamanio; i++)
    {
        posicionAux = posicion + (i * i);
        if (noEstaOcupado(posicionAux))
        {
            salida = posicionAux;
            // tablaHashing.insert(tablaHashing.begin()+posicionAux,estacion);
            break;
        }
    }
    return salida;
}

// Insercion
void insertarEstacion(Estaciones estacion, int tamanio)
{
    int posicionColision, posicionInicial = funcionDeHashing(estacion.codigo, tamanio);
    if (noEstaOcupado(posicionInicial))
    {
        //Sumar el codigo agregado al txt
        tablaHashing.insert(tablaHashing.begin() + posicionInicial, estacion);
        cout << "Soy la estacion: " << estacion.nombre << "Entre en pos Inicial: " << "Pos: " << posicionInicial << endl;
    }
    else
    {
        posicionColision = tratarColision(posicionInicial, tamanio);
        if (posicionColision != (-1))
        {
            //Sumar el codigo agregado al txt
            tablaHashing.insert(tablaHashing.begin() + posicionColision, estacion);
            cout << "Soy la estacion: " << estacion.nombre << " Entre en pos Colision: " << "PosCos: " << posicionColision << endl;
        }
        else
        {
            cout << "No se pudo insertar la estacion en ningun lugar" << endl;
        }
    }
    cout << "Estacion registrada correctamente" << endl;
}

// Cargar estaciones desde el txt.
void cargarEstacionesIniciales()
{
    ifstream archivo(archivoEstaciones); // Reemplaza "datos.txt" por el nombre de tu archivo

    if (archivo.is_open())
    {
        string linea;

        while (getline(archivo, linea))
        {

            istringstream iss(linea);
            string codigo;
            string nombre;
            string ciudad;
            int cantSurtidores;
            double litrosSurtidor;
            string tipoCombustible;

            Estaciones estacionNueva;

            if (iss >> codigo >> nombre >> ciudad >> cantSurtidores >> litrosSurtidor >> tipoCombustible)
            {
                estacionNueva.codigo = codigo;
                estacionNueva.nombre = nombre;
                estacionNueva.ciudad = ciudad;
                estacionNueva.cantSurtidores = cantSurtidores;
                estacionNueva.litrosSurtidor = litrosSurtidor;
                estacionNueva.tipoCombustible = tipoCombustible;
            }
            insertarEstacion(estacionNueva, tamanioDeTabla);
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

//Dar de alta acomodar con hashing
void darDeAltaEstacionV2(){
    // string codigo,nombre,ciudad,tipoCombustible;
    // int cantSurtidores,litrosSurtidor;
    Estaciones estacionNueva;
    
    cout << "Ingrese el CODIGO de 6 digitos de la estacion nueva: " << endl;
    cin >> estacionNueva.codigo;
    while (estacionNueva.codigo.size() != 6) {
        cout << "El CODIGO debe ser de 6 digitos ej: ABC123, vuelve a intentarlo: " << endl;
        cin >> estacionNueva.codigo;
    }
    cout << "Ingrese el nombre: " << endl;
    cin >> estacionNueva.nombre;
    cout << "Ingrese la ciudad: " << endl;
    cin >> estacionNueva.ciudad;
    cout << "Ingrese el tipo de combustible: " << endl;
    cin >> estacionNueva.tipoCombustible;
    while (!verificarTipoComb(estacionNueva.tipoCombustible)) {  // ACA CAMBIO EL NOT POR EL !, PROBAR SI ANDA XD
        cout << "Los tipos de combustible validos son SUP-INF-NIT : " << endl;
        cin >> estacionNueva.tipoCombustible;
    }
    cout << "Ingrese la cantidad de surtidores: " << endl;
    cin >> estacionNueva.cantSurtidores;
    cout << "Ingrese los litros que tiene cada surtidor: " << endl;
    cin >> estacionNueva.litrosSurtidor;
    // estacionNueva.codigo = codigo;
    // estacionNueva.nombre = nombre;
    // estacionNueva.ciudad = ciudad;
    // estacionNueva.cantSurtidores = cantSurtidores;
    // estacionNueva.litrosSurtidor = litrosSurtidor;
    // estacionNueva.tipoCombustible = tipoCombustible;
    cout << "Todos los datos fueron ingresados correctamente" << endl;

    //Insercion
    insertarEstacion(estacionNueva, tamanioDeTabla);
}

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
char deseaContinuar()
{
    char dato;
    cout << "Si desea continuar ingrese s: ";
    cin >> dato;
    if (dato == 's' || dato == 'S')
    {
        return dato;
    }
    else
    {
        return 'n';
    }
}

// Agregar bucle para salida tipo bot.
void mostrarMenu()
{
    char opc;
    cout << "Bienvenido al Menu de opciones, elija la opcion: " << endl;

    while (opc != 'n')
    {
        cout << "1-Consultar informacion de una estacion en particular \n2-Dar de alta una nueva estacion\n3-Dar de baja estaciones\n4-Mostrar todas las estaciones\n5-Salir" << endl;
        cin >> opc;
        if (opc == '1')
        {
            buscarEstacionPorCodigo();
            opc = deseaContinuar();
        }
        else if (opc == '2')
        {
            darDeAltaEstacionV2();
            opc = deseaContinuar();
        }
        else if (opc == '3')
        {
            eliminarEstacionPorCodigo();
            opc = deseaContinuar();
        }
    }
    cout << "Gracias por utilizar nuestro sistema!" << endl;
}

void deseaSeguir()
{
    char resp;
    cout << "Desea continuar? s/n" << endl;
    cin >> resp;
    if (resp == 's' || resp == 'S')
    {
        mostrarMenu();
    }
    cout << "Nos vemo nemo" << endl;
}

int main()
{   
    cargarEstacionesIniciales();
    //darDeAltaEstacionV2();
    mostrarMenu();
    // leerEstaciones();
    return 0;
}
