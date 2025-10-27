#include "Usuario.h"
#include <fstream>
#include <cstdlib> // Para atoi
#include <iostream>
using namespace std;

Usuario::Usuario() : cantidadFavoritos(0) {}

void Usuario::setNombre(const string& _nombre) {
    nombre = _nombre;
}

string Usuario::getNombre() const {
    return nombre;
}

bool Usuario::buscarFavorito(int idCancion) const {
    for (int i = 0; i < cantidadFavoritos; ++i) {
        if (favoritos[i] == idCancion) {
            return true;
        }
    }
    return false;
}




void Usuario::cargarFavoritos() {
    cantidadFavoritos = 0;
    string ruta = nombre + "_favoritos.txt";
    ifstream file(ruta);
    string linea;

    if (!file.is_open()) {

        return;
    }

    while (getline(file, linea) && cantidadFavoritos < MAX_FAVORITOS) {
        int id = atoi(linea.c_str());
        if (id > 0) {
            favoritos[cantidadFavoritos++] = id;
        }
    }
    file.close();
}

void Usuario::guardarFavoritos() const {
    string ruta = nombre + "_favoritos.txt";
    ofstream file(ruta);

    if (!file.is_open()) {
        cout << "Error critico: No se pudo guardar la lista en " << ruta << endl;
        return;
    }

    for (int i = 0; i < cantidadFavoritos; ++i) {
        file << favoritos[i] << endl;
    }
    file.close();
}

void Usuario::agregarFavorito(int idCancion) {
    // 1. Búsqueda para evitar duplicados
    if (buscarFavorito(idCancion)) {
        cout << "La cancion (ID: " << idCancion << ") ya esta en favoritos." << endl;
        return;
    }


    if (cantidadFavoritos >= MAX_FAVORITOS) {
        cout << "Limite de " << MAX_FAVORITOS << " favoritos alcanzado. No se pudo agregar." << endl;
        return;
    }


    favoritos[cantidadFavoritos] = idCancion;
    cantidadFavoritos++;

    guardarFavoritos();
    cout << "Canción (ID: " << idCancion << ") agregada a favoritos." << endl;
}


void Usuario::eliminarFavorito(int idCancion) {
    // 1. Búsqueda para encontrar el índice
    int indiceAEliminar = -1;
    for (int i = 0; i < cantidadFavoritos; ++i) {
        if (favoritos[i] == idCancion) {
            indiceAEliminar = i;
            break;
        }
    }


    if (indiceAEliminar == -1) {
        cout << "La cancion (ID: " << idCancion << ") no estaba en favoritos." << endl;
        return;
    }


    for (int i = indiceAEliminar; i < cantidadFavoritos - 1; ++i) {
        favoritos[i] = favoritos[i + 1];
    }

    // 4. Actualizar contador y guardar
    cantidadFavoritos--;
    guardarFavoritos();

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


        if (cantidadFavoritos >= MAX_FAVORITOS) {
            cout << "Se alcanzó tu limite de favoritos (" << MAX_FAVORITOS << ")." << endl;
            cout << "No se pueden agregar mas canciones de esta lista." << endl;
            break;
        }


        if (buscarFavorito(idCancion)) {

            continue;
        }


        favoritos[cantidadFavoritos] = idCancion;
        cantidadFavoritos++;
        cancionesAgregadas++;
        seHicieronCambios = true;
    }

    file.close();


    if (seHicieronCambios) {
        guardarFavoritos();
    }

    cout << "Se agregaron " << cancionesAgregadas << " canciones nuevas de '" << otroNombre << "'." << endl;
    cout << "Total de favoritos ahora: " << cantidadFavoritos << "." << endl;
}



void Usuario::mostrarFavoritos(const Album albumes[], int totalAlbumes) const {
    cout << "\n Favoritos de " << nombre << ":\n";
    if (cantidadFavoritos == 0) {
        cout << "  (Tu lista de favoritos está vacía)" << endl;
        return;
    }

    for (int i = 0; i < cantidadFavoritos; ++i) {
        int idCancion = favoritos[i];


        int idArtista = idCancion / 10000;
        int idAlbumSimple = (idCancion / 100) % 100;
        int idAlbumCompleto = idArtista * 100 + idAlbumSimple;

        bool encontrado = false;
        for (int j = 0; j < totalAlbumes; ++j) {
            if (albumes[j].getId() == idAlbumCompleto) {

                cout << "  - ID Cancion: " << idCancion << " (pertenece al Album ID: " << idAlbumCompleto << ")" << endl;

                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            cout << "  - ID Cancion: " << idCancion << " (Album no encontrado)" << endl;
        }

    }
}
void Usuario::eliminarFavoritosDeOtro(const string& otroNombre) {
    string ruta = otroNombre + "_favoritos.txt";
    ifstream file(ruta);
    string linea;

    if (!file.is_open()) {
        cout << "Error: No se pudo encontrar la lista de '" << otroNombre << "' para eliminar." << endl;
        return;
    }

    cout << "Eliminando canciones de la lista de '" << otroNombre << "' de tu lista...\n";

    int cancionesEliminadas = 0;

    while (getline(file, linea)) {
        int idCancion = atoi(linea.c_str());
        if (idCancion <= 0) continue;

        // Buscamos si el usuario actual (usuario1) tiene esta canción
        int indiceAEliminar = -1;
        for (int i = 0; i < cantidadFavoritos; ++i) {
            if (favoritos[i] == idCancion) {
                indiceAEliminar = i;
                break;
            }
        }

        if (indiceAEliminar != -1) {
            // Eliminar por desplazamiento de array (misma lógica que eliminarFavorito)
            for (int i = indiceAEliminar; i < cantidadFavoritos - 1; ++i) {
                favoritos[i] = favoritos[i + 1];
            }
            cantidadFavoritos--;
            cancionesEliminadas++;
        }
    }

    file.close();

    if (cancionesEliminadas > 0) {
        guardarFavoritos(); // Guardar el cambio si hubo eliminaciones
        cout << "Se eliminaron " << cancionesEliminadas << " canciones de tu lista.\n";
    } else {
        cout << "Ninguna cancion del usuario '" << otroNombre << "' fue encontrada y eliminada.\n";
    }
}
