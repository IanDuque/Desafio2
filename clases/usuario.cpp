#include "usuario.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

Usuario::Usuario() : cantidadFavoritosusuario(0), cantidadFavoritostotal(0) {}

void Usuario::setNombre(const string& _nombre) {
    nombre = _nombre;
}

void Usuario::setmembresia(const string& membresia){
    if (membresia=="premium"){
        premium=true;
    }
}
void Usuario::setCiudad(const string& _ciudad){
    ciudad= _ciudad;
}
void Usuario::setPais(const string& _pais){
    pais= _pais;
}
void Usuario::setFechaRegistro(const string& _fechaRegistro){
    fechaRegistro= _fechaRegistro;
}

string Usuario::getNombre() const {
    return nombre;
}

bool Usuario::buscarFavorito(int idCancion) const {
    for (int i = 0; i < cantidadFavoritostotal; ++i) {
        if (favoritos[i] == idCancion) {
            return true;
        }
    }
    return false;
}

void Usuario::cargarFavoritos() {
    cantidadFavoritosusuario = 0;
    string ruta = nombre + "_favoritos.txt";
    ifstream file(ruta);
    string linea;

    if (!file.is_open()) {
        cantidadFavoritostotal = 0;
        return;
    }

    while (getline(file, linea) && cantidadFavoritosusuario < MAX_FAVORITOS) {
        int id = atoi(linea.c_str());
        if (id > 0) {
            favoritos[cantidadFavoritosusuario++] = id;
        }
    }
    file.close();
    cantidadFavoritostotal = cantidadFavoritosusuario;
}

void Usuario::guardarFavoritos() const {
    string ruta = nombre + "_favoritos.txt";
    ofstream file(ruta);

    if (!file.is_open()) {
        cerr << "No se pudo guardar la lista en " << ruta << endl;
        return;
    }
    for (int i = 0; i < cantidadFavoritosusuario; ++i) {
        file << favoritos[i] << endl;
    }
    file.close();
}

void Usuario::agregarFavorito(int idCancion) {
    if (buscarFavorito(idCancion)) {
        cout << "La cancion (ID: " << idCancion << ") ya esta en favoritos." << endl;
        return;
    }

    if (cantidadFavoritostotal >= MAX_FAVORITOS) {
        cout << "Limite de " << MAX_FAVORITOS << " favoritos alcanzado. No se pudo agregar." << endl;
        return;
    }

    for (int i = cantidadFavoritostotal; i > cantidadFavoritosusuario; --i) {
        favoritos[i] = favoritos[i - 1];
    }

    favoritos[cantidadFavoritosusuario] = idCancion;

    cantidadFavoritosusuario++;
    cantidadFavoritostotal++;
    guardarFavoritos();

    cout << "Canción (ID: " << idCancion << ") agregada a favoritos." << endl;
}

void Usuario::eliminarFavorito(int idCancion) {
    int indiceAEliminar = -1;
    for (int i = 0; i < cantidadFavoritostotal; ++i) {
        if (favoritos[i] == idCancion) {
            indiceAEliminar = i;
            break;
        }
    }

    if (indiceAEliminar == -1) {
        cout << "La cancion (ID: " << idCancion << ") no estaba en favoritos." << endl;
        return;
    }

    bool eraFavoritoPropio = (indiceAEliminar < cantidadFavoritosusuario);

    for (int i = indiceAEliminar; i < cantidadFavoritostotal - 1; ++i) {
        favoritos[i] = favoritos[i + 1];
    }

    cantidadFavoritostotal--;
    if (eraFavoritoPropio) {
        cantidadFavoritosusuario--;
        guardarFavoritos();
    }

    cout << "Cancion (ID: " << idCancion << ") eliminada de favoritos." << endl;
}


void Usuario::cargarFavoritosDeOtro(const string& otroNombre) {
    string ruta = otroNombre + "_favoritos.txt";
    ifstream file(ruta);
    string linea;

    if (!file.is_open()) {
        cout << "Error: No se pudo encontrar la lista de '" << otroNombre << "'." << endl;
        return;
    }

    cout << "Agregando favoritos de '" << otroNombre << "' a tu lista..." << endl;

    int cancionesAgregadas = 0;
    bool seHicieronCambios = false;

    while (getline(file, linea)) {
        int idCancion = atoi(linea.c_str());
        if (idCancion <= 0) continue;


        if (cantidadFavoritostotal >= MAX_FAVORITOS) {
            cout << "Se alcanzó tu limite de favoritos (" << MAX_FAVORITOS << ")." << endl;
            cout << "No se pueden agregar mas canciones de esta lista." << endl;
            break;
        }

        if (buscarFavorito(idCancion)) {
            continue;
        }
        favoritos[cantidadFavoritostotal] = idCancion;
        cantidadFavoritostotal++;
        cancionesAgregadas++;
    }

    file.close();

    cout << "Se agregaron " << cancionesAgregadas << " canciones nuevas de '" << otroNombre << "'." << endl;
    cout << "Total de favoritos ahora: " << cantidadFavoritostotal << "." << endl;
}

void Usuario::mostrarFavoritos(const Album albumes[], int totalAlbumes) const {
    cout << "\n Favoritos de " << nombre << ":\n";
    if (cantidadFavoritostotal == 0) { // Usa el total
        cout << "  (Tu lista de favoritos está vacía)" << endl;
        return;
    }

    for (int i = 0; i < cantidadFavoritostotal; ++i) {
        int idCancion = favoritos[i];
        int idArtista = idCancion / 10000;
        int idAlbum = (idCancion / 100) % 100;
    }
}

void Usuario::eliminarFavoritosDeOtro() {
    cantidadFavoritostotal = cantidadFavoritosusuario;
}
int Usuario::getCantidadFavoritos() const {
    return cantidadFavoritosusuario;
}


int Usuario::getFavoritoPorIndice(int indice) const {
    // Verificación de límites para seguridad
    if (indice >= 0 && indice < cantidadFavoritosusuario) {
        return favoritos[indice];
    }
    // Devolver un ID inválido si el índice está fuera de rango
    return -1;
}
