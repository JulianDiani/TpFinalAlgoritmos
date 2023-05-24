#include <iostream>
#include <fstream>
#include <string>
using namespace std;


string archivoEstaciones="estaciones.txt";
void leerEstaciones(){
    ifstream archivo(archivoEstaciones); // Reemplaza "datos.txt" por el nombre de tu archivo

    if (archivo.is_open()) {
        string linea;

        while (getline(archivo, linea)) {
            // Procesa la línea leída según tus necesidades
            cout << linea << endl;
        }

        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

void buscarEstacionPorCodigo(){
    ifstream archivo(archivoEstaciones); // Reemplaza "datos.txt" por el nombre de tu archivo
    string codigo;
    cout<<"Ingrese el codigo de la estacion que desea buscar: "<<endl;
    cin>>codigo;

    if (archivo.is_open()) {
        string linea;
        int nroLinea=0;
        bool encontrado=false;

        while (getline(archivo, linea) && !encontrado) {
            // Procesa la línea leída según tus necesidades
            nroLinea++;
            if (linea.find(codigo) != string::npos) {
                cout << "Elemento encontrado en la línea " << codigo << ": " << linea <<endl;
                encontrado=true;
                // Puedes realizar cualquier acción adicional que desees cuando encuentres el elemento
            }
        }
        if (!encontrado){
            cout<<"La estacion ingresada no es valida"<<endl;
        }
        

        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
void eliminarEstacionPorCodigo(){
    ifstream archivo(archivoEstaciones); // Reemplaza "datos.txt" por el nombre de tu archivo
    bool encontrado=false;
    string codigo;
    cout<<"Ingrese el codigo de la estacion a eliminar: "<<endl;
    cin>>codigo;
    if (archivo.is_open()) {
        string linea;
        int nroLinea=0;

        while (getline(archivo, linea) && !encontrado) {
            // Procesa la línea leída según tus necesidades
            nroLinea++;
            if (linea.find(codigo) != string::npos) {
                cout << "Elemento encontrado en la línea " << codigo << ": " << linea << std::endl;
                encontrado=true;
                // Puedes realizar cualquier acción adicional que desees cuando encuentres el elemento
            }
        }

        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
bool encontrarEstacion(string codigo){
    ifstream archivo(archivoEstaciones);
    bool encontrado=false;

    if (archivo.is_open()) {
        string linea;
        int nroLinea=0;
        while (getline(archivo, linea)) {
            nroLinea++;
            if (linea.find(codigo) != string::npos) {
                encontrado=true;
            }
            
    
        }
        archivo.close();
    }else{
        cout<<"no se puede abrir"<<endl;
    }
    return encontrado;
}




void darDeAltaEstacion() {
    ofstream archivo(archivoEstaciones,ios::app); // Reemplaza "datos.txt" por el nombre de tu archivo
    bool encontrado=false;
    if (archivo.is_open()) {
        string codigo,ciudad,datos;
        cout<<"Ingrese el codigo de la estacion: "<<endl;
        cin>>codigo;
        while(encontrarEstacion(codigo)){
            cout<<"El codigo ingresado ya existe\nIngresa otro codigo: "<<endl;
            cin>>codigo;
        }
        cout<<"Ingrese la ciudad de la estacion: "<<endl;
        cin>>ciudad;
        datos= codigo +" "+ ciudad;
        archivo << datos <<endl;
        archivo.close();
        cout << "Datos escritos en el archivo correctamente." <<endl;
    } else {
        cout << "No se pudo abrir el archivo." <<endl;
    }
    
}
char deseaContinuar(){
    char dato;
    cout<<"Si desea continuar ingrese s: ";
    cin >> dato;
    if(dato=='s'|| dato=='S'){
        return dato;
    }else{
        return 'n';
    }
    
}

//Agregar bucle para salida tipo bot.
void mostrarMenu(){
    char opc;
    cout<<"Bienvenido al Menu de opciones,elija la opcion: "<<endl;
    
    while(opc!='n'){
        cout<<"1-Consultar informacion de una estacion en particular \n2-Dar de alta una nueva estacion\n3-Dar de baja estaciones\n4-Mostrar todas las estaciones\n5-Salir"<<endl;
        cin>>opc;
        if(opc=='1'){
        buscarEstacionPorCodigo();
        opc=deseaContinuar();
        }else if(opc=='2'){
            darDeAltaEstacion();
            opc=deseaContinuar();  
        }else if (opc=='3'){
            eliminarEstacionPorCodigo();
            opc=deseaContinuar();
            
        }
    }
    cout<<"Gracias por utilizar nuestro sistema!"<<endl;
}
    
void deseaSeguir(){
    char resp;
    cout<<"Desea continuar? s/n"<<endl;
    cin>>resp;
    if(resp=='s'|| resp=='S'){
        mostrarMenu();
    }
    cout<<"Nos vemo nemo"<<endl;
}

int main() {
    mostrarMenu();
    //leerEstaciones();
    return 0;
}

