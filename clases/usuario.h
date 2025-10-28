#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Album.h"

using namespace std;

const int MAX_FAVORITOS = 10000;

class Usuario {
private:
    string nombre;
    int favoritos[MAX_FAVORITOS];
    int cantidadFavoritosusuario;
    int cantidadFavoritostotal;
    bool buscarFavorito(int idCancion) const;
    bool premium;
    string ciudad;
    string pais;
    string fechaRegistro;
public:
    Usuario();
    //getters y setters
    void setNombre(const string& _nombre);
    string getNombre() const;
    void setmembresia(const string& membresia);
    void setCiudad(const string& ciudad);
    void setPais(const string& pais);
    void setFechaRegistro(const string& fechaRegistro);
    int getCantidadFavoritos() const;
    int getFavoritoPorIndice(int indice) const;

    // Gestión de archivos.
    void cargarFavoritos();
    void guardarFavoritos() const;

    //Funciones necesarias para editar la lista.
    void agregarFavorito(int idCancion);
    void eliminarFavorito(int idCancion);
    void cargarFavoritosDeOtro(const string& otroNombre);
    void eliminarFavoritosDeOtro();

    //Funciones para mostrar la lista de favoritos.
    void mostrarFavoritos(const Album albumes[], int totalAlbumes) const;
};

#endif
