#ifndef ANUNCIOS_H
#define ANUNCIOS_H
#include <string>
using namespace std;

//clase que se encarga de crear los objetos para cada anuncio, haciendo todas las operaciones pertinentes para su rellenado.
class ManejadorAnuncios {
private:
    string archivo;
    string anuncio_actual;
    string categoria;
public:
    ManejadorAnuncios(string nombre_archivo);

    // Obtiene un anuncio aleatorio según la prioridad
    string obtenerAnuncio();

    void mostrarAnuncio();
};

void anuncio();
#endif // ANUNCIOS_H
