#ifndef CANCION_H
#define CANCION_H

#include <string>
using namespace std;

class Cancion {
private:
    int id;
    string nombre;
    float duracion;
public:
    Cancion();
    void setDatos(int _id, const string& _nombre, float _duracion);
    void mostrar() const;

    int getId() const;
    string getNombre() const;
    float getDuracion() const;
};

#endif
