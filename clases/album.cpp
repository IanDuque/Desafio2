#include "Album.h"
#include <iostream>
using namespace std;

Album::Album() : id(0), calificacion(0), cantidadCanciones(0) {}

void Album::setDatos(int _id, const string& _nombre, const string& _artista, const string& _genero,
                     const string& _disquera, const string& _fecha, const string& _ruta, int _calif) {
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
        idsCanciones[cantidadCanciones] = idCancion;
        nombresCanciones[cantidadCanciones] = nombreCancion;
        duracionesCanciones[cantidadCanciones] = duracion;
        cantidadCanciones++;
    } else {
        cout << " Máximo de 15 canciones alcanzado." << endl;
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
