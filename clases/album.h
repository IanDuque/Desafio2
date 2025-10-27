#ifndef ALBUM_H
#define ALBUM_H

#include <string>
using namespace std;

const int MAX_CANCIONES = 15;

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
    int cantidadCanciones;

    int idsCanciones[MAX_CANCIONES];
    string nombresCanciones[MAX_CANCIONES];
    float duracionesCanciones[MAX_CANCIONES];
public:
    Album();
    void setDatos(int _id, const string& _nombre, const string& _artista, const string& _genero,
                  const string& _disquera, const string& _fecha, const string& _ruta, int _calif);
    void agregarCancion(int idCancion, const string& nombreCancion, float duracion);
    void mostrar() const;
    int getId() const;

};

#endif
