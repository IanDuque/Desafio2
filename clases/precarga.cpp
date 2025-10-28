#include "precarga.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "usuario.h"
#include "album.h"
#include "cancion.h"
#include "artista.h"
#include "menu.h"
using namespace std;

extern Usuario usuarioactual;
void dividirCampos(const string& linea, char campos[][MAX_CAMPO_LEN], int& cantidad) {
    cantidad = 0;
    const int LINE_BUFFER_SIZE = 500;
    char buffer[LINE_BUFFER_SIZE];

    strncpy(buffer, linea.c_str(), LINE_BUFFER_SIZE - 1);
    buffer[LINE_BUFFER_SIZE - 1] = '\0';

    char* token = strtok(buffer, "|");
    while (token != nullptr && cantidad < MAX_FIELDS) {
        strncpy(campos[cantidad], token, MAX_CAMPO_LEN - 1);
        campos[cantidad][MAX_CAMPO_LEN - 1] = '\0';
        cantidad++;
        token = strtok(nullptr, "|");
    }
}

void cargarArtistas(const string& ruta, Artistica artistas[], int& totalArtistas) {
    ifstream file(ruta);
    string linea;
    totalArtistas = 0;

    while (getline(file, linea)) {
        char campos[MAX_FIELDS][MAX_CAMPO_LEN];

        int cantidad = 0;
        dividirCampos(linea, campos, cantidad);
        if (cantidad != 5) continue;

        int id = atoi(campos[0]);
        string nombre = campos[1];
        int edad = atoi(campos[2]);
        string pais = campos[3];
        int seguidores = atoi(campos[4]);

        artistas[totalArtistas].setDatos(id, nombre, edad, pais, seguidores);
        totalArtistas++;
    }

    file.close();
}


void cargarAlbumes(const string& ruta, Album albumes[], int& totalAlbumes, Artistica artistas[], int totalArtistas) {
    ifstream file(ruta);
    string linea;
    totalAlbumes = 0;

    while (getline(file, linea)) {
        char campos[MAX_FIELDS][MAX_CAMPO_LEN];

        int cantidad = 0;
        dividirCampos(linea, campos, cantidad);
        if (cantidad != 8) continue;

        int idArtista = atoi(campos[0]);
        int idAlbum = atoi(campos[1]);
        int idCompleto = idArtista * 100 + idAlbum;

        string nombre = campos[2];
        string genero = campos[3];
        string disquera = campos[4];
        string fecha = campos[5];
        string portada = campos[6];
        int calificacion = atoi(campos[7]);
        string nombreArtista = "Desconocido";
        for (int i = 0; i < totalArtistas; ++i) {
            if (artistas[i].getId() == idArtista) {
                artistas[i].agregarAlbum(idCompleto, nombre);
                nombreArtista = artistas[i].getnombre();
                break;
            }
        }
        albumes[totalAlbumes].setDatos(idCompleto, nombre, nombreArtista, genero, disquera, fecha, portada, calificacion,0);
        totalAlbumes++;
    }

    file.close();
}

void cargarCanciones(const string& ruta, Album albumes[], int totalAlbumes) {
    ifstream file(ruta);
    string linea;

    while (getline(file, linea)) {
        char campos[MAX_FIELDS][MAX_CAMPO_LEN];
        int cantidad = 0;
        dividirCampos(linea, campos, cantidad);
        if (cantidad != 3) continue;

        int idCancion = atoi(campos[0]);
        string nombre = campos[1];
        float duracion = atof(campos[2]);

        int idArtista = idCancion / 10000;
        int idAlbumSimple = (idCancion / 100) % 100;
        int idAlbumCompleto = idArtista * 100 + idAlbumSimple;
        bool encontrado = false;
        for (int i = 0; i < totalAlbumes; i++) {
            if (albumes[i].getId() == idAlbumCompleto) {

                albumes[i].agregarCancion(idCancion, nombre, duracion);
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << "No se encontro el album con ID " << idAlbumCompleto << " para la cancion " << nombre << endl;
        }
    }
    file.close();
}
void reproducirAleatorioFavoritos(const Usuario& usuario, const Album albumes[], int totalAlbumes) {
    int cantidad = usuario.getCantidadFavoritosusuario();

    if (cantidad == 0) {
        cout << "Tu lista de favoritos esta vacia." << endl;
        return;
    }

    int indiceAleatorio = rand() % cantidad;
    int idCancionAleatoria = usuario.getFavoritoPorIndice(indiceAleatorio);

    const Cancion* cancion = buscarCancionPorId(idCancionAleatoria, albumes, totalAlbumes);
    const Album* album = nullptr;

    if (cancion != nullptr) {
        int idAlbumCompleto = idCancionAleatoria / 100;
        for (int j = 0; j < totalAlbumes; ++j) {
            if (albumes[j].getId() == idAlbumCompleto) {
                album = &albumes[j];
                break;
            }
        }
    }

    // 3. Llamar a la simulación con el menú y anuncios
    if (cancion != nullptr && album != nullptr) {
        cout << "Reproduccion Aleatoria de Favoritos iniciada.\n";
        simularReproduccion(*cancion, *album);
    } else {
        cout << "La cancion favorita seleccionada (ID: " << idCancionAleatoria << ") no se encontro en el catalogo." << endl;
    }
}

void reproducirAleatorioCatalogo(const Album albumes[], int totalAlbumes) {

    if (totalAlbumes == 0) {
        cout << "El catalogo esta vacio." << endl;
        return;
    }

    int indiceAlbum = rand() % totalAlbumes;
    const Album& albumAleatorio = albumes[indiceAlbum];

    if (albumAleatorio.getCantidadCanciones() == 0) {
        cout << "El album seleccionado no tiene canciones." << endl;
        return;
    }
    int idCancionAleatoria = albumAleatorio.getIDdeCancionAleatoria();

    const Cancion* cancion = albumAleatorio.getCancionPorId(idCancionAleatoria);

    if (cancion != nullptr) {
        simularReproduccion(*cancion, albumAleatorio);
    } else {
        cout << "La cancion seleccionada (ID: " << idCancionAleatoria << ") no se encontro." << endl;
    }
}
