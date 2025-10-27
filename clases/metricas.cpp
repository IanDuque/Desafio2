#include "metricas.h"
#include <fstream>
#include <iostream>
using namespace std;

fstream metricas;

long long calcular_memoria_usada(int totalArtistas, int totalAlbumes) {

    //se define como un long para evitar perdida o errores de datos en caso de que el numero sea demasiado grande.
    long totalusado = 0;

    //en esta parte se suma la memoria total usada por los objetos en el momento en que es invocada,
    //ademas de esto se deberan agregar posteriormente el espacio consumido por cada variable local.
    totalusado += (long)totalArtistas * sizeof(Artistica);
    totalusado += (long)totalAlbumes * sizeof(Album);

    return totalusado;
}
void abrir_archivo(){
    fstream metricas("metricas.txt");
    if (!metricas.is_open()){
        cerr << "error al abrir el archivo" << endl;
    }
}
void cerrar_archivo(){
    if (metricas.is_open()){
        metricas.close();
    }
}
void agregar_metrica(long int iteraciones, long int memoria, string nombrefuncion){
    metricas << "funcion: " << nombrefuncion << ", iteraciones totales: " << to_string(iteraciones) << ", memoria usada en el momento de ejecucion:" << memoria << endl;
}
void mostrarmetricas(){
    string linea=" ";
    while (getline(metricas,linea)){
        cout << linea;
    }
}
