#ifndef PRECARGA_H
#define PRECARGA_H

#include <string>
#include "Artista.h"
#include "Album.h"
using namespace std;


void dividirCampos(const string& linea, char campos[][100], int& cantidad);
void cargarArtistas(const string& ruta, Artistica artistas[], int& totalArtistas);
void cargarAlbumes(const string& ruta, Album albumes[], int& totalAlbumes, Artistica artistas[], int totalArtistas);
void cargarCanciones(const string& ruta, Album albumes[], int totalAlbumes);

#endif
