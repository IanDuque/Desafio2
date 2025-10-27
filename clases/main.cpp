#include <iostream>
#include "Artista.h"
#include "Album.h"
#include "Precarga.h"
#include <fstream>
#include "usuario.h"
using namespace std;

const int MAX_ARTISTAS = 100;
const int MAX_AL =100 ;

int main() {
    Artistica artistas[MAX_ARTISTAS];
    Album albumes[MAX_AL];
    int totalArtistas = 0;
    int totalAlbumes = 0;

    //se inicializa el archivo para guardar los datos de las metricas
    fstream metricas("metricas.txt");
    if (!metricas.is_open()){
        cerr<< "error al abrir el archivo" << endl;
    }

    // Precargar datos desde archivos
    cargarArtistas("artista.txt", artistas, totalArtistas);
    cargarAlbumes("album.txt", albumes, totalAlbumes, artistas, totalArtistas);
    cargarCanciones("cancion.txt", albumes, totalAlbumes);

    Usuario u;
    u.setNombre("usuario1");
    u.cargarFavoritos();

    // Agregar canción 2 del álbum 1000101
    //u.agregarFavoritoPorAlbumYCancion(1000101, 2, albumes, totalAlbumes);

    u.mostrarFavoritos(albumes, totalAlbumes);


    cout<<endl;

    u.cargarFavoritosDeOtro("usuario2");
    u.mostrarFavoritos(albumes,totalAlbumes);


    cout<<endl;
    u.eliminarFavoritosDeOtro("usuario2");
    u.mostrarFavoritos(albumes,totalAlbumes);


    cout<<endl;
    u.cargarFavoritosDeOtro("usuario3");
    u.mostrarFavoritos(albumes,totalAlbumes);



    //se cierra el archivo al final de la ejecucion
    metricas.close();
    return 0;
}
