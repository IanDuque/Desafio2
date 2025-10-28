#include "precarga.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "usuario.h"
#include "album.h"
#include "artista.h" // Asegurar que esta clase se pueda usar

using namespace std;

// CORRECCION DE SEGURIDAD: Uso de strncpy para evitar desbordamiento de buffer
void dividirCampos(const string& linea, char campos[][MAX_CAMPO_LEN], int& cantidad) {
    cantidad = 0;
    const int LINE_BUFFER_SIZE = 500;
    char buffer[LINE_BUFFER_SIZE];

    // Copia segura de la linea al buffer local (usando LINE_BUFFER_SIZE - 1)
    strncpy(buffer, linea.c_str(), LINE_BUFFER_SIZE - 1);
    buffer[LINE_BUFFER_SIZE - 1] = '\0'; // Asegurar terminador nulo

    char* token = strtok(buffer, "|");
    while (token != nullptr && cantidad < MAX_FIELDS) {
        // Copia segura del token al campo (usando MAX_CAMPO_LEN - 1)
        strncpy(campos[cantidad], token, MAX_CAMPO_LEN - 1);
        campos[cantidad][MAX_CAMPO_LEN - 1] = '\0'; // Asegurar terminador nulo
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
    if (usuario.getCantidadFavoritos() == 0) {
        cout << "Tu lista de favoritos esta vacia. No se puede reproducir.\n";
        return;
    }

    // 1. Generar un indice aleatorio dentro del rango de favoritos
    int indiceAleatorio = rand() % usuario.getCantidadFavoritos();

    // 2. Obtener el ID de la cancion favorita
    int idCancion = usuario.getFavoritoPorIndice(indiceAleatorio);

    // 3. Obtener el ID del album al que pertenece (AABB del AABBCC)
    int idAlbumBuscado = (idCancion / 100);

    cout << "\n Reproduciendo de FAVORITOS:\n";
    for (int i = 0; i < totalAlbumes; ++i) {
        if (albumes[i].getId() == idAlbumBuscado) {
            // Llama a la nueva funcion del Album
            albumes[i].simularReproduccion(idCancion);
            return;
        }
    }

    cout << "  -> Error: No se encontro el Album (ID: " << idAlbumBuscado << ") en el catalogo.\n";
}

// --- FUNCION 2: Reproducir Aleatorio del Catalogo Completo ---
void reproducirAleatorioCatalogo(const Album albumes[], int totalAlbumes) {
    if (totalAlbumes == 0) {
        cout << "El catalogo esta vacio. No se puede reproducir.\n";
        return;
    }

    // 1. Elegir un album aleatorio
    int indiceAlbum = 0;

    // Aseguramos que elegimos un album que tenga al menos una cancion
    do {
        indiceAlbum = rand() % totalAlbumes;
    } while (albumes[indiceAlbum].getCantidadCanciones() == 0 && totalAlbumes > 1);

    const Album& albumSeleccionado = albumes[indiceAlbum];

    if (albumSeleccionado.getCantidadCanciones() == 0) {
        cout << "Error: No se encontraron canciones en los albumes precargados.\n";
        return;
    }

    // 2. Elegir una cancion aleatoria dentro de ese album
    int idCancion = albumSeleccionado.getIDdeCancionAleatoria();

    // Se elimino el acento de CATALGO
    cout << "\n Reproduciendo del CATALOGO COMPLETO:\n";
    cout << "  -> Artista: " << albumSeleccionado.getArtista() << ", Album: " << albumSeleccionado.getNombre() << endl;

    // Llama a la nueva funcion del Album
    albumSeleccionado.simularReproduccion(idCancion);
}
