#include "Precarga.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

// 🔧 Utilidad para dividir campos por '|'
void dividirCampos(const string& linea, char campos[][100], int& cantidad) {
    cantidad = 0;
    char buffer[500];
    strcpy(buffer, linea.c_str());

    char* token = strtok(buffer, "|");
    while (token != nullptr && cantidad < 10) {
        strcpy(campos[cantidad], token);
        cantidad++;
        token = strtok(nullptr, "|");
    }
}

// 🎤 Precarga de artistas
void cargarArtistas(const string& ruta, Artistica artistas[], int& totalArtistas) {
    ifstream file(ruta);
    string linea;
    totalArtistas = 0;

    while (getline(file, linea)) {
        char campos[5][100];

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
        char campos[8][100];

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

        albumes[totalAlbumes].setDatos(idCompleto, nombre, campos[0], genero, disquera, fecha, portada, calificacion);
        totalAlbumes++;

        // Asociar álbum al artista
        for (int i = 0; i < totalArtistas; ++i) {
            if (artistas[i].getId() == idArtista) {
                artistas[i].agregarAlbum(idCompleto, nombre);
                break;
            }
        }
    }

    file.close();
}

// 🎵 Precarga de canciones
void cargarCanciones(const string& ruta, Album albumes[], int totalAlbumes) {
    ifstream file(ruta);
    string linea;

    while (getline(file, linea)) {
        char campos[3][100];
        int cantidad = 0;

        dividirCampos(linea, campos, cantidad);
        if (cantidad != 3) continue;

        int idCancion = atoi(campos[0]);
        string nombre = campos[1];
        float duracion = atof(campos[2]);

        int idArtista = idCancion / 10000;
        int idAlbum = (idCancion / 100) % 100;
        int idAlbumCompleto = idArtista * 100 + idAlbum;

        for (int i = 0; i < totalAlbumes; ++i) {
            if (albumes[i].getId() == idAlbumCompleto) {
                albumes[i].agregarCancion(idCancion, nombre, duracion);
                break;
            }
        }
    }

    file.close();
}
