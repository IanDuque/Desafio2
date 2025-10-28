#ifndef METRICAS_H
#define METRICAS_H
#include "artista.h"
#include "album.h"
#include <string>
using namespace std;

long long calcular_memoria_usada(int totalArtistas, int totalAlbumes);
void abrir_archivo();
void cerrar_archivo();
void agregar_metrica(long int iteraciones, long int memoria, string nombrefuncion);
void mostrarmetricas();
#endif
