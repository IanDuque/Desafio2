#include "menu.h"
#include "usuario.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

Usuario usuarioactual;

void dividirCampos(const string& linea, char campos[][30], int& cantidad) {
    cantidad = 0;
    char buffer[500];
    strcpy(buffer, linea.c_str());

    char* token = strtok(buffer, "|");
    while (token != nullptr && cantidad < 10) {
        strcpy(campos[cantidad], token);
        cantidad++;
        token = strtok(nullptr, "|");
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
                char campos[20][30];
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
            opcion = toupper(opcion);

            if (opcion == 'M') {
                break;
            }
        }

    } while (opcion == 'R');
}
int menuPrincipal(fstream& metricas) {
    int opcion;

    while (true) {
        cout << "\n============================================\n";
        cout << "                MENU PRINCIPAL            \n";
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
                cout << "Opcion invalida";
            }
        }
    }

    //se elige una opcion a realizar
    switch (opcion) {
    case 1:
        ingresarusuario();
        break;
    case 2:
        //reproducirAleatorio();
        break;
    case 3:
        //reproducirFavoritos();
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
