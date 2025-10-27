#include "anuncios.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
//se genera una semilla para generar numeros aleatorios, y asi conseguir un anuncio al azar entre los que se encuentran en el archivo "anuncios.txt",
//posteriormente se muestra el anuncio y se elimina el objeto que lo contiene.
string archivo;
string anuncio_actual;
string categoria;

ManejadorAnuncios::ManejadorAnuncios(string nombre_archivo) {
    archivo = nombre_archivo;
    anuncio_actual = "";
}

// Obtiene un anuncio aleatorio según la prioridad
string ManejadorAnuncios::obtenerAnuncio() {
    int tipo = (rand() % 6) + 1; // 1 a 6
    int inicio = 0, fin = 0;

    // Determinar rango según prioridad
    if (tipo == 1) {            // C
        inicio = 1;
        fin = 15;
        categoria="C";
    } else if (tipo <= 3) {   // B
        inicio = 19;
        fin = 33;
        categoria="B";
    } else {                  // AAA
        inicio = 37;
        fin = 51;
        categoria="AAA";
    }

    // Elegir línea aleatoria dentro del rango
    int linea_objetivo = inicio + (rand() % (fin - inicio + 1));

    ifstream archivo_in(archivo.c_str());
    if (!archivo_in.is_open()) {
        cerr << "No se pudo abrir el archivo de anuncios." << endl;
        return "";
    }

    string linea;
    int contador = 1;
    while (getline(archivo_in, linea)) {
        if (contador == linea_objetivo) {
            anuncio_actual = linea;
            break;
        }
        contador++;
    }
    archivo_in.close();

    return anuncio_actual;
}

void ManejadorAnuncios::mostrarAnuncio() {
    cout << anuncio_actual << endl << "categoria " << categoria << endl;
}

void anuncio(){
    ManejadorAnuncios anuncioamostrar("anuncios.txt");
    string anuncio = anuncioamostrar.obtenerAnuncio();
    anuncioamostrar.mostrarAnuncio();
}

int generaranuncio() {
    anuncio();
    return 0;
}
