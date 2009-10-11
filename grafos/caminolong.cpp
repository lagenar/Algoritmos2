#include "Grafo.h"
#include "Lista.h"
#include <iostream>

using namespace std;

template <typename C>
bool existe_camino_long(const Grafo<C> & g, int origen, int destino, int longi, int longi_actual)
{
     if (longi_actual == longi)
	  return origen == destino;

     Lista<typename Grafo<C>::Arco> adyacentes;
     g.devolverAdyacentes(origen, adyacentes);
     typename Lista<typename Grafo<C>::Arco>::Iterador ady = adyacentes.devolverIterador();
     bool existe_camino = false;
     while (!ady.llegoAlFinal() && !existe_camino) {
	  int v = ady.elementoActual().devolverAdyacente();
	  existe_camino = existe_camino_long(g, v, destino, longi, longi_actual + 1);
	  ady.avanzar();
     }
     return existe_camino;
}

int main(int argc, char *argv[])
{
     enum {A, B, C, D};
     Grafo<int> g;
     g.agregarVertice(A);
     g.agregarVertice(B);
     g.agregarVertice(C);
     g.agregarVertice(D);

     g.agregarArco(A, B, 1);
     g.agregarArco(B, A, 1);
     g.agregarArco(B, C, 1);
     g.agregarArco(C, D, 1);

     if (existe_camino_long(g, A, D, 8, 0))
	  cout << "si, existe" << endl;
     else
	  cout << "no existe" << endl;
     return 0;
}
