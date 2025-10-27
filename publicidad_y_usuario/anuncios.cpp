#include "anuncios.h"

//se genera una semilla para generar numeros aleatorios, y asi conseguir un anuncio al azar entre los que se encuentran en el archivo "anuncios.txt",
//posteriormente se muestra el anuncio y se elimina el objeto que lo contiene.
int main() {
    srand(time(nullptr));
    anuncio();
    return 0;
}
