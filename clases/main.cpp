#include "menu.h"
#include "artista.h"
#include "album.h"
#include "precarga.h"
#include "metricas.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int MAX_ARTISTAS = 100;
const int MAX_AL = 100;
long int iteraciones = 0;

Artistica* artistas = new Artistica[MAX_ARTISTAS];
Album* albumes = new Album[MAX_AL];
int totalArtistas = 0;
int totalAlbumes = 0;

int main() {
    srand(time(nullptr));
    int opcion = -1;

    //se abre el archivo de metricas para guardar todo en su interior.
    fstream metricas("metricas.txt", ios::out | ios::app);
    if (!metricas.is_open()) {
        cerr << "Error al abrir el archivo de metricas." << endl;
    }

    //se cargan todos los datos de los archivos correspondientes.
    cargarArtistas("artista.txt", artistas, totalArtistas);
    cargarAlbumes("album.txt", albumes, totalAlbumes, artistas, totalArtistas);
    cargarCanciones("cancion.txt", albumes, totalAlbumes);

    //mientras la opcion no sea 0 el programa continua ejecutandose.
    do {
        //se pasa por referencia metricas para que
        opcion = menuPrincipal(metricas, albumes, totalAlbumes);
    } while (opcion != 0);

    //se cierra el archivo de metricas al finalizar la ejecucion.
    metricas.close();

    return 0;
}
