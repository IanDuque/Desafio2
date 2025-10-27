#ifndef USUARIO_H
#define USUARIO_H

#include <string>
// Se necesita "Album.h" solo para la declaración de mostrarFavoritos
#include "Album.h"

using namespace std;

// Asegúrate que este valor sea el correcto según los requisitos (50 o 10000)
const int MAX_FAVORITOS = 50;

class Usuario {
private:
    string nombre; // Usado como ID para el nombre del archivo (ej. "usuario1")
    int favoritos[MAX_FAVORITOS];
    int cantidadFavoritos;


    // Función interna para buscar, útil para agregar y copiar
    bool buscarFavorito(int idCancion) const;

public:
    Usuario();
    void setNombre(const string& _nombre);
    string getNombre() const;

    // Gestión de archivos
    void cargarFavoritos();
    void guardarFavoritos() const;

    // Funcionalidad de la lista (Corregidas)
    void agregarFavorito(int idCancion);
    void eliminarFavorito(int idCancion);
    void cargarFavoritosDeOtro(const string& otroNombre);

    // Método para mostrar (requiere que Album.h esté bien definido)
    void mostrarFavoritos(const Album albumes[], int totalAlbumes) const;
    void eliminarFavoritosDeOtro(const string& otroNombre);
};

#endif
