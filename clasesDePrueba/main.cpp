#include <iostream>
#include "Artista.h"
#include "Album.h"
#include "Precarga.h"
using namespace std;

const int MAX_ARTISTAS = 100;
const int MAX_AL =100 ;

int main() {
    Artistica artistas[MAX_ARTISTAS];
    Album albumes[MAX_AL];
    int totalArtistas = 0;
    int totalAlbumes = 0;

    // Precargar datos desde archivos
    cargarArtistas("artista.txt", artistas, totalArtistas);
    cargarAlbumes("album.txt", albumes, totalAlbumes, artistas, totalArtistas);
    cargarCanciones("cancion.txt", albumes, totalAlbumes);



    cout << "\n ARTISTAS PRECARGADOS:\n";
    for (int i = 0; i < totalArtistas; ++i) {
        artistas[i].mostrar();
    }

    // Mostrar álbumes con sus canciones
    cout << "\n ALBUMES PRECARGADOS:\n";
    for (int i = 0; i < totalAlbumes; ++i) {
        albumes[i].mostrar();
    }

    return 0;
}

