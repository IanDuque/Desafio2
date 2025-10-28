#include "menu.h"
#include "usuario.h"
#include "album.h"
#include "artista.h"
#include "cancion.h"
#include "precarga.h"
#include "anuncios.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

extern Usuario usuarioactual;
extern int contadorCancionesReproducidas;

void menuReproduccion(bool esPremium);

char toUpperChar(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A');
    }
    return c;
}

const Cancion* buscarCancionPorId(int idCancion, const Album albumes[], int totalAlbumes) {
    int idAlbumCompleto = idCancion / 100;

    for (int i = 0; i < totalAlbumes; ++i) {
        if (albumes[i].getId() == idAlbumCompleto) {
            const Cancion* cancion = albumes[i].getCancionPorId(idCancion);
            if (cancion != nullptr) {
                return cancion;
            }
        }
    }
    return nullptr;
}

void simularReproduccion(const Cancion& cancion, const Album& album) {

    contadorCancionesReproducidas++;

    bool esPremium = usuarioactual.getmembresia();
    bool mostrarAnuncio = !esPremium && (contadorCancionesReproducidas > 1) && (contadorCancionesReproducidas % 2 == 0);

    ManejadorAnuncios *anuncio = nullptr;

    if (mostrarAnuncio) {
        anuncio = new ManejadorAnuncios("anuncios.txt");
        anuncio->obtenerAnuncio();
    }

    cout << "\n============================================\n";
    cout << "           REPRODUCIENDO\n";
    cout << "============================================\n";

    if (mostrarAnuncio && anuncio != nullptr) {
        cout << "Mensaje publicitario\": " << anuncio->getAnuncio() << endl;
        cout << "Categoría del mensaje: " << anuncio->getCategoria() << endl;
        cout << "--------------------------------------------\n";
    }
    cout << "Cantante: " << album.getArtista() << endl;
    cout << "Álbum: " << album.getNombre() << endl;
    cout << "Ruta a la portada del álbum: " << album.getPortada() << endl;
    cout << "Título de la canción reproducida: " << cancion.getNombre() << endl;
    cout << "Ruta al archivo de audio: [Ruta/de/audio/" << cancion.getId() << ".mp3]" << endl;
    cout << "Duración: " << cancion.getDuracion() << " segundos" << endl;
    cout << "--------------------------------------------\n";

    menuReproduccion(esPremium);

    if (anuncio != nullptr) {
        delete anuncio;
        anuncio = nullptr;
    }
}

void reproducirFavoritos(const Usuario& usuario, const Album albumes[], int totalAlbumes) {

    const int* favoritos = usuario.getFavoritos();
    int cantidad = usuario.getCantidadFavoritosusuario();

    if (cantidad == 0) {
        cout << "\nTu lista de favoritos esta vacia. No hay canciones para reproducir." << endl;
        return;
    }

    cout << "\n============================================\n";
    cout << "  LISTA DE FAVORITOS: " << usuario.getNombre() << "\n";
    cout << "============================================\n";

    for (int i = 0; i < cantidad; ++i) {
        int idActual = favoritos[i];

        const Cancion* cancion = buscarCancionPorId(idActual, albumes, totalAlbumes);
        const Album* album = nullptr;

        if (cancion != nullptr) {
            int idAlbumCompleto = idActual / 100;
            for (int j = 0; j < totalAlbumes; ++j) {
                if (albumes[j].getId() == idAlbumCompleto) {
                    album = &albumes[j];
                    break;
                }
            }
        }

        if (cancion != nullptr && album != nullptr) {
            cout << "Cargando cancion " << i + 1 << " de la lista...\n";
            simularReproduccion(*cancion, *album);
        } else {
            cout << "[" << i + 1 << "/" << cantidad << "]Cancion con ID " << idActual << " no encontrada en el catalogo." << endl;
        }
    }
    cout << "\nReproduccion de la lista finalizada." << endl;
}

void menuReproduccion(bool esPremium) {

    int opcion;
    bool enPausa = true;

    while (true) {
        cout << "\n--- CONTROL DE REPRODUCCIÓN ---\n";

        if (esPremium) {
            cout << "  [1] " << (enPausa ? "Continuar" : "Pausar") << "\n";
            cout << "  [2] Siguiente\n";
            cout << "  [3] Anterior (Solo Premium)\n";
            cout << "  [4] Bucle (Solo Premium)\n";
        } else {
            cout << "  [1] " << (enPausa ? "Continuar" : "Pausar") << "\n";
            cout << "  [2] Siguiente\n";
        }

        cout << "  [0] Salir de la reproducción\n";
        cout << "-------------------------------\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cout << "Entrada no valida." << endl;
            break;
        }

        if (!esPremium && (opcion == 3 || opcion == 4)) {
            cout << "Opcion solo disponible para usuarios PREMIUM." << endl;
            continue;
        }

        switch (opcion) {
        case 1:
            enPausa = !enPausa;
            cout << (enPausa ? "Pausado." : "Continuando.") << endl;
            break;
        case 2:
            cout << "⏩ Saltando a la siguiente canción." << endl;
            return;
        case 3:
            if (esPremium) { cout << "Volviendo a la cancion anterior." << endl; }
            break;
        case 4:
            if (esPremium) { cout << "Activando/Desactivando bucle." << endl; }
            break;
        case 0:
            cout << "\nVolviendo al Menú Principal..." << endl;
            return;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
            break;
        }
    }
}

void ingresarusuario() {
    string nickname;
    char opcion = 'R';

    do {
        cout << "\n============================================\n";
        cout << "Ingrese su nickname: ";
        cin >> nickname;

        ifstream accesos("usuarios.txt");
        if (!accesos.is_open()) {
            cerr << "no se ha podido acceder a los usuarios registrados" << endl;
            opcion = 'M';
            continue;
        }

        string linea = "";
        bool usuarioencontrado = false;

        while (getline(accesos, linea)) {
            if (linea.find(nickname + "|") == 0) {
                usuarioencontrado = true;
                char campos[MAX_FIELDS][MAX_CAMPO_LEN];
                int cantidadCampos = 0;

                dividirCampos(linea, campos, cantidadCampos);

                if (cantidadCampos >= 5) {
                    usuarioactual.setNombre(string(campos[0]));
                    usuarioactual.setmembresia(string(campos[1]));
                    usuarioactual.setCiudad(string(campos[2]));
                    usuarioactual.setPais(string(campos[3]));
                    usuarioactual.setFechaRegistro(string(campos[4]));

                    cout << "Bienvenido, " << campos[0] << ", actualmente tienes membresia: " << campos[1] << endl;
                    opcion = 'M';
                }
                break;
            }
        }
        accesos.close();

        if (!usuarioencontrado && opcion != 'M') {
            cerr << "El usuario ingresado no se encuentra registrado en la plataforma." << endl;
            cout << "[R] Reintentar ingreso" << endl;
            cout << "[M] Regresar al Menu Principal" << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            opcion = toUpperChar(opcion);

            if (opcion == 'M') {
                break;
            }
        }

    } while (opcion == 'R');
}

int menuPrincipal(fstream& metricas, Album albumes[], int totalAlbumes) {
    int opcion;

    while (true) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "\n============================================\n";
        cout << "             MENU PRINCIPAL              \n";
        cout << "============================================\n";
        cout << "  [1] Ingresar / Cambiar de Usuario\n";
        cout << "  [2] Reproducir Cancion Aleatoria\n";
        cout << "  [3] Reproducir Lista de Favoritos\n";
        cout << "  [4] Mostrar Metricas de Ejecucion\n";
        cout << "  [0] Finalizar Ejecucion\n";
        cout << "--------------------------------------------\n";
        cout << "Seleccione una opcion: ";

        if (cin >> opcion) {
            if (opcion >= 0 && opcion <= 4) {
                break;
            } else {
                cout << "Opcion invalida. Ingrese un numero entre 0 y 4.\n";
            }
        } else {
            cout << "Entrada invalida. Por favor, ingrese solo el numero de la opcion (0-4).\n";
        }
    }

    if (opcion != 3 && opcion != 2) {
        contadorCancionesReproducidas = 0;
    }

    switch (opcion) {
    case 1:
        ingresarusuario();
        if (!usuarioactual.getNombre().empty()) {
            usuarioactual.cargarFavoritos();
        }
        break;
    case 2:
        if (usuarioactual.getNombre().empty()) {
            cout << "Debe ingresar un usuario primero (Opcion 1).\n";
        } else {
            char origen;
            cout << "\n Seleccione origen de la reproduccion aleatoria:\n";
            cout << " [F] Favoritos\n";
            cout << " [C] Catalogo\n";
            cout << " Seleccione: ";
            cin >> origen;
            origen = toUpperChar(origen);

            if (origen == 'F') {
                if (usuarioactual.getmembresia()==1){
                    reproducirAleatorioFavoritos(usuarioactual, albumes, totalAlbumes);
                }
                else {
                    cout << "necesita ser premium para acceder a esta funcion" << endl;
                }
            } else if (origen == 'C') {
                reproducirAleatorioCatalogo(albumes, totalAlbumes);
            } else {
                cout << "Opcion invalida. Regresando al menu.\n";
            }
        }
        break;
    case 3:
        if (usuarioactual.getNombre().empty()) {
            cout << "Debe ingresar un usuario primero (Opcion 1).\n";
        } else {
            if (usuarioactual.getmembresia()==1){
                reproducirFavoritos(usuarioactual, albumes, totalAlbumes);
            }
            else {
                cout << "necesita ser premium para acceder a esta funcion" << endl;
            }
        }
        break;
    case 4:
        //mostrarmetricas();
        break;
    case 0:
        cout << "muchas gracias por utilizar nuestro programa, esperamos que nos siga eligiendo" << endl;
        break;
    }
    return opcion;
}
