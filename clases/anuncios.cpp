#include "anuncios.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ManejadorAnuncios::ManejadorAnuncios(string nombre_archivo) {
    archivo = nombre_archivo;
    anuncio_actual = "";
    categoria = "";
}

// Obtiene un anuncio aleatorio según la prioridad
string ManejadorAnuncios::obtenerAnuncio() {
    int tipo = (rand() % 6) + 1; // Genera un número del 1 al 6
    int inicio = 0, fin = 0;

    // Determinar rango según prioridad
    // Prioridad C (1)
    if (tipo == 1) {
        inicio = 1;
        fin = 15;
        categoria = "C";
    }
    // Prioridad B (2, 3)
    else if (tipo <= 3) {
        inicio = 19;
        fin = 33;
        categoria = "B";
    }
    // Prioridad AAA (4, 5, 6)
    else {
        inicio = 37;
        fin = 51;
        categoria = "AAA";
    }

    int linea_objetivo = inicio + (rand() % (fin - inicio + 1));

    ifstream archivo_in(archivo.c_str());
    if (!archivo_in.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de anuncios (" << archivo << ")." << endl;
        return "";
    }

    string linea;
    int contador = 1;
    anuncio_actual = "";

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
