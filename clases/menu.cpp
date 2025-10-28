#include "menu.h"
#include "usuario.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "precarga.h" // Se usa para MAX_CAMPO_LEN y MAX_FIELDS
#include <cctype>

using namespace std;

// IMPORTANTE: La funcion dividirCampos fue eliminada de aqui y ahora
// solo esta en precarga.cpp, como debe ser, usando la declaracion de precarga.h.

Usuario usuarioactual; // Declaracion de la variable global

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
                // CORRECCION: Usar las constantes de tamano de precarga.h
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

        if (!usuarioencontrado && opcion != 'M') { // Si no fue encontrado y no hubo error de archivo
            cerr << "El usuario ingresado no se encuentra registrado en la plataforma." << endl;
            cout << "[R] Reintentar ingreso" << endl;
            cout << "[M] Regresar al Menu Principal" << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            opcion = toupper(static_cast<unsigned char>(opcion));

            if (opcion == 'M') {
                break;
            }
        }

    } while (opcion == 'R');
}
int menuPrincipal(fstream& metricas, Album albumes[], int totalAlbumes) {
    int opcion;

    while (true) {
        // CORRECCION CRITICA: Manejo robusto de entrada invalida
        if (cin.fail()) {
            cin.clear(); // Restablece los flags de error de cin
            cin.ignore(1000, '\n'); // Desecha los caracteres restantes en el buffer
        }

        cout << "\n============================================\n";
        cout << "               MENU PRINCIPAL               \n";
        cout << "============================================\n";
        cout << "  [1] Ingresar / Cambiar de Usuario\n";
        cout << "  [2] Reproducir Cancion Aleatoria\n";
        cout << "  [3] Reproducir Lista de Favoritos\n";
        cout << "  [4] Mostrar Metricas de Ejecucion\n";
        cout << "  [0] Finalizar Ejecucion\n";
        cout << "--------------------------------------------\n";
        cout << "Seleccione una opcion: ";

        //si se ingreso una opcion y esta esta entre 0 y 4 continua al switch.
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

    //se elige una opcion a realizar
    switch (opcion) {
    case 1:
        ingresarusuario();
        // CRITICO: Cargar la lista de favoritos inmediatamente despues de ingresar
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
            origen = toupper(static_cast<unsigned char>(origen));

            if (origen == 'F') {

                reproducirAleatorioFavoritos(usuarioactual, albumes, totalAlbumes);
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
            // Asumo que esta funcion existe:
            usuarioactual.mostrarFavoritos(albumes, totalAlbumes);
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
