#include "album.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// CORRECCION: Inicializar duracionalbum en el constructor, no en setDatos
Album::Album() : id(0), calificacion(0), cantidadCanciones(0), duracionalbum(0.0) {}

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
    // CORRECCION: Se elimino la linea "duracionalbum = 0;" que borraba el acumulado.
}

void Album::agregarCancion(int idCancion, const string& nombreCancion, float duracion) {
    if (cantidadCanciones < MAX_CANCIONES) {
        idsCanciones[cantidadCanciones] = idCancion;
        nombresCanciones[cantidadCanciones] = nombreCancion;
        duracionesCanciones[cantidadCanciones] = duracion;
        duracionalbum+=duracion;
        cantidadCanciones++;
    } else {
        // Se elimino el acento de "Maximo"
        cout << " Maximo de 15 canciones alcanzado." << endl;
    }
}

void Album::mostrar() const {
    cout << "Album [" << id << "]: " << nombre << " de " << artista << endl;
    cout << "  Genero: " << genero << ", Disquera: " << disquera << ", Fecha: " << fechaLanzamiento << endl;
    cout << "  Portada: " << rutaPortada << ", Calificacion: " << calificacion << "/10" << endl;
    cout << "  Canciones (" << cantidadCanciones << "):" << endl;
    for (int i = 0; i < cantidadCanciones; ++i) {
        cout << "    - [" << idsCanciones[i] << "] " << nombresCanciones[i]
             << " (" << duracionesCanciones[i] << " min)" << endl;
    }
}
int Album::getId() const {
    return id;
}
float Album::getduracion() {
    return duracionalbum;
}
void Album::simularReproduccion(int idCancion) const {
    for (int i = 0; i < cantidadCanciones; ++i) {
        if (idsCanciones[i] == idCancion) {
            // Se elimino el acento de "Cancion"
            cout << "  - REPRODUCIENDO: Cancion [" << idsCanciones[i] << "] "
                 << nombresCanciones[i] << " (" << duracionesCanciones[i] << " min)"
                 << " del Album: " << nombre << endl;
            return;
        }
    }
    // Se elimino el acento de "cancion"
    cout << "  - Error: La cancion con ID " << idCancion << " no se encontro en el album." << endl;
}

// NUEVA FUNCION 2: Obtiene el ID de una cancion aleatoria del album
int Album::getIDdeCancionAleatoria() const {
    if (cantidadCanciones == 0) return -1;
    // rand() % N genera un numero entre 0 y N-1
    int indiceAleatorio = rand() % cantidadCanciones;
    return idsCanciones[indiceAleatorio];
}

// Getters (solo los necesarios para las funciones de reproduccion)
string Album::getNombre() const {
    return nombre;
}

int Album::getCantidadCanciones() const {
    return cantidadCanciones;
}
string Album::getArtista() const {
    return artista;
}
