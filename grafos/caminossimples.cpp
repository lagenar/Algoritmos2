/* Ejercicio 5 de grafos:
   Escribir un algoritmo que, dado un grafo dirigido y dos
   vértices de este grafo, devuelva todos los caminos simples
   de un vertice a otro
*/

#include "Grafo.h"
#include "Lista.h"

#include <iostream>

using namespace std;


template <typename C>
void caminos_simples(const Grafo<C> & grafo, int origen, int destino,
		     bool visitado[], Lista<Lista<int> > & caminos, Lista<int> & camino_parcial)
{
     visitado[origen] = true;
     camino_parcial.agregarFinal(origen);
     if (origen == destino) {
	  caminos.agregarFinal(camino_parcial);
	  camino_parcial.eliminarFinal();
	  visitado[origen] = false;
	  return;
     }
     
     Lista<typename Grafo<C>::Arco> adyacentes;
     grafo.devolverAdyacentes(origen, adyacentes);
     typename Lista<typename Grafo<C>::Arco>::Iterador ady = adyacentes.devolverIterador();
     while (!ady.llegoAlFinal()) {
	  int v = ady.elementoActual().devolverAdyacente();
	  if (!visitado[v]) 
	       caminos_simples(grafo, v, destino, visitado, caminos, camino_parcial);
	  ady.avanzar();
     }
     camino_parcial.eliminarFinal();
     visitado[origen] = false;
}
     
template <typename C>
void mostrar_camino(const Grafo<C> & grafo, const Lista<int> & camino, const char impr[])
{
	Lista<int>::ConstIterador v = camino.devolverIterador();
	while (!v.llegoAlFinal())
	{
		cout << impr[v.elementoActual()] << " ";
		v.avanzar();
	}
	cout << endl;
}

template <typename C>
void mostrar_caminos(const Grafo<C> & grafo, const Lista<Lista<int> > & caminos, const char impr[])
{
	Lista<Lista<int> >::ConstIterador it = caminos.devolverIterador();
	while (!it.llegoAlFinal())
	{
		mostrar_camino(grafo, it.elementoActual(), impr);
		it.avanzar();
	}
}

int main(int argc, char **argv)
{
	Grafo<int> g;
	enum {A, B, C, D};
	const int n = 4;
	g.agregarVertice(A);
	g.agregarVertice(B);
	g.agregarVertice(C);
	g.agregarVertice(D);

	g.agregarArco(A, B, 1);
	g.agregarArco(A, C, 1);
	g.agregarArco(C, B, 1);
	g.agregarArco(B, D, 1);

	Lista<int> camino_parcial;
	Lista<Lista<int> > caminos;
	int tiempo = 0;
	
	bool visitado[n];
	for (int i = 0; i < n; i++)
	{
		visitado[i] = false;
	}
	caminos_simples(g, A, D,
			visitado, caminos, camino_parcial);
	const char impr[] = "ABCD";
	mostrar_caminos(g, caminos, impr);
	
	return 0;
}
