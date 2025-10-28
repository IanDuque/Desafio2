#ifndef ARTISTICA_H
#define ARTISTICA_H

#include <string>
using namespace std;

const int MAX_ARTISTAS = 30;
const int MAX_ALBUMES = 20;

class Artistica {
private:
    int id;
    string nombre;
    int edad;
    string pais;
    int seguidores;

    int idsAlbumes[MAX_ALBUMES];
    string nombresAlbumes[MAX_ALBUMES];
    int cantidadAlbumes;
public:
    Artistica();
    void setDatos(int _id, const string& _nombre, int _edad, const string& _pais, int _seguidores);
    void agregarAlbum(int idAlbum, const string& nombreAlbum);
    void mostrar() const;
    int getId() const;
    string getnombre() const;

};

#endif
