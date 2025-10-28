#ifndef PRECARGA_H
#define PRECARGA_H

#include <string>
#include "Artista.h"
#include "Album.h"
#include "usuario.h"
using namespace std;

const int MAX_CAMPO_LEN = 100; // Longitud máxima para un campo de datos
const int MAX_FIELDS = 10;     // Máximo número de campos a dividir

void dividirCampos(const string& linea, char campos[][MAX_CAMPO_LEN], int& cantidad);
void cargarArtistas(const string& ruta, Artistica artistas[], int& totalArtistas);
void cargarAlbumes(const string& ruta, Album albumes[], int& totalAlbumes, Artistica artistas[], int totalArtistas);
void cargarCanciones(const string& ruta, Album albumes[], int totalAlbumes);
void reproducirAleatorioFavoritos(const Usuario& usuario, const Album albumes[], int totalAlbumes);
void reproducirAleatorioCatalogo(const Album albumes[], int totalAlbumes);

#endif
