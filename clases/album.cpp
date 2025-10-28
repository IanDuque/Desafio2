#include "album.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Album::Album() : id(0), nombre(""), artista(""), genero(""), disquera(""), fechaLanzamiento(""),
    rutaPortada(""), calificacion(0), cantidadCanciones(0), duracionalbum(0.0f) {
    // Inicialización por defecto
}

void Album::setDatos(int _id, const string& _nombre, const string& _artista, const string& _genero,
                     const string& _disquera, const string& _fecha, const string& _ruta, int _calif, float _duracionTotalPlaceholder) {
    id = _id;
    nombre = _nombre;
    artista = _artista;
    genero = _genero;
    disquera = _disquera;
    fechaLanzamiento = _fecha;
    rutaPortada = _ruta;
    calificacion = _calif;
}

void Album::agregarCancion(int idCancion, const string& nombreCancion, float duracion) {
    if (cantidadCanciones < MAX_CANCIONES) {
        canciones[cantidadCanciones].setDatos(idCancion, nombreCancion, duracion);
        duracionalbum += duracion;
        cantidadCanciones++;
    } else {
        cerr << "ADVERTENCIA: Limite de canciones (" << MAX_CANCIONES << ") alcanzado en el album " << nombre << endl;
    }
}

const Cancion* Album::getCancionPorId(int idCancion) const {
    for (int i = 0; i < cantidadCanciones; ++i) {
        if (canciones[i].getId() == idCancion) {
            return &canciones[i];
        }
    }
    return nullptr;
}

string Album::getPortada() const {
    return rutaPortada;
}

string Album::getArtista() const {
    return artista;
}

string Album::getNombre() const {
    return nombre;
}

int Album::getId() const {
    return id;
}

int Album::getCantidadCanciones() const {
    return cantidadCanciones;
}

float Album::getduracion() const {
    return duracionalbum;
}

int Album::getIDdeCancionAleatoria() const {
    if (cantidadCanciones == 0) return -1;
    int indice = rand() % cantidadCanciones;
    return canciones[indice].getId();
}

void Album::simularReproduccion(int idCancion) const {
    const Cancion* cancion = getCancionPorId(idCancion);
    if (cancion != nullptr) {
        cout << "\nSimulando reproduccion (ID: " << cancion->getId() << "):\n";
        cout << "  -> Album: " << nombre << " (Artista: " << artista << ")\n";
        cout << "  -> Titulo: " << cancion->getNombre() << " (Duracion: " << cancion->getDuracion() << "s)\n";
    } else {
        cout << "\nError: Cancion con ID " << idCancion << " no encontrada en el album " << nombre << ".\n";
    }
}

void Album::mostrar() const {
    cout << "ID Album: " << id << " | Nombre: " << nombre << " | Artista: " << artista << endl;
    cout << "  Genero: " << genero << " | Disquera: " << disquera << " | Lanzamiento: " << fechaLanzamiento << endl;
    cout << "  Calif: " << calificacion << "/5 | Canciones: " << cantidadCanciones << " | Duracion Total: " << duracionalbum << "s" << endl;
    cout << "  Canciones incluidas:\n";

    for (int i = 0; i < cantidadCanciones; ++i) {
        cout << "    - ID: " << canciones[i].getId() << ", Titulo: " << canciones[i].getNombre() << ", Duracion: " << canciones[i].getDuracion() << "s\n";
    }
}
