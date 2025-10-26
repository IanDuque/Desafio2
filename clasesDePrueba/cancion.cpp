#include "Cancion.h"
#include <iostream>
using namespace std;

Cancion::Cancion() : id(0), duracion(0.0) {}

void Cancion::setDatos(int _id, const string& _nombre, float _duracion) {
    id = _id;
    nombre = _nombre;
    duracion = _duracion;
}

void Cancion::mostrar() const {
    cout << "Canción [" << id << "]: " << nombre << " (" << duracion << " min)" << endl;
}

int Cancion::getId() const { return id; }
string Cancion::getNombre() const { return nombre; }
float Cancion::getDuracion() const { return duracion; }
