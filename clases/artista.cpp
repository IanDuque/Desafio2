#include "artista.h"
#include <iostream>
using namespace std;

Artistica::Artistica() : id(0), edad(0), seguidores(0), cantidadAlbumes(0) {}



void Artistica::setDatos(int _id, const string& _nombre, int _edad, const string& _pais, int _seguidores) {
    id = _id;
    nombre = _nombre;
    edad = _edad;
    pais = _pais;
    seguidores = _seguidores;
}

void Artistica::agregarAlbum(int idAlbum, const string& nombreAlbum) {
    if (cantidadAlbumes < MAX_ALBUMES) {
        idsAlbumes[cantidadAlbumes] = idAlbum;
        nombresAlbumes[cantidadAlbumes] = nombreAlbum;
        cantidadAlbumes++;
    } else {
        cout << "⚠️ Máximo de 10 álbumes alcanzado." << endl;
    }
}

void Artistica::mostrar() const {
    cout << "Artista [" << id << "]: " << nombre << endl;
    cout << "  Edad: " << edad << ", Pais: " << pais << ", Seguidores: " << seguidores << endl;
    cout << "  Albumes publicados: " << cantidadAlbumes << endl;
    for (int i = 0; i < cantidadAlbumes; ++i) {
        cout << "    - [" << idsAlbumes[i] << "] " << nombresAlbumes[i] << endl;
    }
}
int Artistica::getId() const {
    return id;
}
string Artistica::getnombre() const {
    return nombre;
}


