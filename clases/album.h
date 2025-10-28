#ifndef ALBUM_H
#define ALBUM_H
#include "cancion.h"
#include <string>
using namespace std;

const int MAX_CANCIONES = 50;

class Album {
private:
    int id;
    string nombre;
    string artista;
    string genero;
    string disquera;
    string fechaLanzamiento;
    string rutaPortada;
    int calificacion;

    Cancion canciones[MAX_CANCIONES];

    int cantidadCanciones;
    float duracionalbum;

public:
    Album();

    void setDatos(int _id, const string& _nombre, const string& _artista, const string& _genero,
    const string& _disquera, const string& _fecha, const string& _ruta, int _calif, float _duracionTotalPlaceholder);

    void agregarCancion(int idCancion, const string& nombreCancion, float duracion);

    void mostrar() const;
    int getId() const;
    float getduracion() const;

    void simularReproduccion(int idCancion) const;
    string getArtista() const;
    int getIDdeCancionAleatoria() const;
    string getNombre() const;
    int getCantidadCanciones() const;

    const Cancion* getCancionPorId(int idCancion) const;

    string getPortada() const;
};

#endif
