#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "usuario.h"
#include "album.h"
#include "artista.h"
#include "precarga.h"
#include "menu.h"

using namespace std;

Usuario usuarioactual;
int contadorCancionesReproducidas = 0;



int main() {
    srand(time(NULL));

    Album albumes[MAX_ALBUMES];
    Artistica artistas[MAX_ARTISTAS];
    int totalAlbumes = 0;
    int totalArtistas = 0;

    cargarArtistas("artistas.txt", artistas, totalArtistas);
    cargarAlbumes("albumes.txt", albumes, totalAlbumes, artistas, totalArtistas);
    cargarCanciones("canciones.txt", albumes, totalAlbumes);

    int opcion = -1;
    fstream metricas;

    do {
        opcion = menuPrincipal(metricas, albumes, totalAlbumes);
    } while (opcion != 0);

    return 0;
}
