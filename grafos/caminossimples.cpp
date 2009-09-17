/* Ejercicio 5 de grafos:
   Escribir un algoritmo que, dado un grafo dirigido y dos
   vértices de este grafo, devuelva todos los caminos simples
   de un vertice a otro
*/

#include "Grafo.h"
#include "Lista.h"

#include <iostream>

using namespace std;

#define NO_DESC -1

bool es_arco_retroceso(int u, int v, const  int descubierto[],
		       const int fin_desc[])
{
	return (descubierto[u] >= descubierto[v] &&
		fin_desc[v] == NO_DESC);
}

template <typename C>
void caminos_simples(const Grafo<C> & grafo, int origen, int destino,
		     int descubierto[], int fin_desc[], int & tiempo,
		     bool visitado[], Lista<Lista<int> > & caminos, Lista<int> & camino_parcial)
{
	if (!visitado[origen])
	{
		visitado[origen] = true;
		descubierto[origen] = tiempo;
		tiempo++;
	}
	camino_parcial.agregarFinal(origen);
	if (origen == destino)
	{
		caminos.agregarFinal(camino_parcial);
	}
	Lista<typename Grafo<C>::Arco> adyacentes;
	grafo.devolverAdyacentes(origen, adyacentes);
	typename Lista<typename Grafo<C>::Arco>::Iterador ady = adyacentes.devolverIterador();
	while (!ady.llegoAlFinal())
	{
		int v = ady.elementoActual().devolverAdyacente();
		if (!visitado[v] || !es_arco_retroceso(origen, v, descubierto, fin_desc))
		{
			caminos_simples(grafo, v, destino, descubierto, fin_desc, tiempo,
					visitado, caminos, camino_parcial);
		}
		else if (v == destino)
		{
			camino_parcial.agregarFinal(v);
			caminos.agregarFinal(camino_parcial);
			camino_parcial.eliminarFinal();
		}
		ady.avanzar();
	}
	if (fin_desc[origen] == NO_DESC)
	{
		fin_desc[origen] = tiempo;
		tiempo++;
	}
	camino_parcial.eliminarFinal();
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
	enum {A, B, C, D, E, F, G};
	g.agregarVertice(A);
	g.agregarVertice(B);
	g.agregarVertice(C);
	g.agregarVertice(D);
	g.agregarVertice(E);
	g.agregarVertice(F);
	g.agregarVertice(G);

	g.agregarArco(A, B, 1);
	g.agregarArco(A, C, 1);
	g.agregarArco(A, D, 1);
	g.agregarArco(B, F, 1);
	g.agregarArco(C, E, 1);	
	g.agregarArco(D, G, 1);
	g.agregarArco(E, F, 1);
	g.agregarArco(F, A, 1);

	Lista<int> camino_parcial;
	Lista<Lista<int> > caminos;
	int tiempo = 0;
	
	bool visitado[G];
	int descubierto[G];
	int fin_desc[G];
	for (int i = 0; i < G; i++)
	{
		visitado[i] = false;
		descubierto[i] = fin_desc[i] = NO_DESC;
	}
	caminos_simples(g, A, A,
			descubierto, fin_desc, tiempo,
			visitado, caminos, camino_parcial);
	const char impr[] = "ABCDEFG";
	mostrar_caminos(g, caminos, impr);
	
	return 0;
}
