#include "Cancion.h"
#include <iostream>
using namespace std;

Cancion::Cancion() : id(0), duracion(0.0) {}

void Cancion::setDatos(int _id, const string& _nombre, float _duracion) {
    id = _id;
    nombre = _nombre;
    duracion = _duracion;
}
//funcion que muestra todos los datos de una cancion.
void Cancion::mostrar() const {
    cout << "Canción [" << id << "]: " << nombre << " (" << duracion << " min)" << endl;
}
//esta funcion recibe el nombre del artista y lo agrega a la ruta.
void Cancion::setruta(string nombreartista){
    ruta="/users/storage/(sub-ruta X variable)/"+nombreartista+"/audio/"+nombre;
}
//getters
int Cancion::getId() const { return id; }
string Cancion::getNombre() const { return nombre; }
float Cancion::getDuracion() const { return duracion; }
