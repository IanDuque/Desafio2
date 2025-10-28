#ifndef ANUNCIOS_H
#define ANUNCIOS_H
#include <string>
using namespace std;

class ManejadorAnuncios {
private:
    string archivo;
    string anuncio_actual;
    string categoria;
public:
    ManejadorAnuncios(string nombre_archivo);

    string obtenerAnuncio();

    void mostrarAnuncio();

    string getCategoria() const { return categoria; }
    string getAnuncio() const { return anuncio_actual; }
};

void anuncio();
#endif
