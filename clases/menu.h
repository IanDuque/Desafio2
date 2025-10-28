#ifndef MENU_H
#define MENU_H

#include <fstream>
#include "album.h"
#include "usuario.h"
#include "cancion.h"

using namespace std;


int menuPrincipal(fstream& metricas, Album albumes[], int totalAlbumes);
void ingresarusuario();
void reproducirFavoritos(const Usuario& usuario, const Album albumes[], int totalAlbumes);

const Cancion* buscarCancionPorId(int idCancion, const Album albumes[], int totalAlbumes);

void simularReproduccion(const Cancion& cancion, const Album& album);

#endif
